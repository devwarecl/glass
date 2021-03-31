
#pragma once 

#include <functional>
#include <memory>

namespace wcl::core {
    class EventRaiser;

    typedef std::function< void(const std::string&, EventRaiser*) > EventCallback;
    typedef int ConnectionId;

    class EventRaiser {
    public:
        EventRaiser();

        ~EventRaiser();

        ConnectionId connect(const std::string &eventName, EventCallback callback);

        void disconnect(const std::string &eventName, const ConnectionId id);

    protected:
        void raise(const std::string &eventName);

    private:
        struct Impl;
        std::unique_ptr<Impl> mEventRaiserImpl;
    };
}
