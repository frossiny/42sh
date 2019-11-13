/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:45 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/06 16:36:56 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"
#include "variables.h"

int	create_compare(t_expansion *exp, t_compare *l, t_var *var, char *str)
{
	char	*key;
	int	len_cmp;

	key = ft_strndup(exp->str + 2, exp->i - 2);
	l->file = var_get_value(var, key);
	free(key);
	if (!(l->file))
		return (0);
	l->l_pattern = (exp->str[exp->i + 1] == exp->str[exp->i]);
	len_cmp = ft_strlen(str + exp->i + (l->l_pattern ? 2 : 1));
	l->cmp = ft_strndup(str + exp->i + (l->l_pattern ? 2 : 1), len_cmp - 1);
	return (1);
}

int	exp_prefix(t_expansion *exp, t_var *var)
{
	t_compare	cmp;	

	if (!create_compare(exp, &cmp, var, exp->str))
		return (1);
	ft_printf("file->%s, cmp->%s\n", cmp.file, cmp.cmp);
	free(cmp.cmp);
	//exp_join(exp, res);
	return (1);
}
