#pragma once
#include "../bddisasm/inc/bddisasm.h"
#include <string>
#include <vector>
#include <map>

enum VCPU {
	evcpu,
	ecpu,
	eargs
};

struct Options {
	bool optimize		= false;

	bool save_assembly	= false;
	bool save_bitcode	= false;
	bool save_main		= false;

	VCPU virtual_cpu    = evcpu;
	bool native_stack	= false;

	bool test_instr     = false;
	bool flag_optimize  = true;
	bool dump_obj       = false;

	bool messagebox		= false;
};

enum cpu_reg { cRAX, cRCX, cRDX, cRBX, cRSP, cRBP, cRSI, cRDI, cR8, cR9, cR10, cR11, cR12, cR13, cR14, cR15, cRFLAGS };

class Asm2Llvm {
public:
	__declspec(dllexport) std::string Asm2LLVM(std::vector<std::pair<INSTRUX, ND_UINT64>> block, struct Options options = Options());
	__declspec(dllexport) std::map<cpu_reg, uintptr_t> GetRegValue(std::vector<std::pair<INSTRUX, ND_UINT64>> block);
	__declspec(dllexport) std::vector<uint64_t> Emulate(INSTRUX ix, ND_UINT64 ip, std::vector<uint64_t> ctx, bool print_ir = false);
	__declspec(dllexport) std::string LLVM2MIR(std::string IR);
	__declspec(dllexport) std::pair<std::string, std::pair<unsigned char*, uint64_t>> MIRCompile(std::string MIR, struct Options options = Options());
};