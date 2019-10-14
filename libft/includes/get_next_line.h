/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:45:44 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/04 17:25:02 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE	2048
# endif

# include "libft.h"
# include <limits.h>

int	get_next_line(const int fd, char **line);

#endif
