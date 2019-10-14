/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:42:18 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/07 19:53:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*nstr;
	int		i;
	int		j;
	int		end;

	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (i < end && ft_isspace(s[end]))
		end--;
	if (!(nstr = ft_strnew(end - i + 1)))
		return (NULL);
	j = 0;
	while (i <= end)
		nstr[j++] = s[i++];
	nstr[j] = '\0';
	return (nstr);
}
