/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:46:38 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 16:35:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buf[13];
	int		i;
	int		sign;
	long	nu;

	nu = n;
	i = 0;
	sign = 0;
	if (nu < 0)
	{
		sign = 1;
		nu *= -1;
	}
	while (nu > 9)
	{
		buf[i++] = '0' + nu % 10;
		nu /= 10;
	}
	buf[i++] = '0' + nu % 10;
	if (sign)
		buf[i++] = '-';
	buf[i] = '\0';
	return (ft_strrev(ft_strdup(buf)));
}
