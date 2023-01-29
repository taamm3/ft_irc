#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include "Channel.hpp"

enum ClientState
{
    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

class Client
{
    private:
        int _fd;
        std::string _hostname;
        int _port;

        std::string _username;
        std::string _nickname;
        std::string _realname;
        ClientState _state;

        Channel *_channel;
    public:
        Client(int fd, const std::string& hostname, int port);
        ~Client();
        void setNickname(const std::string& nickname)
        {
            _nickname = nickname;
        }
        std::string getNickname() const
        {
            return _nickname;
        }
        void setUsername(const std::string& username)
        {
            _username = username;
        }
        std::string getUsername() const
        {
            return _username;
        }
        void setRealname(const std::string& realname)
        {
            _realname = realname;
        }
        std::string getRealname() const
        {
            return _realname;
        }
        bool isRegistered() const
        {
            return _state == REGISTERED;
        }
        void setState(ClientState state)
        {
            _state = state;
        }
        ClientState getState() const
        {
            return _state;
        }
        void setChannel(Channel *channel)
        {
            _channel = channel;
        }
        Channel *getChannel() const
        {
            return _channel;
        }
        std::string getPrefix() const;

        void welcome();
        void reply(const std::string& reply);
        void join(Channel *channel);
        void write(const std::string& message) const;
        void leave();
};

#endif