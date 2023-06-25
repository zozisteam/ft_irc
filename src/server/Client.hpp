/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:10:46 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/25 15:06:18 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/poll.h>
#include <sys/socket.h>
#include <string>
#include <vector>
// #include "Channel.hpp"
class Channel;

class Client
{
private:
	int fd;
	int port;
	std::string nick;
	std::string uname;
	std::string name;
	std::string host;
	// add smth for the channel
	// 0handshake 1login 2registed -1disconnected
	int state;

	// constructor
	Client();
	// cpy constructor
	Client(const Client &src);

public:
	Client(int fd, int port, const std::string &host);
	~Client();

	// setters
	void set_state(int state);
	void set_nick(const std::string &nick);
	void set_uname(const std::string &uname);
	void set_name(const std::string &name);
	void set_channel(Channel *channel);

	// getters
	int get_fd() const;
	int get_port() const;
	int get_state();
	std::string get_nick() const;
	std::string get_uname() const;
	std::string get_name() const;
	std::string get_host() const;
	Channel* get_channel();
	// get prefix???


	// send recieve actions
	void send(const std::string &msg) const;
	void reply(const std::string &msg);
	// welcome msg as in irc
	void welcome();
	// client actions; join/leave
	int join_channel(int num);
	int leave_channel(int num);
};

#endif