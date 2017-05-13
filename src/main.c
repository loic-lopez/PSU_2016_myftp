/*
** main.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/main.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. mai 13 12:00:12 2017 Loïc Lopez
** Last update sam. mai 13 12:00:12 2017 Loïc Lopez
*/

#include "myftp.h"

int	main(int ac, char **av)
{
  if (ac == 1 || ac > 3)
    {
      fprintf(stderr, "Usage: ./%s port path", av[0]);
      return (0);
    }
  launch_server(atoi(av[1]), av[2]);
  return (0);
}