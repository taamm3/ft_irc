#include "Command.hpp"

JoinChannelCommand::JoinChannelCommand(Server *server) :
                            Command(server) {}

JoinChannelCommand::~JoinChannelCommand() {}

void JoinChannelCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        client->reply(ERR_MOREARGSNEEDED(client->getNickname(), "PASS"));
        return;
    }

    std::string channelName = arguments[0];
    std::string password = arguments.size() > 1 ? arguments[1] : "";
    if (client->getChannel())
    {
        client->reply(ERR_TOOMANYCHANNELS(client->getNickname(), channelName));
        return;
    }

    Channel *channel = _server->getChannel(channelName);
    if (!channel)
        channel = _server->createChannel(channelName, password, client);
    
    if (channel->getMaxClients() > 0 && channel->getNumberOfClients() >= channel->getMaxClients())
    {
        client->reply(ERR_CHANNELFULL(client->getNickname(), channelName));
        return;
    }

    if (channel->getPassword() != password)
    {
        client->reply(ERR_BADCHANNELKEY(client->getNickname(), channelName));
        return;
    }

    client->join(channel);
}