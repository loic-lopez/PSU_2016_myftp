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

void	free_2D_array(char **tab)
{
  int i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}

bool 	subcommand(const char *src, const char *to_compare)
{
  int 	i;
  bool	is_supported;

  i = 0;
  is_supported = true;
  while (to_compare[i])
    {
      if (src[i] != to_compare[i])
	{
	  is_supported = false;
	  break;
	}
      i++;
    }
  if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z'))
    is_supported = false;
  return (is_supported);
}


void	epur_command(char *command)
{
  int 	i;

  i = 0;
  while (command[i])
    {
      if (command[i] == '\r' || command[i] == '\n')
	command[i] = ' ';
      i++;
    }
}

void	put_error()
{
  fprintf(stderr, "Error: %s\n", strerror(errno));
  exit(EXIT_FAILURE);
}