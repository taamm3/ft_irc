#include "Channel.hpp"

Channel::Channel(const std::string& name,const std::string& key, Client *admin) :
                _name(name), _key(key), _maxClients(0), _admin(admin) {}

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

