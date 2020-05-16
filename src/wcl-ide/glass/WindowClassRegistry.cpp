
#include "WindowClassRegistry.hpp"

namespace glass {
    Registry::~Registry() {
        for (const std::string &className : classNames) {
            ::UnregisterClassA(className.c_str(), ::GetModuleHandle(NULL));
        }
    }

    void Registry::add(const char *className, WNDPROC wndProc) {
        WNDCLASSEX wcex = {};

        wcex.lpszClassName  = className;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc    = wndProc;
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
        wcex.lpszMenuName   = NULL;
        wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        ::RegisterClassEx(&wcex);
        classNames.insert(wcex.lpszClassName);
    }
}
