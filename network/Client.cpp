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
    if (_state != LOGIN || _nickname.empty() || _realname.empty() || _username.empty())
        return;
    _state = REGISTERED;
    reply(RPL_WELCOME(_nickname));

    char message[100];
    sprintf(message, "%s:%d is now known as %s.",
        _hostname.c_str(), _port, _nickname.c_str());
    ft_log(message);
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
    
    reply(RPL_NAMREPLY(_nickname, channel->getName(), users));
	reply(RPL_ENDOFNAMES(_nickname, channel->getName()));
    _channel->broadcast(RPL_JOIN(getPrefix(), channel->getName()));

    char message[100];
    sprintf(message, "%s has joined channel %s.",
        _nickname.c_str(), _channel->getName().c_str());
    ft_log(message);
}


void Client::write(const std::string& message) const
{
    std::string buf = message + "\r\n";
    if (send(_fd, buf.c_str(), buf.length(), 0) < 0)
        throw std::runtime_error("Cannot send message to the client");
}

void Client::reply(const std::string& reply)
{
    write(":" + getPrefix() + " " + reply);
}

void Client::leave()
{
    if (!_channel)
        return;
    
    const std::string channelName = _channel->getName();
    _channel->broadcast(RPL_PART(getPrefix(), _channel->getName()));
    _channel->removeClient(this);
    
    char message[100];
    sprintf(message, "%s has left channel %s.",
        _nickname.c_str(), channelName.c_str());
    ft_log(message);
}
