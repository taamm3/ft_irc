#include "Client.hpp"

void Client::welcome()
{
    
}

void Client::join(Channel *channel)
{
    channel->addClient(this);
    _channel = channel;

    std::string users;
    std::vector<std::string> nicknames = channel->getNicknames();
    for (std::vector<std::string>::iterator it = nicknames.begin();
                            it != nicknames.end(); it++)
        users.append(*it + " ");
    //TODO continue
}
