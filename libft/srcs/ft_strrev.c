/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:56:25 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 16:11:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	tmp;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	i = 0;
	while (i < len)
	{
		tmp = s[len];
		s[len--] = s[i];
		s[i++] = tmp;
	}
	return (s);
}
