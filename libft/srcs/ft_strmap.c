/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:04:11 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/07 15:17:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*nstr;
	int		i;

	if (!s || !(nstr = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i])
		nstr[i] = f(s[i]);
	return (nstr);
}
