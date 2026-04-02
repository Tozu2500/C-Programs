#include "../include/ui.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleTitleA("LRU Cache Demo");
    SetConsoleOutputCP(CP_UTF8);
#endif
    runMainLoop();
    return 0;
}
