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

void	init_clients(t_ftp_server *ftp_server)
{
  int 	i;

  i = -1;
  while (++i < ftp_server->max_clients)
    {
      ftp_server->client_socket[i] = 0;
      ftp_server->client_command[i] = WAIT_LOGIN;
    }
}

void	init_server(t_ftp_server *ftp_server, int port, const char *home_user)
{
  int 	options;

  options = 1;
  ftp_server->port = port;
  ftp_server->max_clients = 30;
  ftp_server->master_socket = 0;
  init_clients(ftp_server);
  if((ftp_server->master_socket = socket(AF_INET , SOCK_STREAM , 0)) < 0)
    put_error();
  if(setsockopt(ftp_server->master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&options, sizeof(int)) < 0)
    put_error();
  ftp_server->address.sin_family = AF_INET;
  ftp_server->address.sin_addr.s_addr = INADDR_ANY;
  ftp_server->address.sin_port = htons(ftp_server->port);
  if (bind(ftp_server->master_socket,
	   (struct sockaddr *)&ftp_server->address,
	   sizeof(ftp_server->address)) < 0
      || listen(ftp_server->master_socket, 3) < 0)
   put_error();
  ftp_server->addrlen = sizeof(ftp_server->address);
  fill_user_root_directory(ftp_server, home_user);
  chdir(ftp_server->client_path[0]);
}

void	incomming_connection(t_ftp_server *ftp_server)
{
  int 	i;
  if (FD_ISSET(ftp_server->master_socket, &ftp_server->readfds))
    {
      i = -1;
      if ((ftp_server->new_socket =
		   accept(ftp_server->master_socket,
			  (struct sockaddr *)&ftp_server->address,
			  (socklen_t*)&ftp_server->addrlen)) < 0)
	put_error();
      while (++i < ftp_server->max_clients)
	if(ftp_server->client_socket[i] == 0)
	  {
	    ftp_server->client_socket[i] = ftp_server->new_socket;
	    dprintf(ftp_server->new_socket, "220 Connection Etablished\r\n");
	    break;
	  }
    }
}

void	other_operations(t_ftp_server *ftp_server)
{
  int 	i;

  i = -1;
  while (++i < ftp_server->max_clients)
    {
      ftp_server->sd = ftp_server->client_socket[i];
      if (FD_ISSET(ftp_server->sd, &ftp_server->readfds))
	{
	  ftp_server->command = get_next_line(ftp_server->sd);
	  if (ftp_server->command != NULL)
	    launch_server_command(ftp_server, i);
	  free(ftp_server->command);
	}
    }
}

void	launch_server(int port, const char *home_user)
{
  t_ftp_server	ftp_server;
  int 		i;

  init_server(&ftp_server, port, home_user);
  while (true)
    {
      FD_ZERO(&ftp_server.readfds);
      FD_SET(ftp_server.master_socket, &ftp_server.readfds);
      ftp_server.max_sd = ftp_server.master_socket;
      i = -1;
      while (++i < ftp_server.max_clients)
	{
	  ftp_server.sd = ftp_server.client_socket[i];
	  if(ftp_server.sd > 0)
	    FD_SET(ftp_server.sd , &ftp_server.readfds);
	  if(ftp_server.sd > ftp_server.max_sd)
	    ftp_server.max_sd = ftp_server.sd;
	}
      ftp_server.activity = select(ftp_server.max_sd + 1 , &ftp_server.readfds , NULL , NULL , NULL);
      if (ftp_server.activity >= 0 && errno != EINTR)
	{
	  incomming_connection(&ftp_server);
	  other_operations(&ftp_server);
	}
    }
}
