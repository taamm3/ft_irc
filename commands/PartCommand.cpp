#include "Command.hpp"

PartCommand::PartCommand(Server *server) :
                            Command(server) {}

PartCommand::~PartCommand() {}

void PartCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
        return;
    }

    std::string channelName = arguments[0];
    Channel *channel = _server->getChannel(channelName);
    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
        return;
    }

    if (!client->getChannel() || client->getChannel()->getName() != channelName)
    {
        client->reply(ERR_NOTONCHANNEL(client->getNickname(), channelName));
        return;
    }
    
    _client->leave();
}