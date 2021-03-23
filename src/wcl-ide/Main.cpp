
#define UNICODE

#include <glass/core.hpp>

using namespace glass;

class Form1 : public glass::CustomWindow<Form1> {
public:
    explicit Form1() {}

protected:
    void onCreate() override {
        findReplaceGroupBox.create(this, Rect{10, 10, 270, 80}, "Find/Replace parameters");
        findWhatLabel.create(this, Rect{30, 30, 100, 20}, "Find what");
        findWhatEdit.create(this, Rect{150, 30, 100, 20}, "");
        replaceWithCheckBox.create(this, Rect{30, 55, 100, 20}, "Replace with");
        replaceWithEdit.create(this, Rect{150, 55, 100, 20}, "");

        matchGroupBox.create(this, Rect{10, 100, 270, 80}, "Match options");
        matchCaseCheckBox.create(this, Rect{30, 125, 125, 20}, "Match case");
        matchWholeWordCheckBox.create(this, Rect{30, 145, 125, 20}, "Match whole word");

        scopeGroupBox.create(this, Rect{10, 190, 270, 80}, "Scope");
        scopeSelectionRadio.create(this, Rect{30, 210, 125, 20}, "Selection");
        scopeCurrentDocumentRadio.create(this, Rect{30, 230, 125, 20}, "Current Document");

        findNextButton.create(this, Rect{10, 280, 120, 30}, "Find Next");
        closeButton.create(this, Rect{140, 280, 120, 30}, "Close");
        replaceNextButton.create(this, Rect{10, 320, 120, 30}, "Replace Next");
        replaceAllButton.create(this, Rect{140, 320, 120, 30}, "Replace Al");
    }

    void onDestroy() override {
        this->postMessage(WM_QUIT, 0, 0);
    }

private:
    GroupBox findReplaceGroupBox;
    Label findWhatLabel;
    TextBox findWhatEdit;
    CheckBox replaceWithCheckBox;
    TextBox replaceWithEdit;

    GroupBox matchGroupBox;
    CheckBox matchCaseCheckBox;
    CheckBox matchWholeWordCheckBox;

    GroupBox scopeGroupBox;
    RadioButton scopeSelectionRadio;
    RadioButton scopeCurrentDocumentRadio;

    Button findNextButton;
    Button closeButton;
    Button replaceNextButton;
    Button replaceAllButton;
};


int main() {
    ::SetProcessDPIAware();

    Registry registry;
    registry.add<Form1>();

    Form1 form1;
    form1.create({}, "Form1", Rect{CW_USEDEFAULT, CW_USEDEFAULT, 800, 600});
    form1.setVisible(true);

    MessageLoop loop;

    return loop.run();
}
