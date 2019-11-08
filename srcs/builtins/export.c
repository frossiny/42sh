/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:28:29 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 16:50:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"
#include "opt.h"

static int	is_key_valid(char *str, size_t len)
{
	if (len == 0)
		len = ft_strlen(str);
	while (*str && len--)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	split_add_var(char *var, t_var **vars)
{
	char	*key;
	char	*chr;

	chr = ft_strchr(var, '=');
	key = ft_strsub(var, 0, chr - var);
	var_set(vars, key, chr + 1, 1);
	free(key);
}

static int	parse_vars(t_cmd *cmd, t_options *opts, t_shell *shell)
{
	int		i;
	char	*chr;

	i = opts->last - 1;
	while (cmd->args[++i])
	{
		if ((chr = ft_strchr(cmd->args[i], '=')))
		{
			if (is_key_valid(cmd->args[i], chr - cmd->args[i]))
				split_add_var(cmd->args[i], &(shell->vars));
			else
				ft_printf("export: '%s': not a valid identifier\n", \
					cmd->args[i]);
		}
		else
		{
			if (is_key_valid(cmd->args[i], 0))
				var_export(shell->vars, cmd->args[i]);
			else
				ft_printf("export: '%s': not a valid identifier\n", \
					cmd->args[i]);
		}
	}
	return (1);
}

int			b_export(t_cmd *cmd, t_shell *shell)
{
	t_options	*options;

	options = opt_parse(cmd, "p", "export");
	if (options->ret != 0)
	{
		opt_free(options);
		return (1);
	}
	parse_vars(cmd, options, shell);
	if (cmd->args[options->last] == NULL || opt_get(options, "p"))
		var_disp_env(shell->vars);
	opt_free(options);
	return (0);
}
