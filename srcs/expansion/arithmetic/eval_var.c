/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:56:11 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/07 16:02:36 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "shell.h"

static void	incr(char *str, int i, char *key, t_token *token)
{
	t_var	*var;
	char	*value;
	long	num_value;

	if (!ft_strncmp(str + i, "++", 2))
		num_value = ft_atol(token->content) + 1;
	else
		num_value = ft_atol(token->content) - 1;
	value = ft_ltoa(num_value);
	if (value && (var = var_get(g_shell.vars, key)))
		var_set(&g_shell.vars, key, value, var->export);
	else if (value && num_value)
		var_set(&g_shell.vars, key, value, 0);
	ft_strdel(&token->content);
	ft_strdel(&value);
}

void		eval_var(char *str)
{
	t_token		token;
	char		*sub;
	int			i;
	int			j;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str + i, "++", 2) || !ft_strncmp(str + i, "--", 2))
		{
			j = i - 1;
			while (j > 0 && ft_isalnum(str[j]))
				j--;
			sub = ft_strsub(str, !j ? j : j + 1, i - j - (!j ? 0 : 1));
			ft_bzero(&token, sizeof(t_token));
			if (var_get(g_shell.vars, sub))
				token.content = var_get_value(g_shell.vars, sub);
			else
				token.content = ft_strnew(0);
			if (ae_process(&token))
				incr(str, i, sub, &token);
			ft_strdel(&sub);
			i++;
		}
	}
}
