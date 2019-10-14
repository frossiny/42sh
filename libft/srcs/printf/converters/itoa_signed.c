/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_signed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:59:32 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/08 16:43:57 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		size_str(t_arg *list)
{
	long long	value;
	size_t		size;

	value = list->data.ll;
	size = 0;
	if (value == 0 && list->precision != 0)
		size++;
	if (value < 0)
		value *= -1;
	while (value != 0)
	{
		value /= 10;
		size++;
	}
	if ((unsigned)list->precision > size && list->precision != -1)
		size = list->precision;
	if (list->positive == -1 || list->data.ll < 0 || list->space == -1)
		size++;
	return (size);
}

static void		fill_str(t_arg *list, unsigned int *size)
{
	size_t		nb;
	long long	value;

	nb = 0;
	value = list->data.ll;
	if (value == 0)
		nb++;
	if (value < 0)
		value *= -1;
	while (value != 0)
	{
		list->str[(*size)--] = '0' + value % 10;
		value /= 10;
		nb++;
	}
	while (nb++ < (unsigned)list->precision && list->precision != -1)
		list->str[(*size)--] = '0';
}

static void		fill_option(t_arg *arg, char *str, int size)
{
	if (arg->data.ll < 0 && arg->zero == -1)
		str[0] = '-';
	else if (arg->data.ll < 0)
		str[size] = '-';
	else if (arg->positive == -1 && arg->zero == -1)
		str[0] = '+';
	else if (arg->positive == -1)
		str[size] = '+';
	else if (arg->space == -1 && arg->zero == -1)
		str[0] = ' ';
	else if (arg->space == -1)
		str[size] = ' ';
}

void			itoa_signed(t_arg *arg)
{
	unsigned int		size;

	if (arg->data.ll == -9223372036854775807 - 1)
	{
		arg->str = ft_strdup("-9223372036854775808");
		return ;
	}
	size = size_str(arg);
	if ((unsigned int)arg->width > size)
		size = arg->width;
	if (!(arg->str = (char *)malloc(sizeof(char) * size + 1)))
		return ;
	ft_memset(arg->str, (arg->zero == -1 && arg->left == 0) ? '0' : ' ', size);
	arg->str[size--] = '\0';
	if (arg->left == -1)
		size = size_str(arg) - 1;
	if (arg->data.ull == 0 && arg->precision != 0)
		arg->str[size--] = '0';
	fill_str(arg, &size);
	fill_option(arg, arg->str, size);
}
