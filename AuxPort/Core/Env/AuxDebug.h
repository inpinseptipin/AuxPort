#ifndef AUXPORT_DEBUG_H
#define AUXPORT_DEBUG_H
#include "AuxEnv.h"
#if AUXPORT_WINDOWS
#include "Windows.h"
#include <iostream>
namespace AuxPort
{
    /**
        Instantiates a Debug Console, that can be opened with a GUI.
        This console opens up a stream to the standard-in, standard-out and standard-error which enables std::cin and std::cout
     */
    class Console
    {
    public:
        Console(const std::string& windowName)
        {
            AllocConsole();
            SetConsoleTitle(TEXT(windowName.c_str()));
            auto err = freopen("conin$", "r", stdin);
            auto err = freopen("conout$", "w", stdout);
            auto err = freopen("conout$", "w", stderr);
        }
        void clearWindow()
        {
            system("cls");
        }
        ~Console()
        {
            fclose(stdin);
            fclose(stdout);
            fclose(stderr);
            FreeConsole();
        }
    };
}
#endif
#endif
