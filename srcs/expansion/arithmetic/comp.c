/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:54:52 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/05 18:05:19 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ae_equ(long a, long b)
{
	if (a == b)
		return (1);
	return (0);
}

long	ae_nequ(long a, long b)
{
	if (a != b)
		return (1);
	return (0);
}

long	ae_great(long a, long b)
{
	if (a > b)
		return (1);
	return (0);
}

long	ae_greateq(long a, long b)
{
	if (a >= b)
		return (1);
	return (0);
}

long	ae_less(long a, long b)
{
	if (a < b)
		return (1);
	return (0);
}
