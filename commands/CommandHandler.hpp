#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP
#include "Command.hpp"
#include <sstream>

class CommandHandler
{
    private:
        Server *_server;
        std::map<std::string, Command*> _commands;
    public:
        CommandHandler(Server *server);
        ~CommandHandler();
        void invoke(Client *client, const std::string& message);
};

#endif