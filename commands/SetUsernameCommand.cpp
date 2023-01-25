#include "Command.hpp"

SetUsernameCommand::SetUsernameCommand(Server *server, bool authRequired) :
                            Command(server, authRequired) {}

SetUsernameCommand::~SetUsernameCommand() {}

void SetUsernameCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (client->isRegistered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->getNickname()));
        return;
    }
    if (arguments.size() < 4)
    {
        client->reply(ERR_MOREARGSNEEDED(client->getNickname(), "USER"));
        return;
    }
    client->setUsername(arguments[0]);
    client->setRealname(arguments[3]);
    client->welcome();
}