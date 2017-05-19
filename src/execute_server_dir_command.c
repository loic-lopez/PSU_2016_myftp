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

bool	check_if_destination_exists(t_ftp_server *ftp_server,
					const char *dest, int current_client)
{
  DIR	*dir;
  char 	complete_path[PATH_MAX];
  int 	path;
  int 	i;

  i = 0;
  path = 0;
  if (dest[0] == '/')
    while (ftp_server->server_path[i])
      complete_path[path++] = ftp_server->server_path[i++];
  else
    while (ftp_server->client_path[current_client][i])
    	complete_path[path++] = ftp_server->client_path[current_client][i++];
  i = 0;
  while (dest[i])
    complete_path[path++] = dest[i++];
  complete_path[path] = 0;
  if (!(dir = opendir(complete_path)))
    return (false);
  closedir(dir);
  return (true);
}

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
  size_t 	i;
  int	 	path;

  if (cmd_actions[1] && strcmp(cmd_actions[1], ".") == 0)
    dprintf(ftp_server->sd, "250 Directory successfully changed.\r\n");
  else if (cmd_actions[1] && strcmp(cmd_actions[1], "..") == 0)
    execute_cdup(ftp_server, current_client, cmd_actions);
  else if (cmd_actions[1] == NULL ||
	  !check_if_destination_exists(ftp_server, cmd_actions[1],
				       current_client))
    dprintf(ftp_server->sd, "550 Failed to change directory.\r\n");
  else
    {
      path = 0;
      cmd_actions[1][0] == '/' ? (path++, i = strlen(ftp_server->server_path)):
	(i = strlen(ftp_server->client_path[current_client]));
      while (cmd_actions[1][path])
	ftp_server->client_path[current_client][i++] = cmd_actions[1][path++];
      if (ftp_server->client_path[current_client][i - 1] != '/')
	ftp_server->client_path[current_client][i++] = '/';
      ftp_server->client_path[current_client][i] = 0;
      fprintf(stderr, &cmd_actions[1][path]);
      dprintf(ftp_server->sd, "250 Directory successfully changed.\r\n");
    }
}

void	execute_cdup(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  size_t i;

  if (strcmp(ftp_server->client_path[current_client],
	     ftp_server->server_path) != 0)
    {
      i = strlen(ftp_server->client_path[current_client]) - 1;
      memmove(&ftp_server->client_path[current_client][i],
	      &ftp_server->client_path[current_client][i + 1],
	      strlen(ftp_server->client_path[current_client]) - i);
      while (ftp_server->client_path[current_client][--i] != '/')
	{
	  memmove(&ftp_server->client_path[current_client][i],
		  &ftp_server->client_path[current_client][i + 1],
		  strlen(ftp_server->client_path[current_client]) - i);
	}
    }
  dprintf(ftp_server->sd, "250 %s: Directory successfully changed.\r\n",
	  cmd_actions[0]);
}
