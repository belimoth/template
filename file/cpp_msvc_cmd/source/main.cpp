#define STRICT
#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment( lib, "user32.lib" )
#pragma comment( linker, "-entry:mainCRTStartup" )

int main() {
	MessageBox( 0, "Hello, World!", "", MB_OK );
	return 0;
}
