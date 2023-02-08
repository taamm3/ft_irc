#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

#define ERR_UNKNOWNCOMMAND(nick, command)   "421 " + nick + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(nick, command)   "461 " + nick + " " + command + " :Not enough parameters"
#define ERR_NOTREGISTERED(nick)             "451 " + nick + " :You have not registered"
#define ERR_ALREADYREGISTERED(nick)         "462 " + nick + " :Unauthorized command (already registered)"
#define ERR_PASSWDMISMATCH(nick)            "464 " + nick + " :Password Incorrect"
#define ERR_NONICKNAMEGIVEN(nick)           "431 " + nick + " :No nickname given"
#define ERR_NICKNAMEINUSE(nick)             "433 " + nick + " " + nick + " :Nickname is already in use"
#define ERR_TOOMANYCHANNELS(nick, channel)  "405 " + nick + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(nick, channel)     "442 " + nick + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(nick, channel)    "403 " + nick + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(nick, channel)    "475 " + nick + " " + channel + " :Bad Channel Key"
#define ERR_NOSUCHNICK(nick, channel)       "401 " + nick + " " + channel + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(nick, client, channel)    "441 " client + " " + nick + " " + channel + " :They aren't on that channel"
#define ERR_CHANOPRIVSNEEDED(client, channel)          "482 " + client + " " + channel + " :You're not channel operator"
#define ERR_CHANNELISFULL(client, channel)             "471 " + client + " " + channel + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(client, channel)          "404 " + client + " " + channel + " :Cannot send to channel"

#define RPL_WELCOME(source)						"001 " + source + " :Welcome " + source + " to the ft_irc network"
#define RPL_NAMREPLY(source, channel, users)	"353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)			"366 " + source + " " + channel + " :End of /NAMES list."

#define RPL_JOIN(source, channel)					":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)					":" + source + " PART :" + channel
#define RPL_PING(source, token)						":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)		":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)			":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)					":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)	":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args)		":" + source + " MODE " + channel + " " + modes + " " + args

static inline void ft_log(const std::string &message) {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	// std::string str(buffer);
	// (void)message;
	std::cout << "[" << buffer << "] " << message << std::endl;
};


#endif