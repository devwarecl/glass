/**
 *    Windows Class Library
 *
 *    Lightweight Windows API wrapper.
 *
 */

#pragma once

#ifndef __wcl_application_hpp__
#define __wcl_application_hpp__

#include <map>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <commctrl.h>
#include <wcl/Module.hpp>

#pragma comment (lib, "comctl32.lib")

namespace wcl {

    class Application {
    public:        
        Application();

        ~Application() {}

        int Run();

        void SetWindowAccelerator(HWND hWnd, HACCEL hAccelerator);

        HACCEL GetWindowAccelerator(HWND hWnd) const;

    protected:
        void Load(const std::string &moduleName);
        void Unload(const std::string &moduleName);

    private:
        std::map<HWND, HACCEL> accelerators;
        std::map<std::string, ModulePtr> m_modules;
    };

    inline void Application::SetWindowAccelerator(HWND hWnd, HACCEL hAccelerator) {
        accelerators[hWnd] = hAccelerator;
    }

    inline HACCEL Application::GetWindowAccelerator(HWND hWnd) const {
        auto it = accelerators.find(hWnd);

        if (it == accelerators.end()) {
            return NULL;
        } else {
            return it->second;
        }
    }

    inline int Application::Run() {
        MSG msg = {0};

        BOOL result;

        while ( (result = ::GetMessage(&msg, NULL, 0, 0)) != 0) {
            if (result == -1) {
                break;
            } 
            
            auto &accel = this->accelerators;
            auto it = std::find_if(accel.begin(), accel.end(), [&msg](const std::pair<HWND, HACCEL> &value) {

                const bool isChild = ::IsChild(value.first, msg.hwnd)==TRUE;
                const bool isSame = value.first==msg.hwnd;

                return isChild || isSame;
            }) ;

            if (it == accel.end()) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);

            } else {
                BOOL result_ = ::TranslateAccelerator(it->first, it->second, &msg);

                if (!result_) {
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                }
            }
        }

        return 0;
    }

    inline Application::Application() {
        ::InitCommonControls();
    }

    inline void Application::Load(const std::string &moduleName) {
        auto module = std::make_unique<Module>(moduleName);
        m_modules[moduleName] = std::move(module);
    }

    inline void Application::Unload(const std::string &moduleName) {
        m_modules.erase(moduleName);
    }

    template<typename ApplicationType, typename WindowType>
    int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
        try {
            ApplicationType app;

            WindowType frame;
            frame.Create();
            frame.Show();

            return app.Run();
        } catch (const wcl::Exception &exp) {
            ::MessageBoxA(NULL, exp.what(), "Unhandled Windows Exception", MB_OK | MB_ICONERROR);
            return 1;
        
        } catch (const std::exception &exp) {
            ::MessageBoxA(NULL, exp.what(), "Unhandled System Error", MB_OK | MB_ICONERROR);
            return 2;
        
        } catch (...) {
            ::MessageBoxA(NULL, "Unknown error.", "Error", MB_OK | MB_ICONERROR);
        }
    }

    template<typename ApplicationType, typename WindowType>
    int Main() {
        return Main<ApplicationType, WindowType>(NULL, NULL, NULL, 0);
    }
}

#endif
