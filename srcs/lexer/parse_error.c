/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:29:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:50:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		parse_error(const char *str, size_t len, int ret)
{
	write(2, "21sh: parse error near '", 24);
	write(2, str, len);
	ft_putstr_fd("'\n", 2);
	return (ret);
}
