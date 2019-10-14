/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:06:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/13 14:36:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				handle_exceptions(t_arg *arg)
{
	int		sign;
	size_t	i;
	size_t	len;

	if (is_infinite(arg))
		handle_inf(arg);
	else if (is_nan(arg))
	{
		len = (arg->width > 3) ? arg->width : 3;
		sign = is_float_neg(arg);
		if (!(arg->str = (char *)malloc(sizeof(char) * (len + 1))))
			return ((arg->str = ft_strdup("")) != NULL);
		ft_memcpy(arg->str, arg->type == 'f' ? "nan" : "NAN", 4);
		i = 3;
		while (i < (unsigned)arg->width)
			arg->str[i++] = ' ';
		arg->str[i] = '\0';
		if (!arg->left)
			ft_strrev(arg->str);
	}
	else
		return (0);
	return (1);
}

__int128_t		numtoarg(char buf[], __int128_t n, size_t d)
{
	size_t	i;

	i = 0;
	while (n)
	{
		buf[i++] = '0' + n % 10;
		n /= 10;
	}
	while (i < d)
		buf[i++] = '0';
	buf[i] = '\0';
	ft_strrev(buf);
	return (i);
}

size_t			malloc_str(t_arg *arg, size_t *i, char *buf, int neg)
{
	size_t	len;

	len = (size_t)arg->width > *i ? arg->width : *i;
	if (len == *i)
		len += (arg->positive || arg->space || neg) +
								(arg->prefix && arg->precision == 0);
	if (!(arg->str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		arg->str = ft_strdup("");
		return (0);
	}
	ft_memcpy(arg->str, buf, *i);
	if (arg->prefix && arg->precision == 0)
		arg->str[(*i)++] = '.';
	arg->str[*i] = '\0';
	return (len);
}

void			pad(char *buf, size_t i, t_arg *arg, int neg)
{
	size_t	len;

	if (!(len = malloc_str(arg, &i, buf, neg)))
		return ;
	ft_strrev(arg->str);
	while (i < len - (arg->positive || arg->space || neg) && arg->zero)
		arg->str[i++] = '0';
	if (neg)
		arg->str[i++] = '-';
	else if ((arg->positive || arg->space))
		arg->str[i++] = arg->positive ? '+' : ' ';
	arg->str[i] = '\0';
	if (arg->left)
		ft_strrev(arg->str);
	while (i < (unsigned)arg->width && !arg->zero)
		arg->str[i++] = ' ';
	arg->str[i] = '\0';
	if (!arg->left)
		ft_strrev(arg->str);
}

void			handle_float(t_arg *arg)
{
	char		buf[128];
	size_t		i;
	long double	d;

	if (handle_exceptions(arg))
		return ;
	i = 0;
	d = arg->size == L ? arg->data.ld : (long double)arg->data.d;
	if (is_float_neg(arg))
		d *= -1;
	if (d >= 1)
		i += numtoarg(buf + i,
			fround(!arg->precision ? d : (__int128_t)d, 0), 0);
	else
		buf[i++] = '0';
	if (arg->precision > 0)
	{
		buf[i++] = '.';
		i += numtoarg(buf + i,
		fround((d - (__int128_t)d), arg->precision), arg->precision);
	}
	buf[i] = '\0';
	pad(buf, i, arg, is_float_neg(arg));
}
