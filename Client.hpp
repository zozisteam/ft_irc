/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:10:46 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/03 19:36:35 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/poll.h>
#include <sys/socket.h>
#include <string>
#include <vector>

class Client
{
	private:
		int fd;
		int port;
		std::string nick;
		std::string uname;
		std::string name;
		std::string host;
		//add smth for the channel
		//0handshake 1login 2registed -1disconnected
		int state;

		//constructor
		Client();
		//cpy constructor
		Client(const Client &src);

	public:
		Client(int fd, int port, const std::string &host);
		~Client();

		//setters
		//getters
		//check state
		//send recieve actions
		//void send(const string message) const;
		//void reply(const string reply);
		//welcome msg as in irc

		//client actions; join/leave
};

#endif