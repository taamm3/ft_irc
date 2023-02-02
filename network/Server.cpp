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

int Server::newSocket()
{

}

void Server::onClientDisconnect(int fd)
{

}

void Server::onClientConnect()
{

}

void Server::onClientMessage(int fd)
{
    try
    {
        Client *client = _clients.at(fd);
        _commandHandler->invoke(client, readMessage(fd));
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

std::string Server::readMessage(int fd) {
    std::string message;
    char buffer[100] = {0};
    
    while (message.find("\r\n") == std::string::npos) {
        std::memset(buffer, 0, 100);
        if (recv(fd, buffer, 100, 0) < 0) {
            if (errno != EWOULDBLOCK)
                throw std::runtime_error("Error while reading buffer from client.");
        }
        message.append(buffer);
    }
    return message;
}
