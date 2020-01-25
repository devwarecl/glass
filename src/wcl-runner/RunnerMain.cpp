
#include <Windows.h>

#include <string>
#include <vector>
#include <map>

#include "wcl/Rect.hpp"


namespace wcl {
    namespace def {
        enum class ControlType {
            Unknown = -1,
            label,
            button
        };


        ControlType makeControlType(const std::string &in) {
            static std::map<std::string, ControlType> controlTypeMap = {
                {"label", ControlType::label},
                {"button", ControlType::button},
            };

            auto it = controlTypeMap.find(in);
            if (it == controlTypeMap.end()) {
                return ControlType::Unknown;
            }

            return it->second;
        }


        struct ControlDef {
            ControlType type;
            Rect rect;
            std::string text;
        };


        struct FormDef {
            std::string name;
            std::vector<ControlDef> children;
        };  


        FormDef makeTestForm() {
            return FormDef {
                "Form1",
                {
                    { ControlType::label, Rect{0, 0, 150, 25}, "Hello, World" }, 
                    { ControlType::button, Rect{0, 75, 125, 100}, "Push Me 1" }
                }
            };
        }
        

        void SetupWindowMetricsFromTheme(HWND hwnd) {
            // setup a nicer font
            NONCLIENTMETRICS ncm;
            ncm.cbSize = sizeof(NONCLIENTMETRICS);
            ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
            HFONT hFont = ::CreateFontIndirect(&ncm.lfMessageFont);
            ::SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        }

        
        const char *MapClassName(const ControlType type) {
            switch (type) {
                case ControlType::label:  return "Static";
                case ControlType::button:  return "Button";
                default: return nullptr;
            }
        }


        HWND CreateWindowFromControl(HWND hHwndParent, const ControlDef &control) {
            const DWORD style = WS_CHILD | WS_VISIBLE;
            const int width = control.rect.right - control.rect.left;
            const int height = control.rect.bottom - control.rect.top;

            const char* className = MapClassName(control.type);

            if (className == nullptr) {
                return NULL;
            }

            HWND hwnd = ::CreateWindow(
                className, control.text.c_str(), style, 
                control.rect.left, control.rect.top, width, height, 
                hHwndParent, NULL, ::GetModuleHandle(NULL), 
                NULL
            );

            SetupWindowMetricsFromTheme(hwnd);

            return hwnd;
        }


        HWND CreateWindowFromForm(const FormDef &form, const char *className) {
            HWND hwnd  = ::CreateWindow(className, form.name.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, ::GetModuleHandle(NULL), NULL);

            for (const ControlDef &control : form.children) {
                CreateWindowFromControl(hwnd, control);
            }

            return hwnd;
        }
    }
}


LRESULT CALLBACK WndProc(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam) {
    switch (message) {
        case WM_COMMAND: {
            int controlId = HIWORD(wParam);
            ::MessageBox(hWnd, "Hola", "Chao", MB_OK);
            return 0;
        }
    
        case WM_CLOSE: {
            PostMessage(hWnd, WM_QUIT, 0, 0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


int main() {
    WNDCLASSEX wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = ::GetModuleHandle(NULL);
    wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = "Form1";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
       MessageBox(NULL, "Error while registring a Window Class", "wcl-runner", NULL);
       return 1;
    }

    const wcl::def::FormDef form1 = wcl::def::makeTestForm();
    HWND hwnd = wcl::def::CreateWindowFromForm(form1, "Form1");

    if (!hwnd) {
       MessageBox(NULL, "Error while creating a Window instance", "wcl-runner", NULL);
       return 1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_QUIT) {
            return 0;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}
