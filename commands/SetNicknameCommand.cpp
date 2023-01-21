#include "Command.hpp"

SetNicknameCommand::SetNicknameCommand(Server *server, bool authRequired) :
                            Command(server, authRequired) {}

SetNicknameCommand::~SetNicknameCommand() {}

void SetNicknameCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.empty() || arguments[0].empty())
    {
        client->reply(ERR_NONICKNAME(client->getNickname()));
        return;
    }
    if (_server->getClient(arguments[0]))
    {
        client->reply(ERR_NICKNAMEALREADYUSED(client->getNickname()));
        return;
    }
    client->setNickname(arguments[0]);
    client->welcome();
}