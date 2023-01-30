#include "Command.hpp"

ModeCommand::ModeCommand(Server *server) :
                            Command(server) {}

ModeCommand::~ModeCommand() {}

//Works if the target is a channel
void ModeCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
        return;
    }

    std::string target = arguments.at(0);

    if (target.at(0) == '#')
    {
        Channel *channel = client->getChannel();
        if (!channel)
        {
            client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), target));
            return;
        }

        if (channel->getAdmin() != client)
        {
            client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), target));
            return;
        } 

        int i = 0;
        int p = 2;
        char c;
        while(c = arguments[1][i])
        {
            char prev = (i == 0 ? '\0' : arguments[1][i - 1]);
            bool active = prev == '+';

            switch (c)
            {
            case 'n':
                channel->setNoExt(active);
                channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+n" : "-n"), ""));
                break;
            case 'k':
                channel->setPassword(active ? arguments[p] : "");
                channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+k" : "-k"), (active ? arguments[p] : "")));
                p += active;
                break;
            case 'l':
                channel->setMaxClients(active ? std::stoi(arguments[p]) : 0);
                channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+l" : "-l"), (active ? arguments[p] : "")));
                p += active;
                break;
            default:
                break;
            }
            i++;
        }
    }
}