
#include "Frame.Impl.hpp"

#include <wcl/core/Control.hpp>

namespace wcl::core {
    std::map<HWND, Frame*> Frame::Impl::sFrameMap;


    LRESULT Frame::Impl::WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
        switch (Msg) {
            case WM_CREATE: {
                auto cs = (CREATESTRUCT *)lParam;
                Frame::Impl::sFrameMap[hWnd] = reinterpret_cast<Frame*>(cs->lpCreateParams);
                break;
            }

            case WM_DESTROY: {
                ::PostQuitMessage(0);
                Frame::Impl::sFrameMap.erase(hWnd);

                return 0;
            }

            case WM_COMMAND: {
                auto frame = Frame::Impl::sFrameMap[hWnd];

                auto hWndButton = reinterpret_cast<HWND>(lParam);
                auto button = frame->mImpl->mHandleControlMap[hWndButton];

                for (auto &func : button->clickEvent) {
                    func();
                }

                return 0;
            }
        }

        return ::DefWindowProcW(hWnd, Msg, wParam, lParam);
    }


    void Frame::Impl::registerClass() {
        WNDCLASSEX wcex = {};

        wcex.lpszClassName  = mClassName;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc    = &Frame::Impl::WindowProc;
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
        wcex.lpszMenuName   = NULL;
        wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        assert(::RegisterClassEx(&wcex));
    }
}
