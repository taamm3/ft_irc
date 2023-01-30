#include "Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server) :
                            Command(server) {}

PrivMsgCommand::~PrivMsgCommand() {}

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PONG"));
        return;
    }
    client->write(RPL_PING(client->getPrefix(), arguments.at(0)));
}