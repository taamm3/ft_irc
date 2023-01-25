#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>

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
        std::string _username;
        std::string _nickname;
        std::string _realname;
        ClientState _state;

        Channel *_channel;
    public:
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
        void setChannel(Channel *channel)
        {
            _channel = channel;
        }
        Channel *getChannel() const
        {
            return _channel;
        }

        void welcome();
        void reply(const std::string& reply);

};

#endif