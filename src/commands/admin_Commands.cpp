/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_Commands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:07:38 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/25 17:09:01 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../server/Server.hpp"

// KICK <channel> <client> :[<message>]
void KICK::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		client->reply("need more args");
		return;
	}

	std::string name = args[0];
	std::string target = args[1];
	std::string reason = (args.size() >= 3 && args[2][0] != ':') ? args[2] : "No reason specified!";

	Channel *channel = client->get_channel();
	if (!channel || channel->get_name() != name)
	{
		client->reply("u r not in channel/channel doesnt exist");
		return;
	}
	// check if client is admin
	if (channel->get_admin() != client)
	{
		client->reply("unauthorized to kick");
		return;
	}
	Client *dest_client = serv->get_client(target);
	if (!dest_client)
	{
		client->reply("user not found");
		return;
	}
	channel->kick(client, dest_client, reason);
}

// TOPIC <channel> [<topicname>]
void TOPIC::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() < 1 || args.size() > 2)
	{
		client->reply("need more args");
		return;
	}

	std::string channelName = args[0];
	Channel *channel = serv->get_channel(channelName);
	if (!channel)
	{
		client->reply("no channel found");
		return;
	}
	if (channel->check_mode('t') && channel->get_admin() != client)
	{
		client->reply("ur not admin");
		return;
	}
	else
	{
		std::string topic = args[1];
		channel->set_topic(topic);
	}
	if (args.size() == 1)
	{
		std::string topic = "The topic of " + channelName + " is " + channel->get_topic();
		client->reply(topic);
	}
}

// MODE <nickname> <flags> (user)
// MODE <channel> <flags> [<args>]
void MODE::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		client->reply("need more args");
		return;
	}
}

///INVITE <NICK> <channel>
void INVITE::execute(Client* client, std::vector<std::string> args)
{
	if (args.size() != 2)
	{
		client->reply("args error");
		return;
	}

	std::string nickname = args[0];
	Client* target = serv->get_client(nickname);
	if (!target)
	{
		client->reply("user doesnt exist");
		return;
	}

	Channel* channel = serv.get_channel(args[1]);
	if (!channel)
	{
		client->reply("channel doesnt exist");
		return;
	}

	if (channel->get_admin() != client)
	{
		client->reply("unauthorized to kick");
		return;
	}

	if (channel->get_nick(nickname))
	{
		client->reply("user already in channel");
		return;
	}

	target->set_channel(channel);//???
	//add relevant msg here
}