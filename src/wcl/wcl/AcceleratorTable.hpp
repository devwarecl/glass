
#pragma once

#ifndef __wcl_acceleratortable_hpp__
#define __wcl_acceleratortable_hpp__

#include <Windows.h>
#include "Exception.hpp"

namespace wcl {

    struct Accelerator : public ACCEL {
        /*
        Accelerator (BYTE fVirt, WORD key, WORD cmd) {
            this->fVirt = fVirt;
            this->key = key;
            this->cmd = cmd;
        }
        */

        Accelerator (WORD cmd, BYTE fVirt, WORD key) {
            this->fVirt = fVirt;
            this->key = key;
            this->cmd = cmd;
        }

        std::wstring ToString() const;
    };

    inline std::wstring Accelerator::ToString() const {
        std::wstring result;
        std::list<std::wstring> parts;

        if (this->fVirt & FCONTROL) {
            parts.push_back(L"Ctrl");
        }

        if (this->fVirt & FSHIFT) {
            parts.push_back(L"Shift");
        }

        if (this->fVirt & FALT) {
            parts.push_back(L"Alt");
        }

        if (this->fVirt & FVIRTKEY) {
            const int PART_SIZE = 32;

            wchar_t part[PART_SIZE] = {};

            UINT result = ::MapVirtualKey(this->key, 0);

            INT textResult = ::GetKeyNameTextW (
                result<<16/*|1<<24*/, 
                part, 
                PART_SIZE - 1
            );

            parts.push_back(part);

        } else {
            std::wstring part = L" ";
            std::string ch = " ";
            ch[0] = static_cast<char>(this->key);

            std::mbstowcs (
                const_cast<wchar_t*>(part.c_str()), 
                ch.c_str(), 
                ch.size()
            );

            parts.push_back(part);
        }

        // assemble the final string
        bool first = true;

        for (const std::wstring &part : parts) {
            if (first) {
                result += part;

                first = false;
            } else {
                result += L"+" + part;
            }
        }

        return result;
    }

    class AcceleratorTable {
    public:
        AcceleratorTable();
        AcceleratorTable(ACCEL *accelerators, const int acceleratorCount);
        ~AcceleratorTable();

        void Create(ACCEL *accelerators, const int acceleratorCount);

        void Destroy();

        HACCEL GetHandle() const;

    private:
        HACCEL hAccelerator = NULL;
    };

    typedef std::unique_ptr<AcceleratorTable> AcceleratorTablePtr;

    inline AcceleratorTable::AcceleratorTable() {}

    inline AcceleratorTable::AcceleratorTable(ACCEL *accelerators, const int acceleratorCount) {
        this->Create(accelerators, acceleratorCount);
    }

    inline AcceleratorTable::~AcceleratorTable() {
        this->Destroy();
    }

    inline void AcceleratorTable::Create(ACCEL *accelerators, const int acceleratorCount) {
        this->hAccelerator = ::CreateAcceleratorTableW(accelerators, acceleratorCount);
    }

    inline void AcceleratorTable::Destroy() {
        if (this->hAccelerator) {
            ::DestroyAcceleratorTable(this->hAccelerator);
            this->hAccelerator = NULL;
        }
    }

    inline HACCEL AcceleratorTable::GetHandle() const {
        return this->hAccelerator;
    }
}

#endif    //__wcl_acceleratortable_hpp__
