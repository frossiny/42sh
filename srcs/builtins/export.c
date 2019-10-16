/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:28:29 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 16:22:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "opt.h"

int		b_export(t_cmd *cmd, t_shell *shell)
{
	t_options	*options;
	t_opt		*opt;

	options = opt_parse(cmd->argc, cmd->args, "fnp:", "export");

	if (options->ret != 0)
		return (1);

	ft_printf("OPTIONS:\n");
	opt = options->opts;
	while (opt)
	{
		ft_printf("-%s = %s\n", opt->opt, opt->value);
		opt = opt->next;
	}

	//var_disp_env(shell->vars);
	opt_free(options);
	return (0);
}
