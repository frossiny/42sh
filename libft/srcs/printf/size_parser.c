/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:36:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 13:59:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_width(char *format, t_arg *arg, size_t *i)
{
	if (format[*i] == '*')
	{
		arg->width = -2;
		arg->wildcards++;
		(*i)++;
	}
	else
	{
		if (arg->width == -2)
			arg->skipargs |= 1;
		arg->width = ft_atoi_i(format, i);
	}
}

static void	get_prec(char *format, t_arg *arg, size_t *i)
{
	if (format[*i] == '*')
	{
		if (arg->precision > -1 && arg->skipargs)
			arg->skipargs |= 4;
		arg->precision = -2;
		arg->wildcards++;
		(*i)++;
	}
	else
	{
		if (arg->precision == -2)
		{
			if (arg->skipargs)
				arg->skipargs |= 2;
			arg->skipargs |= 1;
		}
		arg->precision = ft_atoi_i(format, i);
	}
}

void		parse_size(char *format, size_t i, t_arg *arg)
{
	arg->width = 0;
	arg->precision = -1;
	arg->skipargs = 0;
	arg->wildcards = 0;
	while (format[i] != '\0' && is_flag(format[i]))
		i++;
	if ((format[i] != '.' || format[i] != '*')
		&& (is_type(format[i]) || is_size(format[i])))
		return ;
	if (format[i] != '.')
		while (format[i] == '*' || ft_isdigit(format[i]))
			get_width(format, arg, &i);
	if (format[i] == '.')
	{
		i++;
		get_prec(format, arg, &i);
		while (arg->width && (format[i] == '*' || ft_isdigit(format[i])))
		{
			arg->skipargs |= 4;
			if (format[i] == '*')
				arg->wildcards++;
			i++;
		}
	}
}
