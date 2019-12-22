
#pragma once

#ifndef __wcl_edit_hpp__
#define __wcl_edit_hpp__

#include "Window.hpp"
#include <string>

namespace wcl {
    class Edit : public Window {
    public:
        Edit();

        //BOOL CanUndo() const;
        //void CharFromPos();
        //void EmptyUndoBuffer();
        //void FmtLines();
        //void GetCueBanner();
        //void GetFirstVisibleLine();
        //void GetHandle();
        //void GetHiLite();
        //void GetIMEStatus();
        //void GetLimitText();
        //void GetLine();
        //void GetLineCount();
        //void GetMargins();
        //void GetModify();
        //void GetPasswordChar();
        //void GetRect();
        //void GetSel();

        //void GetThumb();
        //void GetWordBreakProc();

        //void HideBalloonTip();
        //void LimitText();
        //void LineFromChar();
        //void LineIndex();
        //void LineLength();

        //void LineScroll();
        //void NoSetFocus();
        //void PostFromChar();
        //void ReplaceSel();
        //void Scroll();
        //void ScrollCaret();
        //void SetCubeBanner();
        //void SetHandle();
        //void SetHiLite();
        //void SetIMEStatus();
        //void SetLimitText();
        //void SetModify();
        //void SetPasswordChar();
        //void SetReadOnly();
        //void SetRect();
        //void SetRectNp();
        //void SetSel();
        //void SetTabStopss();
        //void SetWordBreakProc();
        //void ShowBalloonTip();
        //void TakeFocus();
        //void Undo();
    };

    inline Edit::Edit() : Window(WC_EDITW) {}
}

#endif // __wcl_edit_hpp__
