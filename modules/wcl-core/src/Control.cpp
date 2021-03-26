/*
 * The MIT License (MIT)
 *
 * Copyright © 2021 Felipe Apablaza C.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the “Software”), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <wcl/core/Control.hpp>

#include <vector>
#include <map>
#include <set>
#include <cassert>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Window.hpp"


namespace wcl::core {
    struct Connection {
        ConnectionId id;
        EventCallback callback;

        bool operator< (const Connection &rhs) const {
            return id < rhs.id;
        }

        bool operator== (const Connection &rhs) const {
            return id == rhs.id;
        }
    };

    struct Control::Impl {
        Window mWindow;

        std::map<std::string, std::set<Connection>> mConnectionsMap;
    };
}


namespace wcl::core {
    Control::Control(const std::wstring &className) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
    }


    Control::Control(const std::wstring &className, const std::wstring &text) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
        mImpl->mWindow.mCreationText = text;
    }


    Control::Control(const std::wstring &className, const std::wstring &text, const Rect &area) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
        mImpl->mWindow.mCreationText = text;
        mImpl->mWindow.mCreationAreaOpt = area;
    }


    Control::~Control() {}


    void Control::setText(const std::wstring &value) {
        ::SetWindowText(mImpl->mWindow.mHandle, value.c_str());
    }


    std::wstring Control::getText() const {
        const int length = ::GetWindowTextLengthW(mImpl->mWindow.mHandle);

        std::wstring value;
        value.resize(static_cast<size_t>(length) + 1);

        ::GetWindowText(mImpl->mWindow.mHandle, const_cast<wchar_t*>(value.c_str()), length + 1);

        return value;
    }


    Rect Control::getArea() const {
        RECT rect;

        ::GetWindowRect(mImpl->mWindow.mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }


    Rect Control::getClientArea() const {
        RECT rect;

        ::GetClientRect(mImpl->mWindow.mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }


    Window* Control::getWindow() const {
        return &mImpl->mWindow;
    }


    void Control::raise(const std::string &eventName) {
        auto it = mImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mImpl->mConnectionsMap.end()) {
            for (auto &connection : it->second) {
                connection.callback(eventName, this);
            }
        }
    }


    ConnectionId Control::connect(const std::string &eventName, EventCallback callback) {
        auto it = mImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mImpl->mConnectionsMap.end()) {
            const auto id = static_cast<ConnectionId>(it->second.size() + 1);

            it->second.insert({id, callback});

            return id;
        } else {
            mImpl->mConnectionsMap[eventName].insert({1, callback});

            return 1;
        }
    }


    void Control::disconnect(const std::string &eventName, const ConnectionId id) {
        auto it = mImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mImpl->mConnectionsMap.end()) {
            auto &callbacks = it->second;

            const auto pos = std::find_if(callbacks.begin(), callbacks.end(), [id](const auto &connection) {
                return connection.id == id;
            });

            if (pos != callbacks.end()) {
                callbacks.erase(pos);
            }
        }
    }
}
