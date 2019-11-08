/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:37:41 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/29 18:34:22 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

void			strswitch(char **dest, char *new)
{
	char *tmp;

	if (!dest || !*dest || !new || *dest == new)
		return ;
	tmp = *dest;
	*dest = new;
	free(tmp);
}

int				is_glob_char(char c)
{
	return (c == '*' || c == '[' || c == '?');
}

int				is_glob_str(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (is_glob_char(str[i]))
			return (1);
	return (0);
}

char			*pull_multi_occ(char *str, char occ)
{
	int		i;
	int		j;
	char	*tmp;
	char	*curr;

	curr = ft_strdup(str);
	i = -1;
	while (curr[++i])
	{
		j = i;
		while (curr[j] == occ)
			j++;
		if (j > i + 1)
		{
			tmp = ft_strndup(curr, i + 1);
			curr = ft_strfjoin(tmp, curr + j, curr);
			free(tmp);
		}
	}
	return (curr);
}
