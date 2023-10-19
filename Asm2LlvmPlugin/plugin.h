#pragma once

#include "pluginmain.h"

#define PLUGIN_NAME_A2L "Asm2Llvm"
#define PLUGIN_NAME_L2A "Llvm2Asm"
#define PLUGIN_VERSION 1

bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();

#ifdef _WIN64
#define DUINT_FMT "0x%016llX"
#else
#define DUINT_FMT "0x%016lX"
#endif