/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:50:50 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/22 15:50:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "opt.h"

static void		disp(int argc, char **argv)
{
	while (argc--)
	{
		ft_putstr(*argv);
		if (argc)
			ft_putchar(' ');
		argv++;
	}
}

static int		is_alphastr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				b_echo(t_cmd *cmd, t_shell *shell)
{
	int			opt;
	int			y;

	(void)shell;
	opt = 0;
	y = 0;
	if (!isatty(1))
	{
		write(2, "42sh: echo : bad file descriptor\n", 34);
		return (1);
	}
	while (cmd->args[++y] && cmd->args[y][0] == '-' && cmd->args[y][1]
										&& is_alphastr(cmd->args[y] + 1))
		if (ft_strchr(cmd->args[y], 'n'))
			opt = 1;
	disp(cmd->argc - y, cmd->args + y);
	if (!opt)
		ft_putchar('\n');
	return (0);
}
