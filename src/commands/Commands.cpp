/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:24:54 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/24 15:26:35 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../server/Server.hpp"

// Base Command class implementation

Command::Command(Server *server) : serv(server) {}

Command::~Command() {}

// Derived class implementations

PASS::PASS(Server *server) : Command(server) {}

void PASS::execute(Client *client, std::vector<std::string> args)
{
	if (args.empty())
	{
		client->reply("need good pass");
		return;
	}

	if (client->get_state()) //== registered )
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

NICK::NICK(Server *server) : Command(server) {}

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

USER::USER(Server *server) : Command(server) {}

void USER::execute(Client *client, std::vector<std::string> args)
{

}

PM::PM(Server *server) : Command(server) {}

void PM::execute(Client *client, std::vector<std::string> args)
{

}

QUIT::QUIT(Server *server) : Command(server) {}

void QUIT::execute(Client *client, std::vector<std::string> args)
{

}

JOIN::JOIN(Server *server) : Command(server) {}

void JOIN::execute(Client *client, std::vector<std::string> args)
{

}

KICK::KICK(Server *server) : Command(server) {}

void KICK::execute(Client *client, std::vector<std::string> args)
{
	// Implement the execute logic for KICK command
	// ...
}

KILL::KILL(Server *server) : Command(server) {}

void KILL::execute(Client *client, std::vector<std::string> args)
{

}

MODE::MODE(Server *server) : Command(server) {}

void MODE::execute(Client *client, std::vector<std::string> args)
{

}
