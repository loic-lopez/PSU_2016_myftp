/*
** utils_commands.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/utils_commands.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mar. mai 16 18:09:43 2017 Loïc Lopez
** Last update mar. mai 16 18:09:43 2017 Loïc Lopez
*/

#include "myftp.h"

bool 	subcommand(const char *src, const char *to_compare)
{
  int 	i;
  bool	is_supported;

  i = 0;
  is_supported = true;
  while (src[i] && to_compare[i])
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
