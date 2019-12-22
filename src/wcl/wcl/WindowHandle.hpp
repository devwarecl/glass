
#pragma once

#ifndef __wcl_windowhandle_hpp__
#define __wcl_windowhandle_hpp__

#include <cassert>
#include <Windows.h>

#include "Exception.hpp"

namespace wcl {

    struct WindowHandleBase {
        HWND hWnd = nullptr;

        explicit operator bool() const {
            return this->hWnd!=nullptr;
            /*
            if (!this->hWnd) {
                return false;
            }

            return true;
            */
        }
        
        operator HWND() const {
            assert(this->operator bool());
            return hWnd;
        }
    };

    struct WindowHandleRef : public WindowHandleBase {
        WindowHandleRef() {}

        explicit WindowHandleRef(HWND hWnd) {
            this->hWnd = hWnd;
        }

        BOOL Destroy() {
            return TRUE;
        }
    };

    struct WindowHandleSmart : public WindowHandleBase {
        WindowHandleSmart() {}

        explicit WindowHandleSmart(HWND hWnd) {
            this->hWnd = hWnd;
        }

        WindowHandleSmart(WindowHandleSmart&& other) {
            this->hWnd = other.hWnd;

            other.hWnd = nullptr;
        }

        WindowHandleSmart& operator= (WindowHandleSmart&& other)  {
            this->Destroy();

            this->hWnd = other.hWnd;

            other.hWnd = nullptr;

            return *this;
        }

        WindowHandleSmart(const WindowHandleSmart&) = delete;
        WindowHandleSmart& operator=(const WindowHandleSmart&) = delete;

        BOOL Destroy() {
            if (!this->hWnd) {
                return TRUE;
            }
            
            // FIXME: It appears like the hWnd is destroyed from another place.
            if (!::IsWindow(this->hWnd)) {
                this->hWnd = nullptr;
                return TRUE;
            }
            
            if (!::DestroyWindow(this->hWnd)) {
                throw wcl::Exception("Error while destroying the window.");
            }
            
            this->hWnd = nullptr;
            
            return TRUE;
        }

        ~WindowHandleSmart() {
            this->Destroy();
        }
    };
}

#endif
