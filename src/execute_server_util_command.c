/*
** execute_server_util_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_util_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. mai 18 16:10:50 2017 Loïc Lopez
** Last update jeu. mai 18 16:10:50 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_help(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  size_t i;
  const 		char	*available_commands[] =
	  {
		  "CWD", "CDUP", "QUIT", "DELE", "PWD", "PASV", "PORT",
		  "HELP", "NOOP", "RETR", "STOR", "LIST", "USER", "PASS",
	  };

  i = 0;
  (void)current_client;
  dprintf(ftp_server->sd, "214-The following commands are recognized.");
  while (i < sizeof(available_commands) / sizeof(available_commands[0]))
    {
      if (i % 4 == 0)
	dprintf(ftp_server->sd, "\r\n %3s", "");
      if (strlen(available_commands[i]) == 3)
	dprintf(ftp_server->sd, "%s%3s", available_commands[i], "");
      else
	dprintf(ftp_server->sd, "%s%2s", available_commands[i], "");
      i++;
    }
  dprintf(ftp_server->sd, "\r\n214 %s OK.\r\n", cmd_actions[0]);
}