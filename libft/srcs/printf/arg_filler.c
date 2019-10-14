/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:50:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/13 15:33:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_size(t_arg *alst, va_list *args)
{
	if (alst->wildcards)
	{
		alst->wildcards -= ((alst->width == -2) + (alst->precision == -2));
		while (alst->wildcards-- > 0)
			(void)va_arg(*args, int);
		if (alst->skipargs & 2 || alst->skipargs >= 4)
		{
			(void)va_arg(*args, int);
			alst->width = 0;
		}
	}
	if (alst->width == -2)
		alst->width = va_arg(*args, int);
	if (alst->width > 2147483647 || alst->width < -2147483647)
		alst->width = 0;
	alst->left = alst->left || alst->width < 0;
	alst->width = alst->width < 0 ? -(alst->width) : alst->width;
	if (alst->precision == -2)
		alst->precision = va_arg(*args, int);
	alst->precision = alst->precision < 0 ? -1 : alst->precision;
}

static void	fill_decimal(t_arg *alst, va_list *args)
{
	if (alst->type == 'd' || alst->type == 'i')
	{
		alst->data.ll = va_arg(*args, long long);
		if (alst->size == none)
			alst->data.ll = (int)alst->data.ll;
		else if (alst->size == l)
			alst->data.ll = (long)alst->data.ll;
		else if (alst->size == h)
			alst->data.ll = (short)alst->data.ll;
		else if (alst->size == hh)
			alst->data.ll = (char)alst->data.ll;
		return ;
	}
	alst->data.ull = va_arg(*args, unsigned long long);
	if (alst->size == none)
		alst->data.ll = (unsigned int)alst->data.ll;
	else if (alst->size == l)
		alst->data.ll = (unsigned long)alst->data.ll;
	else if (alst->size == h)
		alst->data.ll = (unsigned short)alst->data.ll;
	else if (alst->size == hh)
		alst->data.ll = (unsigned char)alst->data.ll;
}

void		fill_arg(t_arg *alst, va_list *args)
{
	if (!alst || !args)
		return ;
	fill_size(alst, args);
	if (ft_strchr("bdiouxX", alst->type) != NULL)
		fill_decimal(alst, args);
	else if (alst->type == 'f' || alst->type == 'F')
	{
		if (alst->size == L)
			alst->data.ld = va_arg(*args, long double);
		else
			alst->data.d = va_arg(*args, double);
	}
	else if (alst->type == 'c' || alst->type == 'C')
		alst->data.c = va_arg(*args, int);
	else if (alst->type == 's')
		alst->data.ptr = va_arg(*args, char *);
	else if (alst->type == 'p')
		alst->data.ptr = va_arg(*args, void *);
	if ((alst->type == 'f' || alst->type == 'F') && alst->precision < 0)
		alst->precision = 6;
	convert(alst);
}
