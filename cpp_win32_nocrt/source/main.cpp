#include "windows.h"

int main() {
    char msg[] = "Hello, World!\n";
    HANDLE stdout = GetStdHandle( STD_OUTPUT_HANDLE );
    WriteFile( stdout, msg, sizeof(msg), 0, 0 );
    return 0;
}
