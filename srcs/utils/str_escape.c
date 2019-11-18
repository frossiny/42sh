/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:25:20 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:48:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	can_escape(char *s, size_t i)
{
	if (s[i] == '\\')
	{
		return (!is_escaped(s, i, 0));
	}
	return (0);
}

char		*strjoin_escape(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 || !s2 || !(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcpy(new, s1);
	i = 0;
	j = ft_strlen(new);
	while (s2[i])
	{
		if (can_escape(s2, i))
			i++;
		if (s2[i])
			new[j++] = s2[i++];
	}
	new[j] = '\0';
	free(s1);
	return (new);
}

char		*strdup_escape(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!str || !(new = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (can_escape(str, i))
			i++;
		if (str[i])
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}
