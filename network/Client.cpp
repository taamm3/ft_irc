#include "Client.hpp"

Client::Client(int fd, const std::string& hostname, int port) :
            _fd(fd), _hostname(hostname), _port(port), _state(HANDSHAKE), _channel(nullptr)
{}

Client::~Client() {}

std::string Client::getPrefix() const
{
    return _nickname + (_username.empty() ? "" :
        "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
}

void Client::welcome()
{
    
}

void Client::join(Channel *channel)
{
    channel->addClient(this);
    _channel = channel;

    std::string users;
    std::vector<std::string> nicknames = channel->getNicknames();
    for (std::vector<std::string>::iterator it = nicknames.begin();
                            it != nicknames.end(); it++)
        users.append(*it + " ");
    //TODO continue
}


void Client::write(const std::string& message) const
{

}

void Client::leave()
{

}
