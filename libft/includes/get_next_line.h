/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:45:44 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/31 15:11:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE	2048
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# include "libft.h"
# include <limits.h>

int	get_next_line(const int fd, char **line);

#endif
