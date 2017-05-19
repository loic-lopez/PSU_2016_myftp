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

void	execute_list(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  FILE 	*fp;
  DIR	*dir;
  char 	*cmd;

  if (!(cmd = malloc(sizeof(char) * PATH_MAX)))
    return;
  strcpy(cmd, ftp_server->server_path);
  if (cmd_actions[1])
    strcat(cmd, cmd_actions[1]);
  if (!(dir = opendir(cmd)))
    {
      dprintf(ftp_server->sd, "150 Here comes the directory listing.\r\n");
      dprintf(ftp_server->sd, "226 Directory send OK.\r\n");
    }
  else
    {
      strcpy(cmd, "/bin/ls -l ");
      fp = get_file(ftp_server, cmd_actions, cmd);
      pclose(fp);
      closedir(dir);
    }
  free(cmd);
  (void)current_client;
}

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

void	execute_retr(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  char *line;
  int 	file;
  char 	tmp_PATH[PATH_MAX];

  if (!cmd_actions[1])
    dprintf(ftp_server->sd, "550 Failed to open file.\r\n");
  else
    {
      strcpy(tmp_PATH, ftp_server->server_path);
      strcat(tmp_PATH, cmd_actions[1]);
      if ((file = open(tmp_PATH, O_RDONLY)) == -1)
	dprintf(ftp_server->sd, "550 %s\r\n", strerror(errno));
      else
	{
	  dprintf(ftp_server->sd, "150 Starting file download.\r\n");
	  while ((line = get_next_line(file)))
	    {
	      dprintf(ftp_server->sd, "%s\r\n", line);
	      free(line);
	    }
	  close(file);
	}
      dprintf(ftp_server->sd, "226 File retrieve OK.\r\n");
    }
  (void)current_client;
}

void	execute_stor(t_ftp_server *ftp_server,
			 int current_client, char **cmd_actions)
{
  char *line;
  int 	file;
  char 	tmp_PATH[PATH_MAX];

  if (!cmd_actions[1])
    dprintf(ftp_server->sd, "550 No file given.\r\n");
  else
    {
      strcpy(tmp_PATH, ftp_server->server_path);
      strcat(tmp_PATH, cmd_actions[1]);
      if ((file = open(tmp_PATH, O_CREAT | O_WRONLY)) == -1)
	dprintf(ftp_server->sd, "550 %s\r\n", strerror(errno));
      else
	{
	  dprintf(ftp_server->sd, "150 Starting file upload.\r\n");
	  while ((line = get_next_line(file)))
	    {
	      dprintf(file, line);
	      free(line);
	    }
	  dprintf(ftp_server->sd, "226 file send OK.\r\n");
	  close(file);
	}
    }
  (void)current_client;
}