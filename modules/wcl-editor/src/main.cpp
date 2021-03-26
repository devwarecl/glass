
#include <wcl/core.hpp>

using wcl::core::Application;
using wcl::core::Frame;
using wcl::core::Label;
using wcl::core::Button;
using wcl::core::Edit;
using wcl::core::Rect;
using wcl::core::Control;
using wcl::core::Menu;

class EditorFrame : public Frame {
public:
    EditorFrame() : Frame(L"wcl-editor") {
        createChild<Label>(L"Enter your name:", Rect{5, 5, 400, 50});

        mNameEdit = createChild<Edit>(L"", Rect{5, 55, 400, 50});
        mHelloLabel = createChild<Label>(L"$", Rect{5, 105, 400, 50});

        mSayHelloButton = createChild<Button>(L"Say Hello", Rect{5, 155, 400, 50});

        mSayHelloButton->connect("click", [this](const std::string &, Control *) {
            this->sayHelloButtonClicked();
        });

        Menu *menu = nullptr;

        menu = getMenuBar()->addMenu(L"&File");
        menu->addItem(L"&New");
        menu->addSeparator();
        menu->addItem(L"&Open ...");
        menu->addSeparator();
        menu->addItem(L"&Save");
        menu->addItem(L"&Save As...");
        menu->addSeparator();
        menu->addItem(L"&Exit");

        menu = getMenuBar()->addMenu(L"&Edit");
        menu->addItem(L"&Undo");
        menu->addItem(L"&Redo");
        menu->addSeparator();
        menu->addItem(L"&Cut");
        menu->addItem(L"&Copy");
        menu->addItem(L"&Paste");
        menu->addSeparator();
        menu->addItem(L"&Select All");
        menu->addSeparator();
        menu->addItem(L"&Find ...");
        menu->addItem(L"&Replace ...");

        menu = getMenuBar()->addMenu(L"&Build");
        menu->addItem(L"&Clean");
        menu->addItem(L"&Build");
        menu->addItem(L"&Rebuild");

        menu = getMenuBar()->addMenu(L"&Help");
        menu->addItem(L"About ...");
    }


    void sayHelloButtonClicked() {
        std::wstring name = mNameEdit->getText();

        if (name.empty()) {
            name = L"World";
        }

        mHelloLabel->setText(L"Hello, " + name);
    }

protected:
    Label *mHelloLabel = nullptr;
    Button *mSayHelloButton = nullptr;
    Edit *mNameEdit = nullptr;
};


int main(int argc, char **argv) {
    Application app;
    EditorFrame frame1;

    frame1.create();
    frame1.show();

    return app.run();
}
