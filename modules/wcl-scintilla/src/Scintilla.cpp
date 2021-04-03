
#include <wcl/sci/Scintilla.h>


namespace wcl::sci {
    /*
    Scintilla::Scintilla() : Window(L"Scintilla") {}

    /*
    void Scintilla::PreCreate(CREATESTRUCT &cs) {
        cs.style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN;
        cs.lpszClass = "Scintilla";
    }
    
    void Scintilla::SetStyle(int style, COLORREF fore, COLORREF back, int size, const char *face) {
        this->SendMessage_(SCI_STYLESETFORE, style, fore);
        this->SendMessage_(SCI_STYLESETBACK, style, back);

        if (size >= 1) {
            SendMessage_(SCI_STYLESETSIZE, style, size);
        }
        
        if (face) {
            SendMessage_(SCI_STYLESETFONT, style, face);
        }
    }
    
    void Scintilla::SetStyle(const ScintillaStyle &style) {
        const char *face = nullptr;

        if (style.face != "") {
            face = style.face.c_str();
        }

        this->SetStyle(style.style, style.fore, style.back, style.size, face);
    }

    /*
    void Scintilla::OnInitialUpdate() {
        this->SetAStyle(STYLE_DEFAULT, black, white, 10, "Courier New");
        this->SendEditor(SCI_STYLECLEARALL);

        this->SendEditor(SCI_SETLEXER, SCLEX_CPP);
        this->SendEditor(SCI_SETSTYLEBITS, 7);
        this->SendEditor(SCI_SETKEYWORDS, 0, (LPARAM)(cpp_keywords));
        
        this->SetAStyle(SCE_C_DEFAULT, black, white, 10, "Courier New");

        std::map<int, COLORREF> colors = {
            {SCE_C_COMMENT, RGB(0x00, 0x80, 0x00)}, 
            {SCE_C_COMMENTLINE, RGB(0x00, 0x80, 0x00)}, 
            {SCE_C_COMMENTDOC, RGB(0x00, 0x80, 0x00)}, 
            {SCE_C_NUMBER, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_WORD, RGB(0x00, 0x00, 0xFF)}, 
            {SCE_C_STRING, RGB(0x80, 0x00, 0x00)}, 
            {SCE_C_CHARACTER, RGB(0x80, 0x00, 0x00)}, 
            {SCE_C_UUID, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_PREPROCESSOR, RGB(0xA0, 0x00, 0xFF)}, 
            {SCE_C_OPERATOR, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_IDENTIFIER, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_STRINGEOL, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_VERBATIM, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_REGEX, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_COMMENTLINEDOC, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_WORD2, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_COMMENTDOCKEYWORD, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_COMMENTDOCKEYWORDERROR, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_GLOBALCLASS, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_STRINGRAW, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_TRIPLEVERBATIM, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_HASHQUOTEDSTRING, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_PREPROCESSORCOMMENT, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_PREPROCESSORCOMMENTDOC, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_USERLITERAL, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_TASKMARKER, RGB(0x00, 0x00, 0x00)}, 
            {SCE_C_ESCAPESEQUENCE, RGB(0x00, 0x00, 0x00)}
        };

        for (auto styleIt=colors.begin(); styleIt!=colors.end(); styleIt++) {
            this->SetAStyle(styleIt->first, styleIt->second);
        }

        this->SendEditor(SCI_STYLESETBOLD, SCE_C_WORD, 1);
        this->SendEditor(SCI_STYLESETBOLD, SCE_C_WORD2, 1);
    }

    void Scintilla::SetText(const std::string &text) {
        this->SendMessage_(SCI_SETTEXT, 0, (LPARAM)text.c_str());
    }

    std::string Scintilla::GetText() const {
        std::string content;
        const int length = this->SendMessage_(SCI_GETTEXTLENGTH) + 1;
        content.resize(length);
        this->SendMessage_(SCI_GETTEXT, length, (LPARAM)content.c_str());

        return content;
    }
    
    void Scintilla::SetSavePoint() {
        this->SendMessage_(SCI_SETSAVEPOINT);
    }

    void Scintilla::EmptyUndoBuffer() {
        this->SendMessage_(SCI_EMPTYUNDOBUFFER);
    }

    void Scintilla::ClearAll() { 
        this->SendMessage_(SCI_CLEARALL);
    }

    void Scintilla::SetFont(const std::string &name, const int size) {

    }

    void Scintilla::SetTabWidth(const int spaces) {
        this->SendMessage_(SCI_SETUSETABS, 0);
        this->SendMessage_(SCI_SETTABWIDTH, spaces);
    }

    void Scintilla::Undo() {
    }
    
    void Scintilla::Redo() {

    }

    void Scintilla::Cut() {

    }
    
    void Scintilla::Copy() {
    }

    void Scintilla::Paste() {

    }

    void Scintilla::SetMarginType(const int margin, const int type) {
        this->SendMessage_(SCI_SETMARGINTYPEN, margin, type);
    }
    
    void Scintilla::SetMarginWidth(const int margin, const int pixelWidth) {
        this->SendMessage_(SCI_SETMARGINWIDTHN, margin, pixelWidth);
    }

    int Scintilla::TextWidth(const int style, const std::string &text) {
        return this->SendMessage_(SCI_TEXTWIDTH, style, text.c_str());
    }

    void Scintilla::ApplyConfig(const ScintillaConfig &config) {
    this->SendMessage_(SCI_SETLEXER, config.lexer);
    this->SendMessage_(SCI_SETSTYLEBITS, config.styleBits);
    this->SendMessage_(SCI_SETKEYWORDS, 0, (LPARAM)(config.keywords.c_str()));
    this->SendMessage_(SCI_SETUSETABS, config.useTabs?1:0);
    this->SendMessage_(SCI_SETTABWIDTH, config.tabWidth);

    for (const auto &style : config.styles) {
            this->SetStyle(style);
    }

    for (const auto &pair : config.colors) {
            this->SetStyle(pair.first, pair.second);
    }
    }
    */
}
