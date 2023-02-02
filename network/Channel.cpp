#include "Channel.hpp"

Channel::Channel(const std::string& name,const std::string& key, Client *admin) :
                _name(name), _key(key), _maxClients(0), _admin(admin), _noExt(false) {}

Channel::~Channel() {}

std::vector<std::string> Channel::getNicknames()
{
    std::vector<std::string> nicknames;
    for (std::vector<Client*>::iterator it = _clients.begin();
                    it != _clients.end(); it++)
    {
        Client *client = it.operator*();
        nicknames.push_back((_admin == client ? "@" : "") + (*it)->getNickname());
    }
    return nicknames;
}

void Channel::addClient(Client *client)
{
    _clients.push_back(client);
}

void Channel::kick(Client *admin, Client *target, std::string reason)
{
    broadcast(RPL_KICK(admin->getPrefix(), _name, target->getNickname(), reason));
    removeClient(target);

    char message[100];
    sprintf(message, "%s kicked %s from channel %s.",
        admin->getNickname().c_str(), target->getNickname().c_str(), _name.c_str());
    ft_log(message);
}

void Channel::removeClient(Client *client)
{
    std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
    if (it != _clients.end())
    {
        _clients.erase(it);
    }
    client->setChannel(nullptr);
}

void Channel::broadcast(const std::string& message)
{
    for (std::vector<Client*>::iterator it = _clients.begin();
                    it != _clients.end(); it++)
        (*it)->write(message);
}

void Channel::broadcast(const std::string& message, Client *exception)
{
    for (std::vector<Client*>::iterator it = _clients.begin();
                    it != _clients.end(); it++)
        if (*it != exception)
            (*it)->write(message);
}
