/*
** myftp.h for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/myftp.h
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 11:59:40 2017 Loïc Lopez
** Last update sam. mai 13 11:59:40 2017 Loïc Lopez
*/

#ifndef PSU_2016_MYFTP_MYFTP_H
#define PSU_2016_MYFTP_MYFTP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdbool.h>

typedef	struct			s_ftp_server
{
  bool 				opt;
  int 				master_socket;
  int 				addrlen;
  int  				new_socket;
  int 				client_socket[30];
  int 				max_clients;
  int				activity;
  int 				valread;
  int 				sd;
  int 				max_sd;
  struct 	sockaddr_in 	address;
  char 				buffer[1025];
  fd_set 			readfds;
  int 				port;
}				t_ftp_server;

void	launch_server(int port, char const *home_user);
void	init_server(t_ftp_server *ftp_server, int port);
void	put_error(const char *msg);

#endif /* PSU_2016_MYFTP_MYFTP_H */