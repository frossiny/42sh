/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:56:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/04 15:37:54 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int			quote_char(t_compare s, int x, int y, char c)
{
	x++;
	while (s.cmp[x] && s.cmp[x] != c && s.file[y])
	{
		if (s.cmp[x] != s.file[y])
			return (0);
		x++;
		y++;
	}
	if (s.cmp[x] == c)
		return (next_char(s, x + 1, y));
	else
		return (0);
}

int			standard_char(t_compare s, int x, int y)
{
	while (s.cmp[x] && s.file[y] && !is_glob_char(s.cmp[x]) && s.cmp[x] != '"')
	{
		if (s.cmp[x] != s.file[y])
			return (0);
		x++;
		y++;
	}
	return (next_char(s, x, y));
}

#include "ft_printf.h"
int			next_char(t_compare s, int x, int y)
{
	if (s.cmp[x] == '*')
		return (wildcard_star(s, x, y));
	if (s.cmp[x] == '?')
		return (wildcard_question(s, x, y));
	if (s.cmp[x] == '[')
		return (wildcard_bracket(s, x, y));
	if (s.cmp[x] == '"' || s.cmp[x] == '\'')
		return (quote_char(s, x, y, s.cmp[x]));
	if (s.cmp[x])
	{
		if (!(s.file[y]))
			return (0);
		else
			return (standard_char(s, x, y));
	}
	if (!s.file[y])
		return (1);
	return (0);
}

int			complete_str(char *cmp, char *file)
{
	int			ret;
	t_compare	s;

	if (!file || file[0] == '.')
		return (0);
	s.cmp = cmp;
	s.file = file;
	ret = next_char(s, 0, 0);
	return (ret);
}
