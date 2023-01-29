#include "Command.hpp"

UserCommand::UserCommand(Server *server, bool authRequired) :
                            Command(server, authRequired) {}

UserCommand::~UserCommand() {}

void UserCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (client->isRegistered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->getNickname()));
        return;
    }
    if (arguments.size() < 4)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "USER"));
        return;
    }
    client->setUsername(arguments[0]);
    client->setRealname(arguments[3]);
    client->welcome();
}