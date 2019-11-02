/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:42:22 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/02 17:32:37 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_atol(char *str)
{
	long	num;
	int		i;
	int		neg;

	num = 0;
	i = -1;
	neg = 0;
	if (str[0] == '-')
		neg = 1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i] && ft_isdigit(str[i]))
	{
		num *= 10;
		num += str[i] - '0';
	}
	return (num);
}
