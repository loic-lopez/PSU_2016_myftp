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

void	execute_retr(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "150 Starting file download.\r\n");
  dprintf(ftp_server->sd, "226 File retrieve OK.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_stor(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "150 Starting file upload.\r\n");
  dprintf(ftp_server->sd, "226 file send OK.\r\n");
  (void)cmd_actions;
  (void)ftp_server;
  (void)current_client;
}
void	execute_list(t_ftp_server *ftp_server, int current_client, char **cmd_actions)
{
  dprintf(ftp_server->sd, "150 Here comes the directory listing.\r\n");
  dprintf(ftp_server->sd, "226 Directory send OK.\r\n");
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
