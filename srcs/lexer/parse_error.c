/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:29:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 14:54:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		parse_error(const char *str, int ret)
{
	ft_dprintf(2, "42sh: parse error near '%s'\n", str);
	return (ret);
}
