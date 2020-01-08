/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:23:35 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/02 17:04:29 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

static int	ft_strequstrs(char *str, char *strs[])
{
	int i;

	i = 0;
	while (strs[i])
		if (ft_strequ(str, strs[i++]))
			return (1);
	return (0);
}

char		*g_test_binary_operators[] =
{
	"=", "!=", "-eq", "-ne", "-ge", "-lt", "-le"
};

int			test_binary(t_cmd *c)
{
	if (!ft_strequstrs(c->args[2], g_test_binary_operators))
		ft_dprintf(2, "42sh: test: %s: binary operator expected\n", c->args[2]);
	else if ((ft_strequ(c->args[2], "=") && ft_strequ(c->args[1], c->args[3]))
		|| (ft_strequ(c->args[2], "!=") && !ft_strequ(c->args[1], c->args[3]))
		|| (ft_strequ(c->args[2], "-eq")
			&& ft_atoi(c->args[1]) == ft_atoi(c->args[3]))
		|| (ft_strequ(c->args[2], "-ne")
			&& ft_atoi(c->args[1]) != ft_atoi(c->args[3]))
		|| (ft_strequ(c->args[2], "-gt")
			&& ft_atoi(c->args[1]) > ft_atoi(c->args[3]))
		|| (ft_strequ(c->args[2], "-ge")
			&& ft_atoi(c->args[1]) >= ft_atoi(c->args[3]))
		|| (ft_strequ(c->args[2], "-lt")
			&& ft_atoi(c->args[1]) < ft_atoi(c->args[3]))
		|| (ft_strequ(c->args[2], "-le")
			&& ft_atoi(c->args[1]) <= ft_atoi(c->args[3])))
		return (1);
	return (0);
}
