/*
** get_next_line.h for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/get_next_line.h
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 15 15:35:43 2017 Loïc Lopez
** Last update lun. mai 15 15:35:43 2017 Loïc Lopez
*/
#ifndef PSU_2016_MYFTP_GET_NEXT_LINE_H
#define PSU_2016_MYFTP_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef READ_SIZE
#  define READ_SIZE (8)
# endif /* !READ_SIZE */

# ifndef BUF
#  define BUF (READ_SIZE + 1)
# endif /* !BUF */

char   	*get_next_line(const int fd);

#endif //PSU_2016_MYFTP_GET_NEXT_LINE_H