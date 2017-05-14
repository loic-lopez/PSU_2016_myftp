/*
** execute_server_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. mai 14 18:24:00 2017 Loïc Lopez
** Last update dim. mai 14 18:24:00 2017 Loïc Lopez
*/

#include "myftp.h"

void	execute_cwd(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)ftp_server;
  (void)current_client;
  (void)cmd_actions;
}
void	execute_cdup(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)ftp_server;
  (void)current_client;
  (void)cmd_actions;
}
void	execute_quit(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  dprintf(ftp_server->sd, "221 %s Confirmed: Connection Closed by Host\r\n",
	  cmd_actions[0]);
  close(ftp_server->sd);
  ftp_server->client_socket[current_client] = 0;
  ftp_server->client_command[current_client] = WAIT_LOGIN;
}

void	execute_delete(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_pwd(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_pasv(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_port(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_help(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_noop(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_retr(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_stor(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_list(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_user_login(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  if (strcmp(cmd_actions[0], "USER") == 0)
    {
      if (cmd_actions[1] == NULL)
	dprintf(ftp_server->sd, "332 Need account for login.\r\n");
      else if (strcmp(cmd_actions[1], "Anonymous") == 0)
	  {
	    ftp_server->client_command[current_client] = WAIT_PASSWORD;
	    dprintf(ftp_server->sd, "331 User name okay, need password.\r\n");
	  }
      else
	  dprintf(ftp_server->sd, "430 Invalid username or password.\r\n");
    }
  else
    dprintf(ftp_server->sd, "530 Not logged in\r\n");
}

void	execute_password(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  if (strcmp(cmd_actions[0], "PASS") == 0)
    {
      if (cmd_actions[1] == NULL)
	  {
	    ftp_server->client_command[current_client] = STAND_BY;
	    dprintf(ftp_server->sd, "230 User logged in, proceed.\r\n");
	  }
      else
	  dprintf(ftp_server->sd, "430 Invalid username or password\r\n");
    }
  else
    dprintf(ftp_server->sd, "530 Not logged in\r\n");
}

void	execute_server_command(t_ftp_server *ftp_server,
				   char **cmd_actions, int current_client)
{
  void	(*server_functions[])(t_ftp_server *, int, char **) =
	  {
		  execute_cwd, execute_cdup, execute_quit, execute_delete,
		  execute_pwd, execute_pasv, execute_port, execute_help,
		  execute_noop, execute_retr, execute_stor, execute_list,
		  execute_user_login, execute_password
	  };
  if (ftp_server->client_command[current_client] == WAIT_LOGIN)
    execute_user_login(ftp_server, current_client, cmd_actions);
  else if (ftp_server->client_command[current_client] == WAIT_PASSWORD)
      execute_password(ftp_server, current_client, cmd_actions);
  else
      server_functions[ftp_server->client_command[current_client]]
		(ftp_server, current_client, cmd_actions);
}