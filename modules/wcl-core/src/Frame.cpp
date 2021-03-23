
#include <wcl/core/Frame.hpp>

#include <wcl/core/Control.hpp>

#include "Frame.Impl.hpp"
#include "Control.Impl.hpp"


namespace wcl::core {
    Frame::Frame(const std::wstring &title) : mImpl(new Frame::Impl) {
        mImpl->mCreationTitle = title;
    }


    Frame::~Frame() {}


    void Frame::create() {
        mImpl->registerClass();

        mImpl->mHandle = ::CreateWindowExW(
            NULL, mImpl->mClassName,  mImpl->mCreationTitle.c_str(),  WS_OVERLAPPEDWINDOW, 
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, 
            NULL, NULL,
            ::GetModuleHandle(NULL),
            this
        );

        assert(mImpl->mHandle);
        assert(::IsWindow(mImpl->mHandle));

        ::SendMessage(mImpl->mHandle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        // create the child controls
        for (const auto &controlPtr : mImpl->mChildControls) {
            HWND hChildWnd = nullptr;

            const auto className = controlPtr->mImpl->mClassName.c_str();
            const auto text = controlPtr->mImpl->mCreationText.c_str();
            const DWORD style = WS_CHILD | WS_VISIBLE;
            const HMODULE hModule = ::GetModuleHandle(NULL);
            const int id = mImpl->mControlsCreated;
            const HWND hWndParent = mImpl->mHandle;

            if (controlPtr->mImpl->mCreationAreaOpt) {
                const auto &area = controlPtr->mImpl->mCreationAreaOpt.value();

                const int x1 = area.left;
                const int y1 = area.top;

                const int x2 = x1 + area.width;
                const int y2 = y1 + area.height;

                hChildWnd = ::CreateWindow(className, text, style, area.left, area.top, area.width, area.height, hWndParent, (HMENU)id, hModule, NULL);
            } else {
                hChildWnd = ::CreateWindow(className, text, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, (HMENU)id, hModule, NULL);
            }

            assert(hChildWnd);

            ::SendMessage(hChildWnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

            controlPtr->mImpl->mHandle = hChildWnd;
            controlPtr->mImpl->mId = id;

            mImpl->mHandleControlMap[hChildWnd] = controlPtr.get();
            mImpl->mIdControlMap[id] = controlPtr.get();
        }
    }


    void Frame::show() {
        assert(mImpl->mHandle);

        ::ShowWindow(mImpl->mHandle, SW_SHOW);
    }


    void Frame::hide() {
        assert(mImpl->mHandle);

        ::ShowWindow(mImpl->mHandle, SW_HIDE);
    }


    void Frame::setVisible(const bool visible) {
        assert(mImpl->mHandle);

        if (visible) {
            show();
        } else {
            hide();
        }
    }


    bool Frame::isVisible() const {
        assert(mImpl->mHandle);

        if (::IsWindowVisible(mImpl->mHandle)) {
            return true;
        }

        return false;
    }


    void Frame::addChildImpl(Control *control) {
        mImpl->mChildControls.emplace_back(control);
        mImpl->mControlsCreated ++;
    }


    void Frame::connectClick(Control *control, std::function<void()> func) {
        control->clickEvent.push_back(func);
    }
}
