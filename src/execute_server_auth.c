/*
** execute_server_auth.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_auth.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 17 17:01:18 2017 Loïc Lopez
** Last update mer. mai 17 17:01:18 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_user_login(t_ftp_server *ftp_server,
			       int current_client, char **cmd_actions)
{
  size_t i;

  if (strcmp(cmd_actions[0], "USER") == 0)
    {
      if (cmd_actions[1] == NULL)
	dprintf(ftp_server->sd, "331 Need account for login.\r\n");
      else
	{
	  ftp_server->client_command[current_client] = WAIT_PASSWORD;
	  dprintf(ftp_server->sd, "331 Please specify the password.\r\n");
	  i = 0;
	  while (cmd_actions[1][i])
	    {
	      ftp_server->last_login[i] = cmd_actions[1][i];
	      i++;
	    }
	}
    }
  else
    dprintf(ftp_server->sd, "530 Permission denied.\r\n");
}

void	execute_password(t_ftp_server *ftp_server,
			     int current_client, char **cmd_actions)
{
  if (strcmp(cmd_actions[0], "PASS") == 0)
    {
      if (cmd_actions[1] == NULL
	  && strcmp(ftp_server->last_login, "Anonymous") == 0)
	{
	  ftp_server->client_command[current_client] = STAND_BY;
	  dprintf(ftp_server->sd, "230 User logged in, proceed.\r\n");
	}
      else
	dprintf(ftp_server->sd, "530 Login incorrect.\r\n");
    }
  else
    dprintf(ftp_server->sd, "530 Please login with USER and PASS.\r\n");
}