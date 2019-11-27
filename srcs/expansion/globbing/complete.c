/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:56:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/20 17:15:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "utils.h"

int			quote_char(t_compare *s, int x, int y, char c)
{
	x++;
	while (s->cmp[x] && s->cmp[x] != c && s->file[y])
	{
		if (s->cmp[x] != s->file[y])
			return (0);
		x++;
		y++;
	}
	if (s->cmp[x] == c)
		return (next_char(s, x + 1, y));
	else
		return (0);
}

int			standard_char(t_compare *s, int x, int y)
{
	int x_beg;

	x_beg = x;
	while (s->cmp[x] && s->file[y] &&
		(!is_glob_char(s->cmp[x]) || x_beg == x || is_escaped(s->cmp, x, 0))
		&& s->cmp[x] != '"')
	{
		if (!(s->cmp[x] == '\\') || is_escaped(s->cmp, x, 0))
		{
			//ft_printf("standard str->%s index->%d, char->%c, file->%s\n", s->cmp, x, s->cmp[x], s->file);
			if (s->cmp[x] != s->file[y])
				return (0);
			y++;
		}
		x++;
	}
	return (next_char(s, x, y));
}

int			next_char(t_compare *s, int x, int y)
{
	if (!is_escaped(s->cmp, x, 0))
	{
		//ft_printf("str->%s index->%d, char->%c, file->%s\n", s->cmp, x, s->cmp[x], s->file);
		if (s->cmp[x] == '*')
			return (wildcard_star(s, x, y));
		if (s->cmp[x] == '?')
			return (wildcard_question(s, x, y));
		if (s->cmp[x] == '[' && is_close_bracket(s->cmp, x))
			return (wildcard_bracket(s, x, y));
		if (s->cmp[x] == '"' || s->cmp[x] == '\'')
			return (quote_char(s, x, y, s->cmp[x]));
	}
	if (s->cmp[x])
	{
		if (!(s->file[y]))
			return (0);
		else
			return (standard_char(s, x, y));
	}
	if (s->len_find < y)
		s->len_find = y;
	if (!s->file[y] || !(s->l_pattern))
		return (1);
	return (0);
}

int			complete_str(char *cmp, char *file)
{
	int			ret;
	t_compare	s;

	if (!file || file[0] == '.')
		return (0);
	s.len_find = 0;
	s.l_pattern = 1;
	s.cmp = cmp;
	s.file = file;
	ret = next_char(&s, 0, 0);
	return (ret);
}
