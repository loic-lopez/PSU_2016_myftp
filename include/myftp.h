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

#define _GNU_SOURCE
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
#include <limits.h>
#include <dirent.h>
#include "get_next_line.h"

#ifndef PATH_MAX
 #define PATH_MAX 4096
#endif

char 	*get_current_dir_name(void);
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
  char 				client_path[30][PATH_MAX];
  bool				client_already_connected[30];
  int 				max_clients;
  int				activity;
  int 				sd;
  int 				max_sd;
  struct 	sockaddr_in 	address;
  char 				*command;
  fd_set 			readfds;
  int 				port;
  char 				server_path[PATH_MAX];
  char 				last_login[PATH_MAX];
}				t_ftp_server;

void	launch_server(int port, char const *home_user);
void	init_server(t_ftp_server *ftp_server, int port, const char *);
void	init_clients(t_ftp_server *ftp_server);
void	incomming_connection(t_ftp_server *ftp_server);
void	other_operations(t_ftp_server *ftp_server);
void	launch_server_command(t_ftp_server *ftp_server,
				   int current_client);
bool	parse_command(t_ftp_server *ftp_server,
			  char const *command_to_verify,
			  int current_client, bool *syntax_error);
char	**str_to_wordtab(char *str, char c);
void	epur_command(char *command);
bool 	subcommand(const char *src, const char *to_compare);
void	put_error();
void	free_2D_array(char **tab);
void	fill_user_root_directory(t_ftp_server *ftp_server, const char *src);
void	execute_server_command(t_ftp_server *ftp_server,
				   char **cmd_actions, int current_client);
void	execute_user_login(t_ftp_server *ftp_server,
			       int current_client, char **cmd_actions);
void	execute_password(t_ftp_server *ftp_server,
			     int current_client, char **cmd_actions);
void	execute_pwd(t_ftp_server *ftp_server,
			int current_client, char **cmd_actions);
void	execute_cwd(t_ftp_server *ftp_server,
			int current_client, char **cmd_actions);
void	execute_cdup(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions);
void	execute_quit(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions);

#endif /* PSU_2016_MYFTP_MYFTP_H */