/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:45:05 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/07 18:53:40 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "variables.h"

extern t_shell	*g_shell;

static int	parse_base(char *str)
{
	int		i;
	int		len;
	int		hex;

	i = 1;
	hex = 0;
	if (str[1] == 'x')
		hex = 1;
	else if (!ft_isdigit(str[1]))
		return (0);
	len = 2;
	while (ft_isdigit(str[++i]) || ft_isalpha(str[i]))
	{
		if ((hex && ft_isalpha(str[i]) && ((str[i] > 'F' && str[i] < 'A')
					|| (str[i] > 'f' && str[i] < 'a'))) || ft_isalpha(str[i]))
			return (0);
		if (!hex && ft_isdigit(str[i]) && str[i] > '7')
			return (0);
		len++;
	}
	return (len);
}

static int	convert_base_str(char **str, int i)
{
	int		len;
	char	*new_num;

	if (!ft_isdigit((*str)[i + 1]) && !ft_isalpha((*str)[i + 1]))
		return (i);
	if (!(len = parse_base(*str + i)))
		return (i);
	if ((*str)[i + 1] == 'x')
		new_num = ft_ltoa(ft_atol_base(*str + i + 2, 16));
	else
		new_num = ft_ltoa(ft_atol_base(*str + i + 1, 8));
	*str = ft_strdelpart(*str, i, len);
	len = ft_strlen(new_num);
	*str = ft_insert_str(*str, new_num, i);
	return (i += len - 1);
}

static char	*var_ae_replace(char *str, int i, int j)
{
	char	*sub;
	t_var	*var;

	if (!(sub = ft_strsub(str, i, j)))
		return (str);
	if (!(var = var_get(g_shell->vars, sub)))
	{
		ft_strdel(&sub);
		return (str);
	}
	str = ft_strdelpart(str, i, j);
	str = ft_insert_str(str, ft_strdup(var->value), i);
	ft_strdel(&sub);
	return (str);
}

char		*ae_base10(char *str)
{
	int		i;
	int		j;
	char	*sub;

/*	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i + ++j])
		{
			sub = ft_strsub(str, i, j);
			if (sub && var_get(g_shell->vars, sub))
			{
				str = var_ae_replace(str, i, j);
				ft_strdel(&sub);
				i += j;
				break ;
			}
			ft_strdel(&sub);
		}
	}
*/	i = -1;
	while (str[++i])
	{
		if (str[i] == '0' && (i == 0 || !ft_isdigit(str[i - 1])))
			i = convert_base_str(&str, i);
	}
	return (str);
}
