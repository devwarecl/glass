
#include <wcl/core.hpp>

using wcl::core::Application;
using wcl::core::Frame;
using wcl::core::Label;
using wcl::core::Button;
using wcl::core::Edit;
using wcl::core::Rect;
using wcl::core::Control;
using wcl::core::EventRaiser;
using wcl::core::Menu;
using wcl::core::Widget;


#include <wcl/core/WidgetPrivate.h>


class SimpleFrame : public wcl::core::Widget {
public:
    SimpleFrame() {
        registerClass();

        getImpl()->mClassName = "SimpleFrame";
        getImpl()->mStyle = WS_OVERLAPPEDWINDOW;
    }


    ~SimpleFrame() {}

private:
    static LRESULT WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
        switch (Msg) {
            case WM_CREATE: {
                auto cs = (CREATESTRUCT *)lParam;
                break;
            }

            case WM_DESTROY: {
                ::PostQuitMessage(0);

                return 0;
            }
        }

        return ::DefWindowProcW(hWnd, Msg, wParam, lParam);
    }

private:
    void registerClass() {
        WNDCLASSEX wcex = {};

        wcex.lpszClassName  = "SimpleFrame";
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc    = WindowProc;
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

protected:
    void onCreated() override {
        this->setText("This is a test!");
        this->show();
    }
};


int main(int argc, char **argv) {
    Application app;

    SimpleFrame frame;

    frame.create();

    return app.run();
}


//
//class EditorFrame : public Frame {
//public:
//    EditorFrame() : Frame(L"wcl-editor") {
//        createChild<Label>(L"Enter your name:", Rect{5, 5, 400, 50});
//
//        mNameEdit = createChild<Edit>(L"", Rect{5, 55, 400, 50});
//        mHelloLabel = createChild<Label>(L"$", Rect{5, 105, 400, 50});
//
//        mSayHelloButton = createChild<Button>(L"Say Hello", Rect{5, 155, 400, 50});
//
//        mSayHelloButton->connect("click", [this](const std::string &, EventRaiser *) {
//            this->sayHelloButtonClicked();
//        });
//
//        Menu *menu = nullptr;
//
//        menu = getMenuBar()->addMenu(L"&File");
//        menu->addItem(L"&New")->connect("click", [this](const std::string &, EventRaiser *) {
//            this->sayHelloButtonClicked();
//        });
//
//        menu->addSeparator();
//        menu->addItem(L"&Open ...");
//        menu->addSeparator();
//        menu->addItem(L"&Save");
//        menu->addItem(L"&Save As...");
//        menu->addSeparator();
//        menu->addItem(L"&Exit");
//
//        menu = getMenuBar()->addMenu(L"&Edit");
//        menu->addItem(L"&Undo");
//        menu->addItem(L"&Redo");
//        menu->addSeparator();
//        menu->addItem(L"&Cut");
//        menu->addItem(L"&Copy");
//        menu->addItem(L"&Paste");
//        menu->addSeparator();
//        menu->addItem(L"&Select All");
//        menu->addSeparator();
//        menu->addItem(L"&Find ...");
//        menu->addItem(L"&Replace ...");
//
//        menu = getMenuBar()->addMenu(L"&Build");
//        menu->addItem(L"&Clean");
//        menu->addItem(L"&Build");
//        menu->addItem(L"&Rebuild");
//
//        menu = getMenuBar()->addMenu(L"&Help");
//        menu->addItem(L"About ...");
//    }
//
//
//    void sayHelloButtonClicked() {
//        std::wstring name = mNameEdit->getText();
//
//        if (name.empty()) {
//            name = L"World";
//        }
//
//        mHelloLabel->setText(L"Hello, " + name);
//    }
//
//protected:
//    Label *mHelloLabel = nullptr;
//    Button *mSayHelloButton = nullptr;
//    Edit *mNameEdit = nullptr;
//};
//
//
//int main(int argc, char **argv) {
//    Application app;
//
//    EditorFrame frame1;
//    frame1.show();
//
//    return app.run();
//}
