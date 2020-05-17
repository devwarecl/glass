
#pragma once

#include <map>
#include <optional>
#include <typeinfo>
#include <vector>
#include <functional>
#include "Window.hpp"

namespace glass {
    template<typename WindowImpl>
    inline constexpr char const * computeClassName() {
        return typeid(WindowImpl).name();
    }


    template<UINT Message>
    class MessageHandler {};


    template<>
    class MessageHandler<WM_CREATE> {
    public:

    };


    template<typename DerivedWindow>
    class CustomWindow : public Window {
    public:
        typedef CustomWindow<DerivedWindow> Base;

    public:
        static std::string getClassName() {
            return computeClassName<DerivedWindow>();
        }

        CustomWindow() : Window(getClassName(), WS_OVERLAPPEDWINDOW, NULL) {}

        virtual ~CustomWindow() {}

        static LRESULT WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
            if (Msg == WM_CREATE) {
                auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
                auto customWindow = reinterpret_cast< CustomWindow<DerivedWindow>* >(cs->lpCreateParams);

                assert(customWindow);

                customWindow->hWnd = hWnd;
                hWndWindowMap.insert({hWnd, customWindow});
            }
            
            if (auto it = hWndWindowMap.find(hWnd); it != hWndWindowMap.end()) {
                auto customWindow = it->second;
                assert(customWindow);

                if (auto result = customWindow->procedure(Msg, wParam, lParam); result.has_value()) {
                    return result.value();
                }
            }
            
            if (Msg == WM_DESTROY) {
                auto it = hWndWindowMap.find(hWnd); 
                assert(it != hWndWindowMap.end());

                auto customWindow = it->second;
                assert(customWindow);

                hWndWindowMap.erase(hWnd);
                customWindow->hWnd = NULL;
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }

    private:
        static std::map<HWND, CustomWindow<DerivedWindow>*> hWndWindowMap;

    protected:
        virtual std::optional<LRESULT> procedure(UINT Msg, WPARAM wParam, LPARAM lParam) {
            assert(hWnd);

            switch (Msg) {
            case WM_CREATE: this->onCreate(); break;
            case WM_DESTROY: this->onDestroy(); break;
            }

            return {};
        }

        virtual void onCreate() {}

        virtual void onDestroy() {}
    };

    template<class DerivedWindow>
    std::map<HWND, CustomWindow<DerivedWindow>*> CustomWindow<DerivedWindow>::hWndWindowMap;
}
