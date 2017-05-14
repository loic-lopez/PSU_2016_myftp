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

extern	const 		char	*g_available_commands[];

typedef enum			e_command
{
  CWD = 0,
  CDUP = 1,
  QUIT = 2,
  DELE = 3,
  PWD = 4,
  PASV = 5,
  PORT = 6,
  HELP = 7,
  NOOP = 8,
  RETR = 9,
  STOR = 10,
  LIST = 11,
  USER = 12,
  PASS = 13,
  STAND_BY = 14,
  WAIT_LOGIN = 15,
  WAIT_PASSWORD = 16,
}				e_command;

typedef	struct			s_ftp_server
{
  int 				master_socket;
  int 				addrlen;
  int  				new_socket;
  int 				client_socket[30];
  e_command			client_command[30];
  int 				max_clients;
  int				activity;
  ssize_t valread;
  int 				sd;
  int 				max_sd;
  struct 	sockaddr_in 	address;
  char 				buffer[1025];
  fd_set 			readfds;
  int 				port;
}				t_ftp_server;

void	launch_server(int port, char const *home_user);
void	init_server(t_ftp_server *ftp_server, int port);
void	init_clients(t_ftp_server *ftp_server);
void	incomming_connection(t_ftp_server *ftp_server);
void	other_operations(t_ftp_server *ftp_server);
void	launch_server_command(t_ftp_server *ftp_server,
				   int current_client);
bool	parse_command(t_ftp_server *ftp_server,
			  char const *command_to_verify,
			  int current_client);
char	**str_to_wordtab(char *str, char c);
void	epur_command(char *command);
bool 	subcommand(const char *src, const char *to_compare);
void	put_error();
void	execute_server_command(t_ftp_server *ftp_server,
				   char **cmd_actions);
void	close_client_connection(t_ftp_server *ftp_server,
				    int current_client);
void	free_2D_array(char **tab);

#endif /* PSU_2016_MYFTP_MYFTP_H */