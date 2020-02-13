/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:45:44 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/13 14:26:39 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <limits.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE	2048
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

typedef struct	s_gnl
{
	char	b[OPEN_MAX][BUFF_SIZE];
	int		i[OPEN_MAX];
	int		c[OPEN_MAX];
	int		j;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
