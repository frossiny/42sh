/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:48:56 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/04 15:35:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int			wildcard_bracket_normal(t_compare s, int x, int y, int end)
{
	int	i;

	while (++x != end)
	{
		if (s.cmp[x + 1] == '-' && s.cmp[x + 2] != ']'
				&& s.cmp[x] <= s.cmp[x + 2])
		{
			i = 0;
			while (s.cmp[x] + i <= s.cmp[x + 2])
			{
				if (s.cmp[x] + i == s.file[y] && s.cmp[x] != '/')
					if (next_char(s, end + 1, y + 1))
						return (1);
				i++;
			}
			x = x + 2;
		}
		else if (s.cmp[x] == s.file[y])
			if (next_char(s, end + 1, y + 1))
				return (1);
	}
	return (0);
}

int			wildcard_bracket_inverse(t_compare s, int x, int y, int end)
{
	int	i;

	while (++x != end)
	{
		if (s.cmp[x + 1] == '-' && s.cmp[x + 2] != ']'
				&& s.cmp[x] <= s.cmp[x + 2])
		{
			i = 0;
			while (s.cmp[x] + i <= s.cmp[x + 2])
			{
				if (s.cmp[x] + i == s.file[y] && s.cmp[x] != '/')
					return (0);
				i++;
			}
			x = x + 2;
		}
		else if (s.cmp[x] == s.file[y])
			return (0);
	}
	return (next_char(s, end + 1, y + 1));
}

int			wildcard_bracket(t_compare s, int x, int y)
{
	int	end;

	if (!s.file[y])
		return (0);
	end = x + 1;
	while ((s.cmp[end] && s.cmp[end] != ']')
			|| (s.cmp[end] == ']' && x + 1 == end)
			|| (end == x + 2 && s.cmp[end - 1] == '!' && s.cmp[end] == ']'))
		end++;
	if (!s.cmp[end])
		return (0);
	if (s.cmp[x + 1] != '!')
		return (wildcard_bracket_normal(s, x, y, end));
	else
		return (wildcard_bracket_inverse(s, x + 1, y, end));
}

int			wildcard_star(t_compare s, int x, int y)
{
	while (s.file[y])
	{
		if (next_char(s, x + 1, y))
			return (1);
		y++;
	}
	return (next_char(s, x + 1, y));
}

int			wildcard_question(t_compare s, int x, int y)
{
	if (!s.file[y])
		return (0);
	return (next_char(s, x + 1, y + 1));
}
