#include "bddisasm/inc/bddisasm.h"
#include <string>
#include <vector>

struct Options {
	bool optimize = false;
	bool save_assembly = false;
	bool save_bitcode = false;
	bool save_main = false;
};

class Asm2Llvm {
public:
	__declspec(dllexport) std::string Asm2LlvmFnc(std::vector<std::pair<INSTRUX, ND_UINT64>> block, struct Options options = Options());
	__declspec(dllexport) std::vector<uint64_t> Emulate(INSTRUX ix, ND_UINT64 ip, std::vector<uint64_t> ctx, bool print_ir = false);
};