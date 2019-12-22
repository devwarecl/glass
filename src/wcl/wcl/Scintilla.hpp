
#pragma once

#ifndef __wcl_scintilla_hpp__
#define __wcl_scintilla_hpp__

#include <string>
#include <map>
#include <Scintilla.h>
#include <SciLexer.h>
#include "Window.hpp"

namespace wcl { 

    enum ScintillaColors {
        Black = RGB(0x00, 0x00, 0x00),
        White = RGB(0xFF, 0xFF, 0xFF),
        Red = RGB(0xFF, 0x00, 0x00),
        Green = RGB(0x00, 0xFF, 0x00),
        Blue = RGB(0x00, 0x00, 0xFF)
    };
    
    struct ScintillaStyle {
        int style = 0;
        COLORREF fore;
        COLORREF back = White;
        int size = 0;
        std::string face = "";

        ScintillaStyle(int style_, COLORREF fore_) : style(style_), fore(fore_) {}
        ScintillaStyle(int style_, COLORREF fore_, COLORREF back_) : style(style_), fore(fore_), back(back_) {}
        ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_) : style(style_), fore(fore_), back(back_), size(size_) {}
        ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_, const std::string &face_) : style(style_), fore(fore_), back(back_), size(size_), face(face_) {}
    };

    struct ScintillaConfig {
        int lexer = 0;
        std::string keywords;
        std::map<int, COLORREF> colors;
        std::vector<ScintillaStyle> styles;
        int styleBits = 7;
        bool useTabs = false;
        int tabWidth = 4;
    };

    class Scintilla : public Window {
    public:
        Scintilla();
        
        void SetStyle(int style, COLORREF fore, COLORREF back=White, int size=0, const char *face=nullptr);
    
        void SetStyle(const ScintillaStyle &style);

        void SetSavePoint();
        void EmptyUndoBuffer();
        void ClearAll();
        
        void SetFont(const std::string &name, const int size);
        void SetTabWidth(const int spaces);
        
        void Undo();
        void Redo();

        void Cut();
        void Copy();
        void Paste();

        void SetText(const std::string &text);
        std::string GetText() const;

        void SetMarginType(const int margin, const int type);
        void SetMarginWidth(const int margin, const int pixelWidth);
        
        int TextWidth(const int style, const std::string &text);

        void ApplyConfig(const ScintillaConfig &config);
    };
    
    inline Scintilla::Scintilla() : Window(L"Scintilla") {}

    /*
    void Scintilla::PreCreate(CREATESTRUCT &cs) {
        cs.style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN;
        cs.lpszClass = "Scintilla";
    }
    */
    
    inline void Scintilla::SetStyle(int style, COLORREF fore, COLORREF back, int size, const char *face) {
        this->SendMessage_(SCI_STYLESETFORE, style, fore);
        this->SendMessage_(SCI_STYLESETBACK, style, back);

        if (size >= 1) {
            SendMessage_(SCI_STYLESETSIZE, style, size);
        }
        
        if (face) {
            SendMessage_(SCI_STYLESETFONT, style, face);
        }
    }
    
    inline void Scintilla::SetStyle(const ScintillaStyle &style) {
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
    */

    inline void Scintilla::SetText(const std::string &text) {
        this->SendMessage_(SCI_SETTEXT, 0, (LPARAM)text.c_str());
    }

    inline std::string Scintilla::GetText() const {
        std::string content;
        const int length = this->SendMessage_(SCI_GETTEXTLENGTH) + 1;
        content.resize(length);
        this->SendMessage_(SCI_GETTEXT, length, (LPARAM)content.c_str());

        return content;
    }
    
    inline void Scintilla::SetSavePoint() {
        this->SendMessage_(SCI_SETSAVEPOINT);
    }

    inline void Scintilla::EmptyUndoBuffer() {
        this->SendMessage_(SCI_EMPTYUNDOBUFFER);
    }

    inline void Scintilla::ClearAll() { 
        this->SendMessage_(SCI_CLEARALL);
    }

    inline void Scintilla::SetFont(const std::string &name, const int size) {

    }

    inline void Scintilla::SetTabWidth(const int spaces) {
        this->SendMessage_(SCI_SETUSETABS, 0);
        this->SendMessage_(SCI_SETTABWIDTH, spaces);
    }

    inline void Scintilla::Undo() {
    }
    
    inline void Scintilla::Redo() {

    }

    inline void Scintilla::Cut() {

    }
    
    inline void Scintilla::Copy() {
    }

    inline void Scintilla::Paste() {

    }

    inline void Scintilla::SetMarginType(const int margin, const int type) {
        this->SendMessage_(SCI_SETMARGINTYPEN, margin, type);
    }
    
    inline void Scintilla::SetMarginWidth(const int margin, const int pixelWidth) {
        this->SendMessage_(SCI_SETMARGINWIDTHN, margin, pixelWidth);
    }

    inline int Scintilla::TextWidth(const int style, const std::string &text) {
        return this->SendMessage_(SCI_TEXTWIDTH, style, text.c_str());
    }

    inline void Scintilla::ApplyConfig(const ScintillaConfig &config) {
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
}

#endif // __wcl_scintilla_hpp__
