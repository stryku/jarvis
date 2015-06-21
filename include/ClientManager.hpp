#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <Session.hpp>

class ClientManager
{
private:
    typedef std::shared_ptr<Session> SessionPtr;

    std::set<SessionPtr> sessions;

public:
    ClientManager() {}
    ~ClientManager() {}

    void newClient( tcp::socket *socket )
    {
        auto session = std::make_shared<Session>( socket );
        sessions.insert( session );
        session->start();
    }
};

#endif