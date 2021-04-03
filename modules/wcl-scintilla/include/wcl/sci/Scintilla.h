
#pragma once

#include <string>
#include <map>

//#include <Scintilla.h>
//#include <SciLexer.h>
//#include "Window.hpp"

#include <wcl/core/Widget.hpp>


namespace wcl::sci { 

    //enum ScintillaColors {
    //    Black = RGB(0x00, 0x00, 0x00),
    //    White = RGB(0xFF, 0xFF, 0xFF),
    //    Red = RGB(0xFF, 0x00, 0x00),
    //    Green = RGB(0x00, 0xFF, 0x00),
    //    Blue = RGB(0x00, 0x00, 0xFF)
    //};
    //
    //struct ScintillaStyle {
    //    int style = 0;
    //    COLORREF fore;
    //    COLORREF back = White;
    //    int size = 0;
    //    std::string face = "";

    //    ScintillaStyle(int style_, COLORREF fore_) : style(style_), fore(fore_) {}
    //    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_) : style(style_), fore(fore_), back(back_) {}
    //    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_) : style(style_), fore(fore_), back(back_), size(size_) {}
    //    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_, const std::string &face_) : style(style_), fore(fore_), back(back_), size(size_), face(face_) {}
    //};

    //struct ScintillaConfig {
    //    int lexer = 0;
    //    std::string keywords;
    //    std::map<int, COLORREF> colors;
    //    std::vector<ScintillaStyle> styles;
    //    int styleBits = 7;
    //    bool useTabs = false;
    //    int tabWidth = 4;
    //};

    class Scintilla : public wcl::core::Widget {
    public:
        struct Settings {
            int tabWidth = 4;
            bool useTabChar = false;
        };

        struct Lexer {
            std::string keywords;
        };

    public:
        Scintilla();
        
        virtual ~Scintilla();

        void setText(const std::string &text) override;

        std::string getText() const override;

        void cut();

        void copy();

        void paste();

        void undo();

        void redo();

        //void SetStyle(int style, COLORREF fore, COLORREF back=White, int size=0, const char *face=nullptr);
    
        //void SetStyle(const ScintillaStyle &style);

        //void SetSavePoint();
        //void EmptyUndoBuffer();
        //void ClearAll();
        //
        //void SetFont(const std::string &name, const int size);
        //void SetTabWidth(const int spaces);
        //
        //void Undo();
        //void Redo();

        //void Cut();
        //void Copy();
        //void Paste();

        //void SetText(const std::string &text);
        //std::string GetText() const;

        //void SetMarginType(const int margin, const int type);
        //void SetMarginWidth(const int margin, const int pixelWidth);
        //
        //int TextWidth(const int style, const std::string &text);

        //void ApplyConfig(const ScintillaConfig &config);
    };
}
