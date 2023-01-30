#include "Command.hpp"

PingCommand::PingCommand(Server *server) :
                            Command(server) {}

PingCommand::~PingCommand() {}

//TO CHECK
void PingCommand::execute(Client *client, std::vector<std::string> arguments)
{
    client->write("PING");
}