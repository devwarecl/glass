
#pragma once 

#include <functional>
#include <memory>

namespace wcl::core {
    //namespace experimental {
    //    template<typename EventType, typename ConcreteEventRaiser>
    //    class EventRaiser {
    //    public:
    //        struct ConnectionId {
    //            ConnectionId() {}
    //
    //            ConnectionId(const int value) : mValue(value) {}
    //
    //            int mValue = 0;
    //
    //            bool operator< (const ConnectionId &rhs) const {
    //                return mValue < rhs.mValue;
    //            }
    //        };
    //
    //        using Callback = std::function< void(const EventType&, const ConcreteEventRaiser*) >;
    //
    //    public:
    //        virtual ~EventRaiser() {}
    //
    //        ConnectionId connect(const EventType event, EventCallback callback) {
    //            return {};
    //        }
    //
    //        void disconnect(const EventType event, const ConnectionId id) {}
    //
    //    protected:
    //        void raise(const EventType event) {}
    //    };
    //}


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
