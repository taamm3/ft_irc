#ifndef SERVER_HPP
#define SERVER_HPP
#include "Client.hpp"
#include "Channel.hpp"
#include <iostream>
#include <map>

class Server
{
    private:
        const std::string _port;
        const std::string _password;

        std::map<int, Client*> _clients;
        std::vector<Channel *> _channels;
    public:
        Server(const std::string& port, const std::string& password);
        ~Server();

        void start();

        std::string getPassword() const
        {
            return _password;
        }
        Client *getClient(const std::string& nickname);
        Channel *getChannel(const std::string& channelName);

        Channel *createChannel(const std::string& channelName, const std::string& password,Client *client);
};

#endif