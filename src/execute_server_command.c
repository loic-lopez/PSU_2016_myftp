/*
** execute_server_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 19:05:17 2017 Loïc Lopez
** Last update sam. mai 13 19:05:17 2017 Loïc Lopez
*/

#include "myftp.h"

void	parse_command(t_ftp_server *ftp_server)
{
  (void)ftp_server;
}

void	execute_server_command(t_ftp_server *ftp_server)
{

  getpeername(ftp_server->sd , (struct sockaddr*)&ftp_server->address,
	      (socklen_t*)&ftp_server->addrlen);
  printf("Host disconnected , ip %s , port %d \n",
	 inet_ntoa(ftp_server->address.sin_addr),
	 ntohs(ftp_server->address.sin_port));
  close(ftp_server->sd);
  ftp_server->client_socket[ftp_server->sd] = 0;
}