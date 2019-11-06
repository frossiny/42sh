/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:50:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/30 15:39:19 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "opt.h"

static int		get_char(char c)
{
	if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	else
		return (0);
}

static void		disp(int argc, char **argv)
{
	size_t	i;

	while (argc--)
	{
		i = 0;
		while (*argv && (*argv)[i])
		{
			if ((*argv)[i] == '\\' && (*argv)[i + 1])
				ft_putchar(get_char((*argv)[++i]));
			else
				ft_putchar((*argv)[i]);
			i++;
		}
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
	disp(cmd->argc - 1 - opt, cmd->args + 1 + opt);
	opt ? 0 : ft_putchar('\n');
	return (0);
}
