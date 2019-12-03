/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:44:43 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/03 15:01:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "libft.h"

int			histo_cmp(const char *s1, const char *s2)
{
	size_t i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (0);
	if (!s2[i] && s1[i])
		return (0);
	return (1);
}

char		*exp_sub_pattern(char *str, int i, int type)
{
	int		y;
	char	*res;
	char	*tmp;

	if (!str)
		return (NULL);
	if (type)
	{
		y = i;
		while (str[y] && ft_isdigit(str[y]))
			y++;
		res = ft_strsub(str, i, y - i);
	}
	else
	{
		if ((tmp = ft_strchr(str + i, ' ')))
			res = ft_strsub(str, i, tmp - str - 1);
		else
			res = ft_strdup(str + i);
	}
	return (res);
}

void		maj_last_index(t_expansion *e, char *needle)
{
	if (!e || !needle)
		return ;
	e->i = e->i + ft_strlen(needle);
	e->li = e->i;
	e->i--;
	free(needle);
}
