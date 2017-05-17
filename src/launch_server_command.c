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

bool	parse_command(t_ftp_server *ftp_server,
			  char const *command_to_verify,
			  int current_client, bool *syntax_error)
{
  size_t 	i;
  bool		is_supported;
  const 		char	*available_commands[] =
	  {
		  "CWD", "CDUP", "QUIT", "DELE", "PWD", "PASV", "PORT",
		  "HELP", "NOOP", "RETR", "STOR", "LIST", "USER", "PASS",
	  };

  is_supported = false;
  *syntax_error = true;
  i = 0;
  while (i < sizeof(available_commands) / sizeof(available_commands[0]))
    {
      if (subcommand(command_to_verify, available_commands[i]))
	{
	  if ((ftp_server->client_command[current_client] != WAIT_LOGIN &&
	      ftp_server->client_command[current_client] != WAIT_PASSWORD)
	      || (strcmp(command_to_verify, "QUIT") == 0))
	    ftp_server->client_command[current_client] = (e_command)i;
	  *syntax_error = false;
	  is_supported = true;
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
  bool	syntax_error;

  syntax_error = false;
  epur_command(ftp_server->command);
  if ((cmd_actions = str_to_wordtab(ftp_server->command, ' ')) == NULL)
    return;
  if (parse_command(ftp_server, cmd_actions[0],
		    current_client, &syntax_error) && syntax_error == false)
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