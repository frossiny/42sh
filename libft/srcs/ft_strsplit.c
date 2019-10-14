/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:37:13 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 10:21:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_size(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_count_w(const char *s, char c)
{
	int	i;
	int	count;

	if (!s || ft_strlen(s) == 0)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] == c)
				i++;
		}
		else
			i += ft_word_size(s + i, c);
	}
	count++;
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s
		|| !(tab = (char **)malloc(sizeof(char *) * (ft_count_w(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			tab[j++] = ft_strsub(s, i, ft_word_size(s + i, c));
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = 0;
	return (tab);
}
