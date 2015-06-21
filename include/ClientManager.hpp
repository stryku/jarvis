#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <map>

#include <Session.hpp>

class ClientManager
{
private:
    typedef std::shared_ptr<Session> SessionPtr;
    typedef std::shared_ptr<Client> ClientPtr;

    std::set<SessionPtr> sessions;
    std::map<tcp::socket*, ClientPtr> socketClientMap;
    std::map<std::string, ClientPtr> idClientMap;

public:
    ClientManager() {}
    ~ClientManager() {}

    void newClient( tcp::socket *socket )
    {
        auto client = std::make_shared<Client>( socket );
        auto session = std::make_shared<Session>( client );
        sessions.insert( session );
        session->start();
    }

    void newClientId( const tcp::socket *clientSocket, const std::string &clientId )
    {
        idClientMap[clientId] = socketClientMap[clientSocket];
    }

    ClientPtr getClientBySocket( const tcp::socket *clientSocket )
    {
        return socketClientMap[clientSocket];
    }

    ClientPtr getClientById( const std::string &clientId )
    {
        return idClientMap[clientId];
    }
};

#endif