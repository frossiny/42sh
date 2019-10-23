/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:45:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 14:43:16 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *format, ...)
{
	va_list	arg;
	t_arg	*alst;
	size_t	ret;

	if (format == NULL)
		return (-1);
	va_start(arg, format);
	parse_args(format, &alst, &arg);
	if (alst == NULL)
		return (write(1, format, ft_strlen(format)));
	ret = write_all(1, format, alst);
	va_end(arg);
	del_list(&alst);
	return (ret);
}

int		ft_dprintf(int fd, char *format, ...)
{
	va_list	arg;
	t_arg	*alst;
	size_t	ret;

	if (format == NULL)
		return (-1);
	va_start(arg, format);
	parse_args(format, &alst, &arg);
	if (alst == NULL)
		return (write(fd, format, ft_strlen(format)));
	ret = write_all(fd, format, alst);
	va_end(arg);
	del_list(&alst);
	return (ret);
}
