/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:22:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/20 21:01:27 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "shell.h"

static int	is_colon_op(t_expansion *exp, size_t *i)
{
	if (!exp)
		return (0);
	return (ft_strchr("+-?=", exp->str[*i]) != NULL);
}

static int	is_valid_operator(t_expansion *exp, size_t *i)
{
	if (exp->str[*i] == ':')
	{
		(*i)++;
		return (is_colon_op(exp, i) ? 1 : 0);
	}
	else if (exp->str[*i] == '#' || ft_strnequ(exp->str + *i, "##", 2))
		return (1);
	else if (exp->str[*i] == '%' || ft_strnequ(exp->str + *i, "%%", 2))
		return (1);
	else
		return (0);
}

static int	parameter_parse(t_expansion *exp)
{
	size_t	i;
	int		length;

	if (!exp || !ft_strnequ(exp->str + exp->i, "${", 2))
		return (0);
	i = exp->i + 2;
	if (exp->str[i] == '}' || ft_isdigit(exp->str[i]))
		return (0);
	length = 0;
	if (exp->str[i] == '#')
	{
		length = 1;
		i++;
	}
	if (exp->str[i] && ft_strchr(EXP_SPECIAL, exp->str[i]))
	{
		i++;
		if (exp->str[i] && (ft_isalnum(exp->str[i]) || exp->str[i] == '_' \
				|| ft_strchr(EXP_SPECIAL, exp->str[i])))
			return (0);
	}
	else
		while (exp->str[i] && (ft_isalnum(exp->str[i])
				|| exp->str[i] == '_'))
			i++;
	if (exp->str[i] == '}')
		return (1);
	else if (!exp->str[i])
		return (-1);
	else if (length && is_valid_operator(exp, &i))
		return (-1);
	else if (!is_valid_operator(exp, &i))
		return (-1);
	return (1);
}

int			exp_parameter_parse(t_expansion *exp)
{
	int		ret;

	ret = parameter_parse(exp);
	if (ret < 1)
		ft_dprintf(2, "42sh: bad substitution\n");
	return (ret == 1);
}
