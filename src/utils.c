/*
** utils.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/utils.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 14:01:35 2017 Loïc Lopez
** Last update sam. mai 13 14:01:35 2017 Loïc Lopez
*/

#include "myftp.h"

void	verify_is_a_valid_directory(const char *src)
{
  DIR	*dir;

  if (!(dir = opendir(src)))
    {
      strcmp(src, "") == 0 ? (src = "NULL") : 0;
      fprintf(stderr, "%s: ", src);
      put_error();
    }
  closedir(dir);
}

void	fill_client_array(t_ftp_server *ftp_server, const char *str)
{
  int 	i;
  int 	j;

  j = -1;
  while (++j < ftp_server->max_clients)
    {
      i = -1;
      while (str[++i])
	ftp_server->client_path[j][i] = str[i];
      if (str[i - 1] != '/')
	ftp_server->client_path[j][i++] = '/';
      ftp_server->client_path[j][i] = 0;
    }
  j = -1;
  while (ftp_server->client_path[0][++j])
    ftp_server->server_path[j] = ftp_server->client_path[0][j];
  ftp_server->server_path[j] = 0;
}

void	fill_user_root_directory(t_ftp_server *ftp_server, const char *src)
{
  char *path;

  if (strcmp(src, ".") == 0 || strcmp(src, "./") == 0)
    {
      path = get_current_dir_name();
      fill_client_array(ftp_server, path);
      free(path);
    }
  else
    {
      verify_is_a_valid_directory(src);
      fill_client_array(ftp_server, src);
    }
}

void	free_2D_array(char **tab)
{
  int i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}

void	put_error()
{
  fprintf(stderr, "Error: %s\n", strerror(errno));
  exit(EXIT_FAILURE);
}