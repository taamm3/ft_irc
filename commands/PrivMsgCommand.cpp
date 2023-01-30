#include "Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server) :
                            Command(server) {}

PrivMsgCommand::~PrivMsgCommand() {}

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.size() < 2 || arguments[0].empty() || arguments[1].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
        return;
    }

    std::string target = arguments.at(0);
    std::string message;
    for (std::vector<std::string>::iterator it = arguments.begin() + 1;
                    it != arguments.end(); it++)
        message.append(*it + " ");
    message = (message[0] == ':' ? message.substr(1) : message);

    if (target.at(0) == '#')
    {
        Channel *channel = client->getChannel();
        if (!channel)
        {
            client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), target));
            return;
        }
        if (channel->isNoExt())
        {
            std::vector<std::string> nicknames = channel->getNicknames();
            std::vector<std::string>::iterator it;
            for (it = nicknames.begin();
                    it != nicknames.end(); it++)
                if (*it == client->getNickname())
                    break;
            if (it == nicknames.end())
            {
                client->reply(ERR_CANNOTSENDTOCHAN(client->getNickname(), target));
                return;
            }
        }
        channel->broadcast(RPL_PRIVMSG(client->getPrefix(), target, message), client);
        return;
    }
    Client *c = _server->getClient(target);
    if (!c)
    {
        client->reply(ERR_NOSUCHNICK(client->getNickname(), target));
        return;
    }
        
    c->write(RPL_PRIVMSG(client->getPrefix(), target, message));
}