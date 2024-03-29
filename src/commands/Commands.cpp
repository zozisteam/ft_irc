/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:24:54 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/25 17:09:03 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../server/Server.hpp"

// base class

Command::Command(Server *server) : serv(server) {}

//constructors
JOIN::JOIN(Server *server) : Command(server) {}
TOPIC::TOPIC(Server *server) : Command(server) {}
MODE::MODE(Server *server) : Command(server) {}
INVITE::INVITE(Server *server) : Command(server) {}
KILL::KILL(Server *server) : Command(server) {}
KICK::KICK(Server *server) : Command(server) {}
USER::USER(Server *server) : Command(server) {}
NICK::NICK(Server *server) : Command(server) {}
PASS::PASS(Server *server) : Command(server) {}
PM::PM(Server *server) : Command(server) {}
QUIT::QUIT(Server *server) : Command(server) {}

// child class 

// PASS <password>
void PASS::execute(Client *client, std::vector<std::string> args)
{
	if (args.empty())
	{
		client->reply("need good pass");
		return;
	}

	if (client->get_state() == 2) //== registered )
	{
		client->reply(client->get_nick() + " is already registered");
		return;
	}

	std::string password = args[0];
	if (password[0] == ':')
		password = password.substr(1);

	if (serv->get_password() != password)
	{
		client->reply("wrong password");
		return;
	}

	client->set_state(1); // 1 = login
}

// NICK <nickname>
void NICK::execute(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		client->reply("no nickname given");
		return;
	}

	std::string nickname = args[0];
	if (serv->get_client(nickname))
	{
		client->reply("nickname used");
		return;
	}
	client->set_nick(nickname);
	client->welcome();
}

//  USER <username> <hostname> <servername> <realname>
void USER::execute(Client *client, std::vector<std::string> args)
{
	if (client->get_state() == 2)
	{
		client->reply(client->get_nick() + " is already registered");
		return;
	}

	if (args.size() < 4)
	{
		client->reply("args < 4");
		return;
	}

	client->set_uname(args[0]);
	client->set_name(args[3]);
	client->welcome();
}

// PRIVMSG <msgtarget> :<message>
void PM::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() < 2 || args[0].empty() || args[1].empty())
	{
		client->reply("need more params");
		return;
	}

	std::string target = args.at(0);
	std::string message;

	// iterate  args starting from the second one
	for (auto iter = args.begin() + 1; iter != args.end(); ++iter)
	{
		// Access the current argument using '(*it)' and concatenate it to the message
		message += *iter;
	}

	if (message.at(0) == ':')
		message = message.substr(1);

	// if notice is for a channel
	if (target.at(0) == '#')
	{
		Channel *channel = client->get_channel();

		// channel not found
		if (!channel->ext_msg())
		{
			const std::vector<std::string> &nicknames = channel->get_nicknames(); // get all nicks registered in channel

			// check client is in channel
			// check if can use find from <algorithm>
			auto iter = std::find(nicknames.begin(), nicknames.end(), client->get_nick());

			// not found
			if (iter == nicknames.end())
			{
				client->reply("cant send to channel");
				return;
			}
		}
		// implement**
		// channel->broadcast(RPL_PRIVMSG(client->get_prefix(), target, message), client);
		return;
	}

	// else if notice is for a client
	Client *dest_client = serv->get_client(target);
	if (!dest_client)
	{
		client->reply("no nickname found");
		return;
	}

	dest_client->send("implement reply to client");
}

// QUIT [<message>]
void QUIT::execute(Client *client, std::vector<std::string> args)
{
	// if args empty set reason to leaving, if not empty check at [0][0] if ':' then take string without first char
	std::string reason = args.empty() ? "leaving!!!" : (args.at(0)[0] == ':' ? args.at(0).substr(1) : args.at(0));
	client->send("leaving because " + reason);
	serv->on_client_disconnect(client->get_fd());
}

//  JOIN <channels> [<keys>]
void JOIN::execute(Client *client, std::vector<std::string> args)
{
	if (args.empty())
	{
		client->reply("need more args");
		return;
	}
	std::string name = args[0];
	std::string pass = args.size() > 1 ? args[1] : "";

	Channel *channel = client->get_channel();
	if (channel)
	{
		client->reply("already in a channel");
		return;
	}

	channel = serv->get_channel(name);
	if (!channel)
		channel = serv->create_channel(name, pass, client);

	// checks channel has a user limit and if current number of users is more than limit
	if (channel->get_limit() > 0 && channel->get_size() >= channel->get_limit())
	{
		client->reply("channel is full");
		return;
	}

	if (channel->get_key() != pass)
	{
		client->reply("wrong channel key");
		return;
	}

	client->join(channel);
}

void KILL::execute(Client *client, std::vector<std::string> args)
{
}



// destructors 
Command::~Command() {}
PASS::~PASS() {}
INVITE::~INVITE() {}
NICK::~NICK() {}
USER::~USER() {}
PM::~PM() {}
QUIT::~QUIT() {}
JOIN::~JOIN() {}
KICK::~KICK() {}
TOPIC::~TOPIC() {}
MODE::~MODE() {}
KILL::~KILL() {}
