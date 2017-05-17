/*
** execute_server_dir_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_dir_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 17 17:21:52 2017 Loïc Lopez
** Last update mer. mai 17 17:21:52 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_pwd(t_ftp_server *ftp_server,
			int current_client, char **cmd_actions)
{
  if (errno != EACCES)
    {
      if (strcmp(ftp_server->server_path,
		 ftp_server->client_path[current_client]) == 0)
	dprintf(ftp_server->sd, "257 %s: \"%s\"\r\n", cmd_actions[0], "/");
      else
	dprintf(ftp_server->sd, "257 %s: \"%s%s\"\r\n", cmd_actions[0], "/",
		&ftp_server->client_path[current_client]
		[strlen(ftp_server->server_path)]);
    }
  else
    dprintf(ftp_server->sd, "553 Permission Denied\r\n");
}

void	execute_cwd(t_ftp_server *ftp_server,
			int current_client, char **cmd_actions)
{
  (void)current_client;
  (void)cmd_actions;
  (void)ftp_server;
}

void	execute_cdup(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  (void)ftp_server;
  (void)current_client;
  (void)cmd_actions;
}