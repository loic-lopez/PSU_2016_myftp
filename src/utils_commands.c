/*
** utils_commands.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/utils_commands.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mar. mai 16 18:09:43 2017 Loïc Lopez
** Last update mar. mai 16 18:09:43 2017 Loïc Lopez
*/

#include "myftp.h"

FILE	*get_file(t_ftp_server *ftp_server,
		      char **cmd_actions, char *cmd, int current_client)
{
  FILE	*fp;
  char 	path[PATH_MAX];

  if (cmd_actions[1] && cmd_actions[1][0] != '/')
    fp = popen(strcat(strcat(cmd, ftp_server->client_path[current_client]),
		      cmd_actions[1]), "r");
  else
    fp = popen(strcat(strcat(cmd, ftp_server->client_path[current_client]),
		      cmd_actions[1] ? cmd_actions[1]: ""), "r");
  dprintf(ftp_server->sd, "150 Here comes the directory listing.\r\n");
  while (fgets(path, sizeof(path) - 1, fp) != NULL)
    dprintf(ftp_server->sd, "%s", path);
  dprintf(ftp_server->sd, "226 Directory send OK.\r\n");
  return (fp);
}

bool 	subcommand(const char *src, const char *to_compare)
{
  int 	i;
  bool	is_supported;

  i = 0;
  is_supported = true;
  while (src[i] && to_compare[i])
    {
      if (src[i] != to_compare[i])
	{
	  is_supported = false;
	  break;
	}
      i++;
    }
  if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z'))
    is_supported = false;
  return (is_supported);
}


void	epur_command(char *command)
{
  int 	i;

  i = 0;
  if (!command)
    return;
  while (command[i])
    {
      if (command[i] == '\r')
	command[i] = ' ';
      i++;
    }
}
