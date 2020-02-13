/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:23 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/13 18:21:02 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putchar_err(int c)
{
	char x;

	x = (char)c;
	write(2, &x, 1);
	return (c);
}

int		ft_putchar(int c)
{
	char x;

	x = (char)c;
	write(1, &x, 1);
	return (c);
}
