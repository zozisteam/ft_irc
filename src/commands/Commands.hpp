/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:09:42 by alalmazr          #+#    #+#             */
/*   Updated: 2023/06/24 15:26:42 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../server/Server.hpp"
#include <numeric>
#include <string>
#include <vector>

class Command;
class Server;

class Command
{
protected:
    Server* serv;
    std::vector<std::string> args;
    std::string cmd;

    bool is_valid_mode(char c);

public:
    Command(Server* server);
    virtual ~Command();

    virtual void execute(Client* client, std::vector<std::string> args) = 0;
};

class PASS : public Command
{
public:
    PASS(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class NICK : public Command
{
public:
    NICK(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class USER : public Command
{
public:
    USER(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class PM : public Command
{
public:
    PM(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class QUIT : public Command
{
public:
    QUIT(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class JOIN : public Command
{
public:
    JOIN(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class KICK : public Command
{
public:
    KICK(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class KILL : public Command
{
public:
    KILL(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

class MODE : public Command
{
public:
    MODE(Server* server);
    void execute(Client* client, std::vector<std::string> args) override;
};

#endif