#include "bddisasm/inc/bddisasm.h"
#include <asmjit/asmjit.h>
#include <string>
#include <vector>
#include <map>

struct Options {
	bool optimize		= false;
	bool save_assembly	= false;
	bool save_bitcode	= false;
	bool save_main		= false;
	bool virtual_cpu	= true;
	bool a2l_asm		= false;
	bool native_stack	= false;
	bool messagebox		= false;
};

struct AsmJitOptions {
	bool print_ir		= false;
	bool messagebox		= false;
};

enum cpu_reg { cRAX, cRCX, cRDX, cRBX, cRSP, cRBP, cRSI, cRDI, cR8, cR9, cR10, cR11, cR12, cR13, cR14, cR15, cRFLAGS };

class Asm2Llvm {
public:
	__declspec(dllexport) std::string Asm2LLVM(std::vector<std::pair<INSTRUX, ND_UINT64>> block, struct Options options = Options());
	__declspec(dllexport) std::map<cpu_reg, uintptr_t> GetRegValue(std::vector<std::pair<INSTRUX, ND_UINT64>> block);
	__declspec(dllexport) std::vector<uint64_t> Emulate(INSTRUX ix, ND_UINT64 ip, std::vector<uint64_t> ctx, bool print_ir = false);
	__declspec(dllexport) std::pair<uint8_t*, size_t> AsmJit(std::vector<std::pair<INSTRUX, ND_UINT64>> block, struct AsmJitOptions jit_options = AsmJitOptions());
};