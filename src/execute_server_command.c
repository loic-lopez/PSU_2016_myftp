/*
** execute_server_command.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/execute_server_command.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 19:05:17 2017 Loïc Lopez
** Last update sam. mai 13 19:05:17 2017 Loïc Lopez
*/

#include "myftp.h"


bool	parse_command(t_ftp_server *ftp_server, char *command_to_verify)
{
  size_t 	i = 0;
  bool		is_supported;
  const 		char	*command[] =
	  {
		  "CWD", "CDUP", "QUIT", "DELE", "PWD", "PASV", "PORT", "HELP",
		  "NOOP", "RETR", "STOR", "LIST", "USER", "PASS",
	  };
  is_supported = false;
  while (i < sizeof(command) / sizeof(command[0]))
    {
      if (subcommand(command_to_verify, command[i]))
	{
	  is_supported = true;

	}
      i++;
    }
  if (!is_supported)
    dprintf(ftp_server->sd, "501 Syntax Error: %s\r\n", command_to_verify);
  return (is_supported);
}

void	execute_server_command(t_ftp_server *ftp_server)
{
  char **cmd_actions;

  epur_command(ftp_server->buffer);
  cmd_actions = str_to_wordtab(ftp_server->buffer, ' ');
  if (parse_command(ftp_server, cmd_actions[0]))
    printf("toto");
  else
    return;
  /*
  getpeername(ftp_server->sd , (struct sockaddr*)&ftp_server->address,
	      (socklen_t*)&ftp_server->addrlen);
  printf("Host disconnected , ip %s , port %d \n",
	 inet_ntoa(ftp_server->address.sin_addr),
	 ntohs(ftp_server->address.sin_port));
  close(ftp_server->sd);
  ftp_server->client_socket[ftp_server->sd] = 0;
   */
}