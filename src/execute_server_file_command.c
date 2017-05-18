/*
** execute_server_file_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_file_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. mai 18 17:42:18 2017 Loïc Lopez
** Last update jeu. mai 18 17:42:18 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_delete_and_parse_path(t_ftp_server *ftp_server,
					  int current_client, char const *file)
{
  char 	file_path[PATH_MAX];
  int 	index_file_path;
  int 	i;

  i = 0;
  index_file_path = 0;
  while (ftp_server->client_path[current_client][i])
    file_path[index_file_path++] =
	    ftp_server->client_path[current_client][i++];
  i = 0;
  while (file[i])
    file_path[index_file_path++] = file[i++];
  file_path[index_file_path] = 0;
  if (remove(file_path) < 0)
    dprintf(ftp_server->sd, "550 %s.\r\n", strerror(errno));
  else
    dprintf(ftp_server->sd, "250 %s file has been deleted.\r\n",
	    &file_path[strlen(ftp_server->server_path)]);
}

void	execute_delete(t_ftp_server *ftp_server,
			   int current_client, char **cmd_actions)
{
  if (cmd_actions[1][0] == '/')
    execute_delete_and_parse_path(ftp_server, current_client, &cmd_actions[1][1]);
  else
    execute_delete_and_parse_path(ftp_server, current_client, cmd_actions[1]);
}
