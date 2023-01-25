#include "Server.hpp"

Server::Server(const std::string& port, const std::string& password) :
            _port(port), _password(password)
{
    
}
        
Server::~Server()
{

}

void Server::start()
{

}

Client *Server::getClient(const std::string& nickname)
{
    for (std::map<int, Client*>::iterator it = _clients.begin();
                                it != _clients.end(); it++)
    {
        if (!nickname.compare(it->second->getNickname()))
            return it->second;
    }
    return nullptr;
}

Channel *Server::getChannel(const std::string& name)
{
    for (std::vector<Channel*>::iterator it = _channels.begin();
                                it != _channels.end(); it++)
    {
        if (it.operator*()->getName() == name)
            return it.operator*();
    }
    return nullptr;
}