
#include <initializer_list>

#include <wcl/core.hpp>

using wcl::core::Application;
using wcl::core::Frame;
using wcl::core::Label;
using wcl::core::Button;
using wcl::core::Edit;
using wcl::core::Rect;
using wcl::core::Control;

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

        getMenuBar()->addMenu(L"&File");
        getMenuBar()->addMenu(L"&Edit");
        getMenuBar()->addMenu(L"&Compile");
        getMenuBar()->addMenu(L"&Help");
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
