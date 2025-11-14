#pragma once

#define STRICT
#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment( lib, "user32.lib" )
#pragma comment( linker, "-entry:mainCRTStartup" )
