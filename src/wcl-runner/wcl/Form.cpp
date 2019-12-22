
#include "Form.hpp"
#include "private/Window.hpp"

namespace wcl {
    inline RECT convertToRECT(const Rect &rect) {
        return { rect.left, rect.top, rect.right, rect.bottom };
    }


    inline Rect convertToRect(const RECT &rect) {
        return { rect.left, rect.top, rect.right, rect.bottom };
    }


    struct Form::Private {
        Window window;

        Private() {

        }

        ~Private() {
            if (window) {
                window.Destroy();
            }
        }

        LRESULT HandleMessage(const int Msg, LPARAM lParam, WPARAM wParam) {
            return DefWindowProc(window.hWnd, Msg, wParam, lParam);
        }
    };


    Form::Form() 
        : m_impl(new Form::Private()) {}


    Form::~Form() {
        delete m_impl;
    }


    void Form::setText(const std::string &value) {

    }


    std::string Form::getText() const {
        return {};
    }


    void Form::setClientRect(const Rect &clientRect) {
        const DWORD style = m_impl->window.GetLongPtr<DWORD>(GWL_STYLE);
        const DWORD exStyle = m_impl->window.GetLongPtr<DWORD>(GWL_EXSTYLE);

        RECT rect = convertToRECT(clientRect);

        ::AdjustWindowRectEx(&rect, style, FALSE, exStyle);

        m_impl->window.SetPos(NULL, rect, SWP_FRAMECHANGED);
    }


    Rect Form::getClientRect() const {
        const RECT clientRect = m_impl->window.GetClientRect();

        return convertToRect(clientRect);
    }


    std::vector<Control*> Form::getChildren() const {
        return {};
    }
}
