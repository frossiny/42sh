/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:56:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/28 17:06:09 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

int			wildcard_bracket(char *cmp, char *file, int x, int y)
{
	int	end;
	int	i;

	end = x + 1;
	while ((cmp[end] && cmp[end] != ']') || (cmp[end] == ']' && x + 1 == end))
		end++;
	if (!cmp[end])
		return (0);
	while (++x != end)
	{
		if (cmp[x + 1] == '-' && cmp[x + 2] != ']' && cmp[x] <= cmp[x + 2])
		{
			i = 0;
			while (cmp[x] + i <= cmp[x + 2])
			{
				if (cmp[x] + i == file[y] && cmp[x] != '/')
					if (next_char(cmp, file, end + 1, y + 1))
						return (1);
				
				i++;
			}
			x = x + 2;
		}
		else if (cmp[x] == file[y])
			if (next_char(cmp, file, end + 1, y + 1))
				return (1);
	}
	return (0);
}

int			wildcard_star(char *cmp, char *file, int x, int y)
{
	while (file[y])	
	{
		if (next_char(cmp, file, x + 1, y))
			return (1);
		y++;	
	}
	return (next_char(cmp, file, x + 1, y));
}

int			wildcard_question(char *cmp, char *file, int x, int y)
{
	if (!file[y])
		return (0);
	return (next_char(cmp, file, x + 1, y + 1));
}

int			standard_char(char *cmp, char *file, int x, int y)
{
	while (cmp[x] && file[y] && !is_glob_char(cmp[x]))
	{
		if (cmp[x] != file[y])
			return (0);
		x++;
		y++;
	}
	return (next_char(cmp, file, x, y));
}

int			next_char(char *cmp, char *file, int x, int y)
{
	if (cmp[x] == '*')
		return (wildcard_star(cmp, file, x, y));
	if (cmp[x] == '?')
		return (wildcard_question(cmp, file, x, y));
	if (cmp[x] == '[')
		return (wildcard_bracket(cmp, file, x, y));
	if (cmp[x])
	{
		if (!file[y])
			return (0);
		else
			return (standard_char(cmp, file, x, y));
	}
	if (!file[y])
		return (1);
	else
		return (0);
}

int			complete_str(char *cmp, char *file)
{
	int	ret;

	if (!file || file[0] == '.')
		return (0);
	ret = next_char(cmp, file, 0, 0);
	return (ret);
}
