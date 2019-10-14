/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:59:32 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/16 12:26:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	val;
	int		i;
	char	neg;

	i = 0;
	val = 0;
	neg = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = (val * 10) + str[i] - '0';
		if (val < 0 && neg)
			return (0);
		if (val < 0 && !neg)
			return (-1);
		str++;
	}
	return (neg ? (int)-val : (int)val);
}
