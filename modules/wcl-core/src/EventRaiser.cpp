
#include <wcl/core/EventRaiser.hpp>

#include <map>
#include <set>


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

    struct EventRaiser::Impl {
        std::map<std::string, std::set<Connection>> mConnectionsMap;
    };
}


namespace wcl::core {

    EventRaiser::EventRaiser() : mEventRaiserImpl(new EventRaiser::Impl()) {}


    EventRaiser::~EventRaiser() {}


    void EventRaiser::raise(const std::string &eventName) {
        auto it = mEventRaiserImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mEventRaiserImpl->mConnectionsMap.end()) {
            for (auto &connection : it->second) {
                connection.callback(eventName, this);
            }
        }
    }


    ConnectionId EventRaiser::connect(const std::string &eventName, EventCallback callback) {
        auto it = mEventRaiserImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mEventRaiserImpl->mConnectionsMap.end()) {
            const auto id = static_cast<ConnectionId>(it->second.size() + 1);

            it->second.insert({id, callback});

            return id;
        } else {
            mEventRaiserImpl->mConnectionsMap[eventName].insert({1, callback});

            return 1;
        }
    }


    void EventRaiser::disconnect(const std::string &eventName, const ConnectionId id) {
        auto it = mEventRaiserImpl->mConnectionsMap.find(eventName);
        // assert(it != mImpl->mConnectionsMap.end());

        if (it != mEventRaiserImpl->mConnectionsMap.end()) {
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
