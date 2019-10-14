/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:22:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/08 18:36:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_modulo(t_arg *arg)
{
	char	*str;
	size_t	i;

	str = ft_strnew(arg->width ? arg->width : 1);
	if (!str)
		arg->str = ft_strdup("%");
	else
	{
		i = 0;
		while (arg->width && i < (unsigned)arg->width - 1)
		{
			str[i++] = arg->zero ? '0' : ' ';
		}
		str[i++] = '%';
		str[i] = '\0';
		if (arg->left)
			ft_strrev(str);
		arg->str = str;
	}
}

void	handle_char(t_arg *arg)
{
	size_t	i;

	i = 0;
	if ((arg->str = ft_strnew(arg->width > 0 ? arg->width : 1)))
	{
		while (!arg->left && arg->width && i < (unsigned)arg->width - 1)
			arg->str[i++] = arg->zero ? '0' : ' ';
		arg->str[i++] = (unsigned char)arg->data.c;
		while (arg->left && i < (unsigned)arg->width)
			arg->str[i++] = arg->zero ? '0' : ' ';
	}
	else
		arg->str = ft_strdup("");
}

void	handle_null_str(t_arg *arg)
{
	char		*new;
	size_t		len;
	size_t		i;
	size_t		j;
	const char	nullstr[] = "(null)";

	i = 0;
	j = 0;
	len = 6;
	if (arg->precision > -1 && len > (size_t)arg->precision)
		len = arg->precision;
	if ((new = ft_strnew(((size_t)arg->width < len) ? arg->width : len)))
	{
		while (!arg->left && i + len < (size_t)arg->width)
			new[i++] = arg->zero ? '0' : ' ';
		while (nullstr[j] && j < len)
			new[i++] = nullstr[j++];
		while (arg->left && i < (size_t)arg->width)
			new[i++] = arg->zero ? '0' : ' ';
		new[i] = '\0';
	}
	else
		new = ft_strdup("");
	arg->str = new;
}

void	handle_str(t_arg *arg)
{
	char	*str;
	char	*new;
	size_t	len;
	size_t	i;

	str = (char *)arg->data.ptr;
	if (!str)
		return (handle_null_str(arg));
	len = ft_strlen(str);
	if (arg->precision > -1 && len > (size_t)arg->precision)
		len = arg->precision;
	i = 0;
	if ((new = ft_strnew(((size_t)arg->width > len) ? arg->width : len)))
	{
		while (!arg->left && i + len < (size_t)arg->width)
			new[i++] = arg->zero ? '0' : ' ';
		ft_memcpy(new + i, str, len);
		i += len;
		while (arg->left && i < (unsigned)arg->width)
			new[i++] = arg->zero ? '0' : ' ';
		new[i] = '\0';
	}
	else
		new = ft_strdup("");
	arg->str = new;
}
