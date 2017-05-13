/*
** server.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/server.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 12:50:47 2017 Loïc Lopez
** Last update sam. mai 13 12:50:47 2017 Loïc Lopez
*/

#include "myftp.h"

void	init_server(t_ftp_server *ftp_server, int port)
{
  int 	i;

  i = -1;
  ftp_server->port = port;
  ftp_server->max_clients = 30;
  ftp_server->opt = true;
  while (++i < ftp_server->max_clients)
    ftp_server->client_socket[i] = 0;
  if((ftp_server->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    put_error();
  if(setsockopt(ftp_server->master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&ftp_server->opt, sizeof(ftp_server->opt)) < 0)
    put_error();
  ftp_server->address.sin_family = AF_INET;
  ftp_server->address.sin_addr.s_addr = INADDR_ANY;
  ftp_server->address.sin_port = htons(ftp_server->port);
  if (bind(ftp_server->master_socket,
	   (struct sockaddr *)&ftp_server->address,
	   sizeof(ftp_server->address)) < 0)
   put_error();
  if (listen(ftp_server->master_socket, 3) < 0)
    put_error();
  ftp_server->addrlen = sizeof(ftp_server->address);
}

void	launch_server(int port, const char *home_user)
{
  t_ftp_server	ftp_server;

  init_server(&ftp_server, port);
  (void)home_user;
}
