
#include <wcl/core/Frame.hpp>

#include <map>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//--------------------------------------
// Frame::Impl interface declaration
//--------------------------------------
namespace wcl::core {
    struct Frame::Impl {
    public:
        std::wstring mCreationTitle;
        const wchar_t *mClassName = L"Frame";
        HWND mHandle = nullptr;
        std::vector<std::unique_ptr<Control>> mChildControls;

        int mControlsCreated = 10000;
        std::map<HWND, Control*> mHandleControlMap;
        std::map<int, Control*> mIdControlMap;

    public:
        static std::map<HWND, Frame*> sFrameMap;

    public:
        static LRESULT WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        void registerClass();
    };
}
