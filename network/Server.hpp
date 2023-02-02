#ifndef SERVER_HPP
#define SERVER_HPP
#include <algorithm>
// #include <sys/poll.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <map>
// #include <poll.h>
// #include <unistd.h>

// #include <sys/poll.h>
// #include <sys/socket.h>

class Server;
#include "Client.hpp"
#include "Channel.hpp"
#include "../commands/CommandHandler.hpp"

class Server
{
    private:
        int _running; 
        int _socket;
        const std::string _host;
        const std::string _port;
        const std::string _password;

        std::vector<pollfd> _pollfds;
        std::map<int, Client*> _clients;
        std::vector<Channel *> _channels;
        CommandHandler *_commandHandler;
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

        int newSocket();
        void onClientDisconnect(int fd);
        void onClientConnect();
        void onClientMessage(int fd);
        std::string readMessage(int fd);
};

#endif