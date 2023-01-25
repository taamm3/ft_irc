#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <vector>
#include <string>
#include "../network/Server.hpp"
#include "../network/Client.hpp"
#include "../network/Channel.hpp"

class Command
{
    protected:
        Server *_server;
        bool _authRequired;
    public:
        explicit Command(Server *server, bool authRequired = true) :
                _server(server), _authRequired(authRequired) {}
        virtual ~Command() {}
        bool authRequired() const { return _authRequired; }
        virtual void execute(Client *client, std::vector<std::string> arguments) = 0;
};

class SetNicknameCommand : public Command
{
    public:
        SetNicknameCommand(Server *server, bool authRequired);
        ~SetNicknameCommand();
        void execute(Client *client, std::vector<std::string> arguments);
};

class SetUsernameCommand : public Command
{
    public:
        SetUsernameCommand(Server *server, bool authRequired);
        ~SetUsernameCommand();
        void execute(Client *client, std::vector<std::string> arguments);
};

class JoinChannelCommand : public Command
{
    public:
        JoinChannelCommand(Server *server);
        ~JoinChannelCommand();
        void execute(Client *client, std::vector<std::string> arguments);
};

#endif