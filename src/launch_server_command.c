/*
** launch_server_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/launch_server_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 19:05:17 2017 Loïc Lopez
** Last update sam. mai 13 19:05:17 2017 Loïc Lopez
*/

#include "myftp.h"

const 		char	*g_available_commands[] =
{
	"CWD", "CDUP", "QUIT", "DELE", "PWD",
	"PASV", "PORT", "HELP",
	"NOOP", "RETR", "STOR", "LIST", "USER", "PASS",
};


bool	parse_command(t_ftp_server *ftp_server,
			  char const *command_to_verify, int current_client)
{
  size_t 	i;
  bool		is_supported;

  if ((ftp_server->client_command[current_client] == WAIT_LOGIN ||
      ftp_server->client_command[current_client] == WAIT_PASSWORD))
    is_supported = true;
  else
    is_supported = false;
  i = 0;
  while (i < sizeof(g_available_commands)
	     / sizeof(g_available_commands[0]))
    {
      if (command_to_verify == NULL)
	{
	  ftp_server->client_command[current_client] = STAND_BY;
	  is_supported = true;
	  break;
	}
      if (subcommand(command_to_verify, g_available_commands[i]))
	{
	  is_supported = true;
	  ftp_server->client_command[current_client] = (e_command)i;
	  break;
	}
      i++;
    }
  return (is_supported);
}

void	launch_server_command(t_ftp_server *ftp_server,
				   int current_client)
{
  char **cmd_actions;

  epur_command(ftp_server->buffer);
  if ((cmd_actions = str_to_wordtab(ftp_server->buffer, ' ')) == NULL)
    return;
  if (parse_command(ftp_server, cmd_actions[0], current_client))
    {
      if (ftp_server->client_command[current_client] == STAND_BY)
	return;
      execute_server_command(ftp_server, cmd_actions, current_client);
    }
  else
    dprintf(ftp_server->sd,
	    "501 Syntax Error: %s\r\n", cmd_actions[0]);
  free_2D_array(cmd_actions);
}