/*
** execute_server_port_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_port_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. mai 19 21:25:58 2017 Loïc Lopez
** Last update ven. mai 19 21:25:58 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_pasv(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "227 Entering Passive Mode.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_port(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "200 PORT command successful.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}