#include "plugin.h"
#include "..\bddisasm\inc\bddisasm.h"
#include "..\Asm2Llvm\Asm2Llvm.h"
#include "QtPlugin.h"
#include <algorithm>

enum class MenuEntries {
	ASM2LLVM_VCPU_OPT,
	ASM2LLVM_VCPU_NO_OPT,
	ASM2LLVM_CPU_OPT,
	ASM2LLVM_CPU_NO_OPT,
	ASM2LLVM_ARG_OPT,
	ASM2LLVM_ARG_NO_OPT,
	IR2MIR_NO_OPT,
	IR2MIR_OPT,
	ASSEMBLY_OPT,
	ASSEMBLY_NO_OPT,
	ASSEMBLY_WRITE_OPT,
	ASSEMBLY_WRITE_NO_OPT,
	DISASSEMBLY,
	REGISTERS,
};

bool Begin(int argc, char** argv)
{
	return true;
}

bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	QtPlugin::Init();
	_plugin_registercommand(pluginHandle, "Asm2LLVM", Begin, true);
	return true;
}

void pluginStop()
{
	GuiExecuteOnGuiThread(QtPlugin::Stop);
	QtPlugin::WaitForStop();
}

void pluginSetup()
{
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_VCPU_OPT),       "&LLVM IR VCPU - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_VCPU_NO_OPT),    "&LLVM IR VCPU - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_CPU_OPT),        "&LLVM IR CPU - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_CPU_NO_OPT),     "&LLVM IR CPU - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_ARG_OPT),        "&LLVM IR ARG - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM_ARG_NO_OPT),     "&LLVM IR ARG - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::IR2MIR_NO_OPT),           "&LLVM MIR - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::IR2MIR_OPT),              "&LLVM MIR - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASSEMBLY_OPT),            "&Assembly - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASSEMBLY_NO_OPT),         "&Assembly - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASSEMBLY_WRITE_OPT),      "&Assemble Memory - Optimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASSEMBLY_WRITE_NO_OPT),   "&Assemble Memory - Unoptimized");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::DISASSEMBLY),             "&Disassembly");
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::REGISTERS),               "&Registers");

	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASM2LLVM_CPU_OPT),   "1");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::IR2MIR_NO_OPT),      "2");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASSEMBLY_OPT),       "3");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASSEMBLY_WRITE_OPT), "4");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::DISASSEMBLY),        "5");

	GuiExecuteOnGuiThread(QtPlugin::Setup);
	QtPlugin::WaitForSetup();
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
		uintptr_t end = node.instrs.empty() ? node.end : node.instrs[node.instrs.size() - 1].addr;
		
		BASIC_INSTRUCTION_INFO info;	
		DbgDisasmFastAt(end, &info);
		end += info.size;

		ranges.push_back(std::make_pair(start, end));
	}

	std::sort(ranges.begin(), ranges.end(), [](const std::pair<uintptr_t, uintptr_t>& a, const std::pair<uintptr_t, uintptr_t>& b) {
		return a.first < b.first;
	});

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
	case MenuEntries::ASM2LLVM_CPU_OPT:
	case MenuEntries::ASM2LLVM_CPU_NO_OPT:
	case MenuEntries::ASM2LLVM_ARG_OPT:
	case MenuEntries::ASM2LLVM_ARG_NO_OPT:
	{
		Options options;
		switch (entry)
		{
		case MenuEntries::ASM2LLVM_VCPU_OPT:
		case MenuEntries::ASM2LLVM_CPU_OPT:
		case MenuEntries::ASM2LLVM_ARG_OPT:
		{
			options.optimize = true;
		} break;
		}

		switch (entry)
		{
		case MenuEntries::ASM2LLVM_VCPU_OPT:
		case MenuEntries::ASM2LLVM_VCPU_NO_OPT:
		{
			options.virtual_cpu = evcpu;
		} break;

		case MenuEntries::ASM2LLVM_CPU_OPT:
		case MenuEntries::ASM2LLVM_CPU_NO_OPT:
		{
			options.virtual_cpu = ecpu;
		} break;

		case MenuEntries::ASM2LLVM_ARG_OPT:
		case MenuEntries::ASM2LLVM_ARG_NO_OPT:
		{
			options.virtual_cpu = eargs;
		} break;
		}

		options.native_stack = true;
		options.messagebox   = true;

		QtPlugin::Clear();
		QtPlugin::Insert(asm2llvm.Asm2LLVM(block, options).c_str());
		QtPlugin::ShowTab();
	} break;

	case MenuEntries::IR2MIR_NO_OPT:
	case MenuEntries::IR2MIR_OPT:
	{
		Options options;
		switch (entry)
		{
		case MenuEntries::IR2MIR_OPT:
		{
			options.optimize = true;
		} break;

		default:
			options.optimize = false;
		}
		options.virtual_cpu  = ecpu;
		options.native_stack = true;
		options.messagebox   = true;

		std::string IR = asm2llvm.Asm2LLVM(block, options);
		std::string MIR = asm2llvm.LLVM2MIR(IR);
		std::pair<std::string, std::pair<unsigned char*, uint64_t>> CMIR = asm2llvm.MIRCompile(MIR);

		QtPlugin::Clear();
		QtPlugin::Insert(CMIR.first.c_str());
		delete[] CMIR.second.first;
		QtPlugin::ShowTab();
	} break;

	case MenuEntries::ASSEMBLY_OPT:
	case MenuEntries::ASSEMBLY_NO_OPT:
	case MenuEntries::ASSEMBLY_WRITE_OPT:
	case MenuEntries::ASSEMBLY_WRITE_NO_OPT:
	{
		Options options;
		switch (entry)
		{
		case MenuEntries::ASSEMBLY_OPT:
		case MenuEntries::ASSEMBLY_WRITE_OPT:
		{
			options.optimize = true;
		} break;

		default:
			options.optimize = false;
		}

		options.virtual_cpu  = ecpu;
		options.native_stack = true;
		options.dump_obj     = true;
		options.messagebox   = true;

		std::string IR = asm2llvm.Asm2LLVM(block, options);
		std::string MIR = asm2llvm.LLVM2MIR(IR);
		std::pair<std::string, std::pair<unsigned char*, uint64_t>> CMIR = asm2llvm.MIRCompile(MIR, options);

		if (entry == MenuEntries::ASSEMBLY_OPT || entry == MenuEntries::ASSEMBLY_NO_OPT)
		{
			QtPlugin::Clear();

			for (unsigned pos = 0; pos < CMIR.second.second;) {
				char* disasm = new char[ND_MIN_BUF_SIZE];
				INSTRUX ix = Decode(LPVOID(CMIR.second.first + pos));
				NdToText(&ix, ranges[0].first + pos, ND_MIN_BUF_SIZE, disasm);
				QtPlugin::Insert((std::string(disasm) + "\n").c_str());
				pos += ix.Length;
				delete[] disasm;
			}

			QtPlugin::ShowTab();
		}
		else if (entry == MenuEntries::ASSEMBLY_WRITE_OPT || entry == MenuEntries::ASSEMBLY_WRITE_NO_OPT)
		{
			for (unsigned iblock = 0; iblock < block.size(); iblock++) {
				ND_UINT8 size = block[iblock].first.Length;
				unsigned char* instr = new unsigned char[size];
				memset(instr, 0xcc, size);

				DbgFunctions()->MemPatch(block[iblock].second, instr, size);

				delete[] instr;
			}

			DbgFunctions()->MemPatch(ranges[0].first, CMIR.second.first, CMIR.second.second);
		}

		delete[] CMIR.second.first;
	} break;

	case MenuEntries::DISASSEMBLY:
	{
		QtPlugin::Clear();

		for (unsigned iblock = 0; iblock < block.size(); iblock++) {
			char* disasm = new char[ND_MIN_BUF_SIZE];
			NdToText(&block[iblock].first, block[iblock].second, ND_MIN_BUF_SIZE, disasm);
			QtPlugin::Insert((std::string(disasm) + "\n").c_str());
			delete[] disasm;
		}

		QtPlugin::ShowTab();
	} break;

	case MenuEntries::REGISTERS:
	{
		QtPlugin::Clear();

		std::map<cpu_reg, uintptr_t> mreg = asm2llvm.GetRegValue(block);
		for (const auto& m : mreg) {
			int bufferSize = snprintf(nullptr, 0, "%s = %016llx\n", reg_map()[m.first].c_str(), m.second);
			char* buffer = new char[bufferSize + 1];
			snprintf(buffer, bufferSize + 1, "%s = %016llx\n", reg_map()[m.first].c_str(), m.second);
			QtPlugin::Insert(buffer);
			delete[] buffer;
		}

		QtPlugin::ShowTab();
 	} break;
	}
}

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	TranslateBlock(MenuEntries(info->hEntry));
}