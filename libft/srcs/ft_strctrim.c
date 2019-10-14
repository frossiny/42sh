/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:42:18 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/07 19:06:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strctrim(char const *s, char c)
{
	char	*nstr;
	int		i;
	int		j;
	int		end;

	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (i < end && s[end] == c)
		end--;
	if (!(nstr = ft_strnew(end - i)))
		return (NULL);
	j = 0;
	while (i <= end)
		nstr[j++] = s[i++];
	nstr[j] = '\0';
	return (nstr);
}
