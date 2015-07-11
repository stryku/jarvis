#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <memory>
#include <map>

#include <Session.hpp>

class ClientManager
{
private:
    typedef std::shared_ptr<Session> SessionPtr;
    typedef std::shared_ptr<Client> ClientPtr;

    std::set<SessionPtr> sessions;
    std::map<const tcp::socket*, ClientPtr> socketClientMap;
    std::map<std::string, ClientPtr> idClientMap;

    ClientPtr createNewClient( tcp::socket *socket )
    {
        auto client = std::make_shared<Client>( socket );
        socketClientMap[socket] = client;
        return client;
    }

    void createNewSession( ClientPtr &client )
    {
        auto session = std::make_shared<Session>( client );
        sessions.insert( session );
        session->start( );
    }

public:
    ClientManager() {}
    ~ClientManager() {}

    void newClientAccepted( tcp::socket *socket )
    {
        auto client = createNewClient( socket );
        createNewSession( client );
    }

    void newClientId( tcp::socket *clientSocket, const std::string &clientId )
    {
        idClientMap[clientId] = socketClientMap[clientSocket];
        socketClientMap[clientSocket]->id = clientId;
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