/*
** execute_server_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. mai 14 18:24:00 2017 Loïc Lopez
** Last update dim. mai 14 18:24:00 2017 Loïc Lopez
*/

#include "myftp.h"

void	close_client_connection(t_ftp_server *ftp_server, int current_client)
{
  /*
  getpeername(ftp_server->sd , (struct sockaddr*)&ftp_server->address,
	      (socklen_t*)&ftp_server->addrlen);
	      */
  dprintf(ftp_server->sd, "221 Connection Closed by Host\r\n");
  close(ftp_server->sd);
  ftp_server->client_socket[current_client] = 0;
}

void	execute_server_command(t_ftp_server *ftp_server, char **cmd_actions)
{
  (void)ftp_server;
  (void)cmd_actions;
}