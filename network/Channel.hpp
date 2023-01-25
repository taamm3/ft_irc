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
        std::vector<Client*> _clients;
    public:
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

};

#endif