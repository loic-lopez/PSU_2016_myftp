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

void	execute_delete(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "550 Failed to open file.");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_pasv(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "227 Entering Passive Mode.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

void	execute_port(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "200 PORT command successful.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}

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

void	execute_noop(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "200 %s ok.\r\n", cmd_actions[0]);
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
  dprintf(ftp_server->sd, "150 Here comes the directory listing.");
  dprintf(ftp_server->sd, "226 Directory send OK.");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
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
