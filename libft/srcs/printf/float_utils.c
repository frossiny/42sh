/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:31:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/13 13:34:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_infinite(t_arg *arg)
{
	long	expo;
	long	mantissa;

	expo = arg->data.bin >> (arg->size == L ? 64 : 52);
	expo &= (arg->size == L ? 0x7FFF : 0x7FF);
	mantissa = arg->data.bin;
	mantissa &= (arg->size == L ? 0xFFFFFFFFFFFFFFFF : 0xFFFFFFFFFFFFF);
	if (arg->size == L)
		return (expo == 0x7FFF && mantissa == 0);
	else
		return (expo == 0x7FF && mantissa == 0);
}

int			is_nan(t_arg *arg)
{
	long	expo;
	long	mantissa;

	expo = arg->data.bin >> (arg->size == L ? 64 : 52);
	expo &= (arg->size == L ? 0x7FFF : 0x7FF);
	mantissa = arg->data.bin;
	mantissa &= (arg->size == L ? 0xFFFFFFFFFFFFFFFF : 0xFFFFFFFFFFFFF);
	if (arg->size == L)
		return (expo == 0x7FFF && mantissa);
	else
		return (expo == 0x7FF && mantissa);
}

int			is_float_neg(t_arg *arg)
{
	return ((arg->data.bin >> (arg->size == L ? 79 : 63)) & 1);
}

__int128_t	fround(long double d, int precision)
{
	while (precision--)
		d *= 10;
	d += (d > 0) ? 0.5 : -0.5;
	return ((__int128_t)d);
}

void		handle_inf(t_arg *arg)
{
	size_t	len;
	size_t	i;
	int		neg;

	if (!arg)
		return ;
	neg = is_float_neg(arg);
	len = (arg->width > 3 + neg) ? arg->width : 3 + neg;
	if (!(arg->str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		arg->str = ft_strdup("");
		return ;
	}
	i = 0;
	while (i < len - (3 + neg) && !arg->left)
		arg->str[i++] = ' ';
	if (neg)
		ft_memcpy(arg->str + i, arg->type == 'F' ? "-INF" : "-inf", 4);
	else
		ft_memcpy(arg->str + i, arg->type == 'F' ? "INF" : "inf", 3);
	i += 3 + neg;
	while (i < (size_t)arg->width && arg->left)
		arg->str[i++] = ' ';
	arg->str[i] = '\0';
}
