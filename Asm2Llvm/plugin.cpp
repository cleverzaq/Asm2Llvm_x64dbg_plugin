#include "plugin.h"
#include "Asm2LLvm.h"

enum class MenuEntries {
	ASM2LLVM,
};

bool Begin(int argc, char** argv) {
	return true;
}

#define COMMAND_BEGIN "Asm2LLVM"

bool pluginInit(PLUG_INITSTRUCT* initStruct) {
	_plugin_registercommand(pluginHandle, COMMAND_BEGIN, Begin, true);
	return true;
}

void pluginStop() {}

void pluginSetup() {
	_plugin_menuaddentry(hMenuGraph, int(MenuEntries::ASM2LLVM), "&LLVM IR");
	_plugin_menuentrysethotkey(pluginHandle, int(MenuEntries::ASM2LLVM), "T");
}

#define CHECK(BOOLVAR, IFTRUE, ELSE)	((BOOLVAR) == true ? (IFTRUE) : (ELSE))

bool Is64Bit()
{
#ifdef _WIN64
	return true;
#else
	return false;
#endif
}

#ifdef _WIN64
#pragma comment(lib, "Asm2Llvm_x64.lib")
#else
#pragma comment(lib, "Asm2Llvm_Win32.lib")
#endif

INSTRUX Decode(LPVOID addr)
{
	INSTRUX ix;
	NdDecodeEx(&ix, (uint8_t*)addr, ND_MIN_BUF_SIZE, CHECK(!Is64Bit(), ND_CODE_32, ND_CODE_64), CHECK(!Is64Bit(), ND_DATA_32, ND_DATA_64));
	return ix;
}

void GetBlockAndConvert()
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
	Options options;
	options.optimize = true;
	std::string	ir = asm2llvm.Asm2LlvmFnc(block, options);
	_plugin_logprintf("[" PLUGIN_NAME "]\n%s\n", ir.c_str());
}

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info) {
	switch((MenuEntries)info->hEntry) {
	case MenuEntries::ASM2LLVM:
		GetBlockAndConvert();
		return;
	}
}
