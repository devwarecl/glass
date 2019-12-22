/*
#pragma once

#ifndef __wcl_dialog_hpp__
#define __wcl_dialog_hpp__

#include <string>
#include "WindowBase.hpp"

namespace wcl {
    class Dialog : public WindowBase {
    public:
        Dialog(int DialogId, HINSTANCE hInstance, HWND hWndParent);

        virtual ~Dialog();

        std::wstring GetItemText(const int DialogItemID);

        void Create();

        virtual LRESULT Procedure(UINT Msg, WPARAM wParam, LPARAM lParam);

        virtual void OnInitDialog();

        virtual void OnCommand(const int Command) = 0;

    protected:
        void End();

    private:
        int dialogId = 0;
        HINSTANCE hInstance = NULL;
        HWND hWndParent = NULL;
        
    private:
        static LRESULT CALLBACK DialogProcedure(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
    };

    inline Dialog::Dialog(int DialogId, HINSTANCE hInstance, HWND hWndParent) {
        this->dialogId = DialogId;
        this->hInstance = hInstance;
        this->hWndParent = hWndParent;
    }

    inline Dialog::~Dialog() {}

    inline void Dialog::Create() {

        // modal-less dialog
        // ::CreateDialogParam (
        //     this->hInstance, 
        //     MAKEINTRESOURCE(this->dialogId), 
        //     this->hWndParent, 
        //     reinterpret_cast<DLGPROC>(&Dialog::DialogProcedure), 
        //     (LPARAM) this
        // );
        
        // modal dialog
        ::DialogBoxParam (
            this->hInstance, 
            MAKEINTRESOURCE(this->dialogId), 
            this->hWndParent, 
            reinterpret_cast<DLGPROC>(&Dialog::DialogProcedure), 
            (LPARAM) this
        );

    }

    inline LRESULT Dialog::Procedure(UINT Msg, WPARAM wParam, LPARAM lParam) {
        return FALSE;
    }

    inline void Dialog::OnInitDialog() {}

    inline void Dialog::OnCommand(const int Command) {}

    inline void Dialog::End() {
        ::EndDialog(this->Handle, 0);
        this->Handle.hWnd = nullptr;
    }

    inline LRESULT CALLBACK Dialog::DialogProcedure(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam) {
        Dialog *dialog = reinterpret_cast<Dialog*>(::GetWindowLong(hWndDlg, DWLP_USER));

        switch (Msg) {
            case WM_INITDIALOG: {
                ::SetWindowLong(hWndDlg, DWLP_USER, lParam);
                dialog = reinterpret_cast<Dialog*>(lParam);
                dialog->Handle = WindowHandle(hWndDlg);
                dialog->OnInitDialog();

                return TRUE;
            }

            case WM_COMMAND: {
                dialog->OnCommand(wParam);

                return TRUE;
            }
        }

        return FALSE;
    }

    inline std::wstring Dialog::GetItemText(const int DialogItemID) {
        // TODO: Handle the error
        HWND hWnd = ::GetDlgItem(this->Handle, DialogItemID);

        if (!hWnd) {
            throw wcl::Exception();
        }

        std::wstring itemText;
        itemText.resize(::GetWindowTextLength(hWnd));

        ::GetWindowText(hWnd, const_cast<LPWSTR>(itemText.c_str()), itemText.size());

        return itemText;
    }
}

#endif    // __wcl_dialog_hpp__
*/