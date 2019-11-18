/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_par_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:02:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 15:07:38 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expansion.h"

char	*exp_par_len(t_expansion *exp)
{
	char	*tmp;
	t_var	*var;
	char	*ret;
	size_t	vsize;

	vsize = get_var_size(exp->str + exp->i);
	exp->li = exp->i + vsize + 1;
	if (!(tmp = ft_strsub(exp->str, exp->i, vsize)))
		return (ft_strdup("0"));
	if (!(var = var_get(g_shell.vars, tmp)) || !var->value)
	{
		free(tmp);
		return (ft_strdup("0"));
	}
	if (var->value)
		ret = ft_itoa(ft_strlen(var->value));
	else
		ret = ft_strdup("0");
	free(tmp);
	return (ret);
}
