/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_del_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:50:35 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/18 16:37:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"
#include "variables.h"

char	*strrev_pattern(char *s)
{
	char	*str;
	int		x;
	int		j;

	x = -1;
	while (s && s[++x])
	{
		if (s[x] == '[' && (j = is_close_bracket(s, x)))
		{
			j++;
			str = ft_strndup(s + x, j - x);
			ft_strrev(str);
			j = -1;
			while (str[++j])
			{
				s[x] = str[j];
				x++;
			}
			free(str);
			if (!s[x])
				break ;
		}
	}
	return (ft_strrev(s));
}

int		create_compare(t_expansion *exp, t_compare *l, t_var *var, char *str)
{
	char	*key;
	int		len_cmp;

	key = ft_strndup(exp->str + 2, exp->i - 2);
	l->file = var_get_value(var, key);
	free(key);
	if (!(l->file))
		return (0);
	l->len_find = 0;
	l->l_pattern = (exp->str[exp->i + 1] == exp->str[exp->i]);
	len_cmp = ft_strlen(str + exp->i + (l->l_pattern ? 2 : 1));
	l->cmp = ft_strndup(str + exp->i + (l->l_pattern ? 2 : 1), len_cmp - 1);
	return (1);
}

int		exp_del_pattern(t_expansion *exp, t_var *var)
{
	t_compare	cmp;
	char		*res;

	if (!create_compare(exp, &cmp, var, exp->str))
		return (1);
	if (exp->str[exp->i] == '%')
	{
		ft_strrev(cmp.file);
		strrev_pattern(cmp.cmp);
		next_char(&cmp, 0, 0);
		res = ft_strrev(ft_strdup(cmp.file + cmp.len_find));
	}
	else
	{
		next_char(&cmp, 0, 0);
		res = ft_strdup(cmp.file + cmp.len_find);
	}
	exp_join(exp, res, 1);
	ft_multifree(&cmp.cmp, &cmp.file, NULL);
	return (1);
}
