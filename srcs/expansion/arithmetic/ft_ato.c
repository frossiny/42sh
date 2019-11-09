/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:42:22 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/06 18:25:55 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ltoa(long nb)
{
	int		nb_digit;
	int		tmp;
	char	*rtrn;

	nb_digit = 1;
	tmp = nb;
	while (tmp >= 10)
	{
		tmp /= 10;
		nb_digit++;
	}
	if (!(rtrn = (char *)malloc((nb_digit + 1) * sizeof(char))))
		return (NULL);
	rtrn[nb_digit] = '\0';
	while (--nb_digit >= 0)
	{
		rtrn[nb_digit] = nb % 10 + '0';
		nb /= 10;
	}
	return (rtrn);
}

long		ft_atol_base(char *str, int base)
{
	int		i;
	long	nb;

	nb = 0;
	i = -1;
	while (ft_isdigit(str[++i]) || (base == 16 && ft_tolower(str[i]) >= 'a'
			&& ft_tolower(str[i]) <= 'f'))
	{
		nb *= base;
		if (ft_isdigit(str[i]))
			nb += str[i] - '0';
		else
			nb += ft_tolower(str[i]) - 'a' + 10;
	}
	return (nb);
}

long		ft_atol(char *str)
{
	long	num;
	int		i;
	int		neg;

	num = 0;
	i = 0;
	neg = 0;
	if (str[0] == '-')
		neg = 1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (neg ? num * -1 : num);
}
