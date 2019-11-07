/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:38:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/07 16:31:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "variables.h"

char	*exp_get_word(t_expansion *exp)
{
	size_t	i;
	int		rec;

	rec = 0;
	i = exp->i;
	while (exp->str[i])
	{
		if (ft_strnequ(exp->str + i, "${", 2))
		{
			i++;
			rec++;
		}
		else if (exp->str[i] == '}' && rec == 0)
			break ;
		else if (exp->str[i] == '}')
			rec--;
		i++;
	}
	return (ft_strsub(exp->str, exp->i, i - exp->i));
}
