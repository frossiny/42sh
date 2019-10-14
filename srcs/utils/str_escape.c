/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:25:20 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:59:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*strjoin_escape(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 || !s2 || !(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(new, s1);
	i = 0;
	j = ft_strlen(new);
	while (s2[i])
	{
		if (s2[i] == '\\')
			i++;
		new[j++] = s2[i++];
	}
	free(s1);
	return (new);
}

char	*strdup_escape(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!str || !(new = ft_strnew(ft_strlen(str))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		new[j++] = str[i++];
	}
	return (new);
}
