/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:50:50 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/07 17:34:10 by pcharrie         ###   ########.fr       */
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

static int		empty_args(void)
{
	ft_putchar('\n');
	return (0);
}

int				b_echo(t_cmd *cmd, t_shell *shell)
{
	t_options	*options;
	int			opt;

	(void)shell;
	options = opt_parse(cmd, "n", "echo");
	if (options->ret != 0)
	{
		opt_free(options);
		return (1);
	}
	opt = opt_get(options, "n") ? 1 : 0;
	if (cmd->argc < 2)
		return (empty_args());
	disp(cmd->argc - options->last, cmd->args + options->last);
	opt ? 0 : ft_putchar('\n');
	opt_free(options);
	return (0);
}
