/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:06:21 by vsaltel           #+#    #+#             */
/*   Updated: 2019/07/29 10:21:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	size_str(t_arg *list, unsigned int base, unsigned int *size)
{
	unsigned long long	value2;

	value2 = list->data.ull;
	*size = 0;
	if ((list->data.ull == 0 && list->precision != 0)
		|| (list->type == 'o' && list->prefix))
		(*size)++;
	while (list->data.ull > 0)
	{
		list->data.ull = list->data.ull / base;
		(*size)++;
	}
	list->data.ull = value2;
	if ((unsigned int)list->precision > *size && list->precision != -1)
		*size = list->precision;
	if (list->prefix && list->data.ull != 0
		&& (list->type == 'x' || list->type == 'X'))
		*size = *size + 2;
	return (*size);
}

static void	fill_str(t_arg *list, unsigned int base, unsigned int *size)
{
	char			*base_str;
	size_t			nb;

	if ((base_str = create_base(base, list->type)) == NULL)
		return ;
	nb = 0;
	if (list->data.ull == 0)
		nb++;
	if (list->type == 'o' && list->data.ull > 0 && list->prefix)
		nb++;
	if ((list->data.ull == 0 && list->precision != 0))
		list->str[(*size)--] = '0';
	else
		while (list->data.ull > 0)
		{
			list->str[(*size)--] = base_str[list->data.ull % base];
			list->data.ull = list->data.ull / base;
			nb++;
		}
	while (nb++ < (unsigned)list->precision && list->precision != -1)
		list->str[(*size)--] = '0';
	free(base_str);
}

static void	fill_option(t_arg *arg, char *str, int size)
{
	if ((arg->type == 'x' || arg->type == 'X') && arg->zero
			&& arg->prefix && arg->data.ull != 0)
	{
		str[1] = 'x';
		if (arg->type == 'X')
			str[1] = 'X';
		str[0] = '0';
	}
	else if ((arg->type == 'x' || arg->type == 'X') && arg->prefix
			&& arg->data.ull != 0)
	{
		str[size] = 'x';
		if (arg->type == 'X')
			str[size] = 'X';
		str[size - 1] = '0';
	}
	else if ((arg->type == 'o' && arg->prefix && arg->data.ull != 0)
				|| (arg->type == 'o' && arg->prefix && arg->precision == 0))
		str[size] = '0';
}

void		itoa_unsigned(t_arg *arg)
{
	unsigned long long	value2;
	unsigned int		size;
	unsigned int		base;

	base = size_base(arg->type);
	value2 = arg->data.ull;
	size = size_str(arg, base, &size);
	if ((unsigned int)arg->width > size)
		size = arg->width;
	if (!(arg->str = (char *)malloc(sizeof(char) * size + 1)))
		return ;
	ft_memset(arg->str, (arg->zero) ? '0' : ' ', size);
	arg->str[size--] = '\0';
	if (arg->left)
		size = size_str(arg, base, &size) - 1;
	fill_str(arg, base, &size);
	arg->data.ull = value2;
	fill_option(arg, arg->str, size);
}
