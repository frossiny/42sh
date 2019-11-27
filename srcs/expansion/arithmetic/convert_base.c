/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:45:05 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/27 03:51:37 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "variables.h"

extern t_shell	*g_shell;

/*static char	*replace_ae_var(char *str)
{
	int		i;
	int		j;
	char	*sub;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i + ++j - 1])
		{
			sub = ft_strsub(str, i, j);
			if (sub && g_shell->vars && var_get_value(g_shell->vars, "PATH"))
			{
				str = ft_strdelpart(str, i, j);
				str = ft_insert_str(str, var_get_value(g_shell->vars, sub), i);
				ft_strdel(&sub);
				i += j;
				break ;
			}
			ft_strdel(&sub);
		}
	}
	return (str);
}
*/
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
		if ((hex && ft_isalpha(str[i]) && !((str[i] <= 'F' && str[i] >= 'A')
					|| (str[i] <= 'f' && str[i] >= 'a'))))
			return (0);
		if (!hex && ((ft_isdigit(str[i]) && str[i] > '7')
					|| ft_isalpha(str[i])))
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

char		*ae_base10(char *str)
{
	int		i;

	i = -1;
	//str = replace_ae_var(str);
	while (str[++i])
	{
		if (str[i] == '0' && (i == 0 || !ft_isdigit(str[i - 1])))
			i = convert_base_str(&str, i);
	}
	return (str);
}
