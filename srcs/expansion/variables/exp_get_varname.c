/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_get_varname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:02:38 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 13:06:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"

char	*exp_get_varname(t_expansion *exp)
{
	size_t	varsize;

	if (!(varsize = get_var_size(exp->str + exp->i)))
		return (ft_strdup(""));
	return (ft_strsub(exp->str, exp->i + 1, varsize));
}
