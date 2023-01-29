#include "Command.hpp"

NickCommand::NickCommand(Server *server, bool authRequired) :
                            Command(server, authRequired) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.empty() || arguments[0].empty())
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->getNickname()));
        return;
    }
    if (_server->getClient(arguments[0]))
    {
        client->reply(ERR_NICKNAMEINUSE(client->getNickname()));
        return;
    }
    client->setNickname(arguments[0]);
    client->welcome();
}