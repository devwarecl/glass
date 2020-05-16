
/* glass: A Modern interface to Classic Windows UI */

#pragma once 

#include <Windows.h>

#include <typeinfo>
#include <vector>
#include <set>
#include <string>
#include <cassert>
#include <map>
#include <optional>

namespace glass {
    struct Rect {
        int left, top;
        int width, height;
    };

    typedef long Handle;

    class AbstractWindow {
    public:
        virtual ~AbstractWindow() {}

        virtual void setVisible(const bool value) = 0;

        virtual bool isVisible() const = 0;

        virtual void setText(const std::string &value) = 0;

        virtual std::string getText() const = 0;

        virtual HWND getHandle() const = 0;

        virtual void setRect(const Rect &value) = 0;

        virtual Rect getRect() const = 0;

        virtual void setClientArea(const Rect &value) = 0;

        virtual Rect getClientArea() const = 0;
    };
    

    class Window : public AbstractWindow {
    public:
        explicit Window(const std::string className, const DWORD dwStyle, const DWORD dwExStyle);

        void create(Window *parent, const std::string &text, const Rect &rect);

        bool isCreated() const {
            return hWnd != NULL;
        }

        void setVisible(const bool value) override;

        bool isVisible() const override;

        void setText(const std::string &value) override;

        std::string getText() const override;

        HWND getHandle() const override;

        void setRect(const Rect &value) override;

        Rect getRect() const override;

        void setClientArea(const Rect &value) override;

        Rect getClientArea() const override;


    protected:
        LONG_PTR getLongPtr(int nIndex) const {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::GetWindowLongPtr(hWnd, nIndex);
        }

        LONG_PTR getLongPtr(int nIndex, LONG_PTR longPtr) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SetWindowLongPtr(hWnd, nIndex, longPtr);
        }

        LRESULT sendMessage(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }

        LRESULT sendMessage(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L) const {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }

        LRESULT postMessage(UINT Msg, WPARAM wParam, LPARAM lParam) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::PostMessage(hWnd, Msg, wParam, lParam);
        }

    protected:
        HWND hWnd = NULL;
        const std::string className;
        const DWORD dwStyle;
        const DWORD dwExStyle;
    };


    template<typename WindowImpl>
    inline constexpr char const * computeClassName() {
        return typeid(WindowImpl).name();
    }


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
            switch (Msg) {
                case WM_CREATE: {
                    auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
                    auto customWindow = reinterpret_cast< CustomWindow<DerivedWindow>* >(cs->lpCreateParams);

                    assert(customWindow);

                    customWindow->hWnd = hWnd;
                    hWndWindowMap.insert({hWnd, customWindow});

                    break;
                }
                
                case WM_DESTROY: {
                    auto it = hWndWindowMap.find(hWnd); 
                    assert(it != hWndWindowMap.end());

                    auto customWindow = it->second;
                    assert(customWindow);

                    hWndWindowMap.erase(hWnd);
                    customWindow->hWnd = NULL;

                    break;
                }
            }

            if (auto it = hWndWindowMap.find(hWnd); it != hWndWindowMap.end()) {
                auto customWindow = it->second;
                assert(customWindow);

                if (auto result = customWindow->procedure(Msg, wParam, lParam); result.has_value()) {
                    return result.value();
                }
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }

    private:
        static std::map<HWND, CustomWindow<DerivedWindow>*> hWndWindowMap;

    protected:
        virtual std::optional<LRESULT> procedure(UINT Msg, WPARAM wParam, LPARAM lParam) {
            assert(hWnd);

            return {};
        }
    };

    template<class DerivedWindow>
    std::map<HWND, CustomWindow<DerivedWindow>*> CustomWindow<DerivedWindow>::hWndWindowMap;

    class Registry {
    public:
        ~Registry();

        void add(const char *className, WNDPROC wndProc);
        
        template<typename DerivedWindow>
        void add() {
            this->add(computeClassName<DerivedWindow>(), &DerivedWindow::WindowProc);
        }

    private:
        std::set<std::string> classNames;
    };


    class Button : public Window {
    public:
        Button();
    };


    class Label : public Window {
    public:
        Label() : Window("STATIC", WS_CHILD, NULL) {}
    };


    class MessageLoop {
    public:
        int run();
    };
}
