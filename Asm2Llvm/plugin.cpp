#include "plugin.h"
#include "Asm2LLvm.h"
#include <map>

enum class MenuEntries {
	ASM2LLVM_VCPU_OPT,
	ASM2LLVM_VCPU_NO_OPT,
	ASM2LLVM_NATIVE_OPT,
	ASM2LLVM_NATIVE_NO_OPT,
	ASSEMBLY,
	REGISTERS
};

bool Begin(int argc, char** argv)
{
	return true;
}

bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	_plugin_registercommand(pluginHandle, "Asm2LLVM", Begin, true);
	return true;
}

void pluginStop()
{
}

void pluginSetup()
{
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_VCPU_OPT), "&LLVM IR VCPU Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_VCPU_NO_OPT), "&LLVM IR VCPU Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_NATIVE_OPT), "&LLVM IR Native Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_NATIVE_NO_OPT), "&LLVM IR Native Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASSEMBLY), "&Assembly");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::REGISTERS), "&Registers");

	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASM2LLVM_VCPU_OPT), "T");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASSEMBLY), "Y");
}

bool Is64Bit()
{
#ifdef _WIN64
	return true;
#else
	return false;
#endif
}

#define CHECK(BOOLVAR, IFTRUE, ELSE) ((BOOLVAR) == true ? (IFTRUE) : (ELSE))

INSTRUX Decode(LPVOID addr)
{
	INSTRUX ix;
	NdDecodeEx(&ix, (uint8_t*)addr, ND_MIN_BUF_SIZE, CHECK(!Is64Bit(), ND_CODE_32, ND_CODE_64), CHECK(!Is64Bit(), ND_DATA_32, ND_DATA_64));
	return ix;
}

std::map<cpu_reg, std::string> reg_map()
{
	return { { cRAX, "RAX" }, { cRCX, "RCX" }, { cRDX, "RDX" }, { cRBX, "RBX" }, { cRSP, "RSP" }, { cRBP, "RBP" }, { cRSI, "RSI" }, { cRDI, "RDI" },
			 { cR8,  "R8"  }, { cR9,  "R9"  }, { cR10, "R10" }, { cR11, "R11" }, { cR12, "R12" }, { cR13, "R13" }, { cR14, "R14" }, { cR15, "R15" },
			 { cRFLAGS, "RFLAGS" }
	};
}

void TranslateBlock(enum MenuEntries entry)
{
	BridgeCFGraphList graphList;
	GuiGetCurrentGraph(&graphList);
	BridgeCFGraph currentGraph(&graphList, true);

	if (currentGraph.nodes.empty())
		return;

	std::vector<std::pair<uintptr_t, uintptr_t>> ranges;
	for (const auto& nodeIt : currentGraph.nodes) {
		const BridgeCFNode& node = nodeIt.second;
		uintptr_t start = node.instrs.empty() ? node.start : node.instrs[0].addr;
		uintptr_t end = node.instrs.empty() ? node.end : node.instrs[node.instrs.size() - 1].addr + Decode(LPVOID(node.instrs[node.instrs.size() - 1].data)).Length;
		ranges.push_back(std::make_pair(start, end));
	}

	std::vector<std::pair<INSTRUX, ND_UINT64>> block;
	for (const auto& range : ranges) {
		uintptr_t codeSize = range.second - range.first;
		LPVOID processMemory = BridgeAlloc(codeSize);
		if (!DbgMemRead(range.first, processMemory, codeSize))
		{
			BridgeFree(processMemory);
		}
		else {
			for (unsigned pos = 0; pos < codeSize;) {
				INSTRUX ix = Decode(LPVOID(uintptr_t(processMemory) + pos));
				block.push_back(std::make_pair(ix, range.first + pos));
				pos += ix.Length;
			}
		}
		BridgeFree(processMemory);
	}

	Asm2Llvm asm2llvm;

	switch (entry) {
	case MenuEntries::ASM2LLVM_VCPU_OPT:
	case MenuEntries::ASM2LLVM_VCPU_NO_OPT:
	case MenuEntries::ASM2LLVM_NATIVE_OPT:
	case MenuEntries::ASM2LLVM_NATIVE_NO_OPT:
	{
		Options options;
		options.optimize = (entry == MenuEntries::ASM2LLVM_VCPU_OPT || entry == MenuEntries::ASM2LLVM_NATIVE_OPT) ? true : false;
		options.virtual_cpu = (entry == MenuEntries::ASM2LLVM_VCPU_OPT || entry == MenuEntries::ASM2LLVM_VCPU_NO_OPT) ? true : false;
		options.messagebox = true;
		std::string ir = asm2llvm.Asm2LLVM(block, options);
		_plugin_logprintf("[" PLUGIN_NAME "]\n%s\n", ir.c_str());
	} break;

	case MenuEntries::ASSEMBLY:
	{
		Options options;
		options.optimize = true;
		options.virtual_cpu = false;
		options.a2l_asm = true;
		options.messagebox = true;
		std::string ir = asm2llvm.Asm2LLVM(block, options);
		_plugin_logprintf("[" PLUGIN_NAME "]\n%s\n", ir.c_str());
	} break;

	case MenuEntries::REGISTERS:
	{
		_plugin_logprintf("[" PLUGIN_NAME "]\n");
		std::map<cpu_reg, uintptr_t> mreg = asm2llvm.GetRegValue(block);
		for (const auto& m : mreg) {
			_plugin_logprintf("%s = %016llx\n", reg_map()[m.first].c_str(), m.second);
		}
 	} break;
	}
}

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	TranslateBlock(MenuEntries(info->hEntry));
}