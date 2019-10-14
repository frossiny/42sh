/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:51:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/08 18:18:33 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_flag(char c)
{
	return (c == '-' || c == '+' || c == '#' || c == ' ' || c == '0');
}

int		is_size(char c)
{
	return (c == 'h' || c == 'l' || c == 'z');
}

int		is_type(char c)
{
	return (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'f'
		|| c == 'x' || c == 'X' || c == 'c' || c == 's' || c == 'p'
		|| c == 'b' || c == '%' || c == 'F');
}

void	del_list(t_arg **alst)
{
	t_arg	*next;

	while (*alst != NULL)
	{
		next = (*alst)->next;
		free((*alst)->str);
		free(*alst);
		*alst = next;
	}
	*alst = NULL;
}

size_t	ft_strcat_c(char *s1, const char *s2, int j)
{
	char	*dst;
	int		i;

	i = -1;
	dst = s1 + j;
	while (s2[++i])
		dst[i] = s2[i];
	dst[i] = '\0';
	return (i);
}
