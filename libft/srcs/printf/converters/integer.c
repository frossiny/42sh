/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:06:45 by frossiny          #+#    #+#             */
/*   Updated: 2018/12/19 11:51:02 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi_i(const char *str, size_t *i)
{
	long	val;

	val = 0;
	while (ft_isspace(str[*i]))
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		val = (val * 10) + str[*i] - '0';
		if (val < 0)
			return (0);
		(*i)++;
	}
	return ((int)val);
}
