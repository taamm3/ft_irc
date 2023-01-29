#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include <vector>
#include "Client.hpp"

class Channel
{
    private:
        std::string _name;
        const std::string _key;
        int _maxClients;
        Client *_admin;
        std::vector<Client*> _clients;
        bool noExt;
    public:
        Channel(const std::string& name, const std::string& key, Client *client);
        ~Channel();
        std::string getPassword() const
        {
            return _key;
        } 
        int getNumberOfClients() const
        {
            return _clients.size();
        }
        int getMaxClients() const
        {
            return _maxClients;
        }
        std::string getName() const
        {
            return _name;
        }
        Client *getAdmin() const
        {
            return _admin;
        }
        bool isNoExt() const
        {
            return noExt;
        }
        std::vector<std::string> getNicknames();

        void addClient(Client *client);
        void kick(Client *admin, Client *client, std::string reason);
        void broadcast(const std::string& message, Client *client);
};

#endif