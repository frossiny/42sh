/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lite_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:53:44 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/14 18:13:45 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	check_index(char *str, int i)
{
	if (str[i] == ' ')
		return (0);
	if (str[i] == '$')
		return (VAR);
	if (ft_strchr("|&<>;", str[i]))
		return (0);
	return (4);
}

int			lite_parser(t_cursor_pos *pos)
{
	int		i;

	i = pos->x_rel == pos->len_str ? pos->x_rel - 1 : pos->x_rel;
	if (check_index(pos->str, i) != 4)
		return (check_index(pos->str, i));
	while (--i >= 0)
	{
		if (pos->str[i] == '$')
			return (VAR);
		if (ft_strchr("|&;", pos->str[i]))
			return (CMD);
		if (pos->str[i] == ' ')
		{
			while (i > 0 && pos->str[i - 1] == ' ')
				i--;
			while (--i >= 0)
			{
				if (ft_strchr("|&;", pos->str[i]))
					return (CMD);
				if (pos->str[i] == ' ')
					return (FILE);
			}
			return (FILE);
		}
	}
	return (CMD);
}
