#pragma once

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

#define PLUG_EXPORT extern "C" __declspec(dllexport)

//superglobal variables
extern int pluginHandle;
extern HWND hwndDlg;
extern int hMenu;
extern int hMenuDisasm;
extern int hMenuDump;
extern int hMenuStack;
extern int hMenuGraph;
extern int hMenuMemmap;
extern int hMenuSymmod;
