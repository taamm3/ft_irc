#include "Command.hpp"

QuitCommand::QuitCommand(Server *server, bool authRequired) :
                            Command(server, authRequired) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Client *client, std::vector<std::string> arguments)
{
    std::string reason = arguments.empty() ? "" :
            arguments[0][0] == ':' ? arguments[0].substr(1) : arguments[0];
    client->write(RPL_QUIT(client->getPrefix(), reason));
}