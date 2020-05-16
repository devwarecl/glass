
#include <glass/core.hpp>

using namespace glass;

class Form1 : public glass::CustomWindow<Form1> {
public:
    explicit Form1() {
        /*
        this->connect<WM_CREATE>( [this](){
            helloButton.create(this, "Hello", Rect{10, 60, 120, 40});
            helloButton.setVisible(true);

            helloLabel.create(this, "This is the push button", Rect{10, 10, 120, 40});
            helloLabel.setVisible(true);
        });

        this->connect(WM_CLOSE)( [this]() {
            this->postMessage(WM_QUIT, 0, 0);
        });
        */
    }

protected:
    std::optional<LRESULT> procedure(UINT Msg, WPARAM wParam, LPARAM lParam) override {
        switch (Msg) {
        case WM_CREATE:
            helloButton.create(this, "Hello", Rect{10, 60, 120, 40});
            helloButton.setVisible(true);

            helloLabel.create(this, "This is the push button", Rect{10, 10, 120, 40});
            helloLabel.setVisible(true);

            break;

        case WM_CLOSE:
            this->postMessage(WM_QUIT, 0, 0);
            break;
        }

        return Base::procedure(Msg, wParam, lParam);
    }

private:
    Button helloButton;
    Label helloLabel;
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    Registry registry;
    registry.add<Form1>();

    Form1 form1;
    form1.create({}, "Form1", Rect{CW_USEDEFAULT, CW_USEDEFAULT, 800, 600});
    form1.setVisible(true);

    MessageLoop loop;

    return loop.run();
}
