#include "Command.hpp"

KickCommand::KickCommand(Server *server) :
                            Command(server) {}

KickCommand::~KickCommand() {}

void KickCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"));
        return;
    }

    std::string channelName = arguments[0];
    std::string target = arguments[1];
    std::string reason = "No reason specified.";
    if (arguments.size() >= 3 && (arguments[2][0] != ':' || arguments[2].size() > 1))
    {
        reason = "";
        for (std::vector<std::string>::iterator it = arguments.begin() + 2;
                            it != arguments.end(); it++)
            reason.append(*it + " ");
    }

    Channel *channel = client->getChannel();
    if (!channel || channel->getName() != channelName)
    {
        client->reply(ERR_NOTONCHANNEL(client->getNickname(), channelName));
        return;
    }
    if (channel->getAdmin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
        return;
    }

    Client *c = _server->getClient(target);
    if (!c)
    {
        client->reply(ERR_NOSUCHNICK(client->getNickname(), target));
        return;
    }
    if (!c->getChannel() || c->getChannel() != channel)
    {
        client->reply(ERR_USERNOTINCHANNEL(client->getNickname(), target, channelName));
        return;
    }

    channel->kick(client, c, reason);
}