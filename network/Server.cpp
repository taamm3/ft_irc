#include "Server.hpp"

Server::Server(const std::string& port, const std::string& password) :
            _running(1), _host("127.0.0.1"), _port(port), _password(password)
{
    _socket = newSocket();
    _commandHandler = new CommandHandler(this);
}
        
Server::~Server()
{
    delete _commandHandler;
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

Channel *Server::createChannel(const std::string& channelName,
                    const std::string& password, Client *client)
{
    Channel *channel = new Channel(channelName, password, client);
    _channels.push_back(channel);
    return channel;
}
