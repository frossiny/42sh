/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:41 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/26 19:44:19 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "opt.h"
#include "hashtable.h"
#include "utils.h"

char	*find_path_jobs(t_shell *shell, char *first_command)
{
	t_var			*path;
	char			**dirs;
	size_t			i;
	char			*file;

	path = var_get(shell->vars, "PATH");
	i = -1;
	dirs = ft_strsplit(path->value, ':');
	while (dirs && dirs[++i])
	{
		if (access(file = format_path_exe(dirs[i], first_command), F_OK) == 0)
		{
			ft_strddel(&dirs);
			return (file);
		}
	}
	ft_strddel(&dirs);
	ft_printf("42sh: hash: %s: not found", first_command);
	return (NULL);
}

int		job_add_value(t_shell *shell, t_cmd *cmd)
{
	char	*file;
	int		i;

	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
		i++;
	while (cmd->args[i])
	{
		if ((file = find_path_jobs(&g_shell, cmd->args[i]))
		&& !is_builtin(cmd->args[i]))
		{
			if (ht_exists(shell, cmd->args[i]))
				ht_delone(cmd->args[i], shell);
			ht_put(shell, cmd->args[i], file, 0);
		}
		ft_strdel(&file);
		i++;
	}
	return (0);
}

int		display_hash_table(t_hashtable table)
{
	int i;

	i = 0;
	ft_putendl("hits    command");
	while (i != table.size)
	{
		if (table.table[i].key)
			ft_printf("%4zu    %s\n", table.table[i].occurence,
				table.table[i].value);
		i++;
	}
	return (0);
}

int		b_hash(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	opts = opt_parse(cmd, "r", "hash");
	if (opts->ret != 0)
		ft_putendl_fd("hash: usage: hash [-r]", 2);
	else if (shell->bin_ht.table && opts->last == 1 && !(cmd->argc - opts->last))
		display_hash_table(shell->bin_ht);
	else if (opts->opts && !ft_strcmp(opts->opts->opt, "r"))
	{
		if (shell->bin_ht.table)
			ht_delete();
	}
	else if (!shell->bin_ht.table)
		ft_putendl("hash: hash table empty");
	if (cmd->argc - opts->last)
		job_add_value(shell, cmd);
	opt_free(opts);
	return (0);
}
