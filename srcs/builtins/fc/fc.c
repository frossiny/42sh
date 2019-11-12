/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/12 01:17:21 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

// void	fc_options_parse(t_cmd *cmd)
// {

// }

// void	fc_edit_history_exec(char *path, char *editor)
// {
// 	int		pid;
// 	char	*args[3];
	
// 	if (access(editor, F_OK | X_OK))
// 		return ;
// 	pid = fork();
// 	if (!pid)
// 	{
// 		args[0] = editor;
// 		args[1] = path;
// 		args[2] = NULL;
// 		execve(editor, args, NULL);
// 		exit(0);
// 	}
// 	else if (pid != -1)
// 	{
// 		waitpid(pid, NULL, 0);
// 		ft_strdel(&path);	
// 	}
// }

// void	fc_edit_history_file(char **tab, char *editor)
// {
// 	char	*path;
// 	int		i;
// 	int		fd;

// 	path = ft_strpathfile(getenv("HOME"), ".42sh_fc");
// 	if ((fd = open(path, O_CREAT | O_WRONLY, 0777)) < 0)
// 		return (ft_strdel(&path));
// 	i = 0;
// 	while (tab[i])
// 	{
// 		write(fd, tab[i], ft_strlen(tab[i]));
// 		write(fd, "\n", 1);
// 		i++;
// 	}
// 	close(fd);
// 	fc_edit_history_exec(path, editor);
// }

// void	fc_edit_history(int min, int max, char *editor)
// {
// 	char		**tab;
// 	int			i;
// 	int			j;
// 	t_histo_lst	*lst;
	
// 	if (!(tab = ft_2dstrnew(max > 0 ? max - min + 1 : 1)))
// 		return ;
// 	i = 0;
// 	j = 0;
// 	lst = g_shell.history.lst;
// 	while (lst)
// 	{
// 		i++;
// 		if (max < 0 && i == min)
// 		{
// 			if (!(tab[j++] = ft_strdup(lst->str)))
// 				return ft_2dstrdel(&tab);
// 			break ;
// 		}
// 		else if (i >= min && i <= max)
// 			if (!(tab[j++] = ft_strdup(lst->str)))
// 				return ft_2dstrdel(&tab);
// 		lst = lst->next;
// 	}
// 	fc_edit_history_file(tab, editor);
// }

// void	fc_edit_history_last(char *editor)
// {

// 	// if (!(tab = ft_2dstrnew(1)))
// 	// 	return ;
// }



// t_histo_lst	*fc_get_histo_lst(int from)
// {
// 	t_histo_lst	*lst;
// 	int			i;

// 	i = 2;
// 	lst = g_shell.history.lst;
// 	while (lst && lst->next)
// 	{
// 		if (i == from)
// 			return (lst);
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (lst);
// }

// void	fc_print_history(int min, int max)
// {
// 	int			i;
// 	t_histo_lst	*lst;

// 	i = 2;
// 	lst = g_shell.history.lst;
// 	while (lst)
// 	{
// 		i++;
// 		if (i >= min && (max < 0 ? 1 : i <= max))
// 			ft_printf("%d     %s\n", i, lst->str);
// 		lst = lst->next;
// 	}
// }

// int		fc_get_from(t_cmd *cmd)
// {
// 	int i;

// 	i = 1;
// 	while (cmd->args[i])
// 	{
// 		if (ft_strlen(cmd->args[i]) && cmd->args[i] != '-')
// 		{
// 			if (!ft_isnumeric(cmd->args[i]))
// 				return (-1);
// 			return (ft_atoi(cmd->args[i]));
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int		fc_get_to(int i, t_cmd *cmd)
// {
// 	while (cmd->args[i])
// 	{
// 		if (ft_strlen(cmd->args[i]) && cmd->args[i] != '-')
// 		{
// 			if (!ft_isnumeric(cmd->args[i]))
// 				return (-1);
// 			return (ft_atoi(cmd->args[i]));
// 		}
// 		i++;
// 	}
// }

// int		fc_get_mode(t_cmd *cmd)
// {

// }

// char	*fc_get_editor(t_cmd *cmd)
// {
	
// }

// void	fc_parse_args(t_cmd *cmd)
// {
// 	int i;

// 	i = 1;
// 	while (cmd->args[i])
// 	{

// 	}
// }

// int		b_fc(t_cmd *cmd, t_shell *shell)
// {
	// char		*editor;
	// t_histo_lst	*lst;
	// int			from;
	// int			to;

	// if ((from = fc_get_from(cmd) < 0))
	// {
	// 	ft_putendl_fd(2, "42sh: fc: history specification out of range");
	// 	return (1);
	// }
	// to = fc_get_to(cmd);
	// if (fc_get_mode(cmd))
	// {
	// 	if (!(lst = fc_get_lst(from)))
	// 	{
	// 		ft_putendl_fd(2, "42sh: fc: history specification out of range");
	// 		return (1);
	// 	}
	// 	editor = fc_get_editor(cmd);
	// 	fc_edit_history(lst, to, editor);
	// }
	// else
	// 	fc_print_history(from, to);
	// return (0);
// }

typedef struct	t_fc_vars
{
	int		from;
	int		to;
	int		list;
	int		exec;
	int		rm;
	int		rv;
	char	*editor;
	int		i;
}				t_fc_vars;

int		ft_isnumeric(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{		
		if (!(str[i] >= '0' && str[i] <= '9'))
			if (!(i == 0 && (str[i] == '+' || str[i] == '-')
				&& ft_strlen(str) > 1))
				return (0);
		i++;
	}
	return (1);
}

int		fc_parse_options(t_cmd *cmd, t_fc_vars *fc)
{
	int i;
	int j;

	i = 0;
	while (++i < cmd->argc)
	{
		if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '-' && !ft_isnumeric(cmd->args[i]))
		{
			j = 0;
			while (cmd->args[i][++j])
			{
				if (cmd->args[i][j] == 'e')
				{
					if (j < ft_strlen(cmd->args[i]) - 1)
					{
						if (!(fc->editor = ft_strnew(ft_strlen(cmd->args[i]) - j + 1)))
							return (0);
						ft_strcpy(fc->editor, cmd->args[i] + j + 1);
					}
					else if (cmd->args[i + 1])
					{
						if (!(fc->editor = ft_strdup(cmd->args[i + 1])))
							return (0);
					}
					else
					{
						ft_putendl_fd("42sh: fc: -e: option requires an argument", 2);
						return (-1);
					}
					break;
				}
				else if (cmd->args[i][j] == 'l' || cmd->args[i][j] == 's')
					cmd->args[i][j] == 'l' ? (fc->list = 1) : (fc->exec = 1);
				else if (cmd->args[i][j] == 'n' || cmd->args[i][j] == 'r')
					cmd->args[i][j] == 'n' ? (fc->rm = 1) : (fc->rv = 1);
				else
				{
					ft_dprintf(2, "42sh: fc: -%c: invalid option\n", cmd->args[i][j]);
					return (-1);
				}
			}
		}
		else
			break ;
	}
	fc->i = i;
	return (1);
}

int		fc_parse_range(t_cmd *cmd, t_fc_vars *fc)
{
	if (cmd->args[fc->i])
	{
		if (!ft_isnumeric(cmd->args[fc->i]))
			return (0);
		fc->from = ft_atoi(cmd->args[fc->i++]);
	}
	if (cmd->args[fc->i])
	{
		if (!ft_isnumeric(cmd->args[fc->i]))
			return (0);
		fc->to = ft_atoi(cmd->args[fc->i++]);
	}
	return (1);
}

void	fc_vars_init(t_fc_vars *fc)
{
	fc->from = -1;
	fc->to = -1;
	fc->list = 0;
	fc->exec = 0;
	fc->rm = 0;
	fc->rv = 0;
	fc->editor = NULL;
	fc->i = 0;
}

void	fc_proceed(t_fc_vars &fc)
{
	if (fc->exec)
	{

	}
	else if (fc->list)
	{
		
	}
	else
	{
		// edit
	}
}

int		b_fc(t_cmd *cmd, t_shell *shell)
{
	t_fc_vars	fc;
	int			ret;

	
	ft_printf("\nfrom: %d\n", fc.from);
	ft_printf("to: %d\n", fc.to);
	ft_printf("list: %d\n", fc.list);
	ft_printf("exec: %d\n", fc.exec);
	ft_printf("rm: %d\n", fc.rm);
	ft_printf("rv: %d\n", fc.rv);
	ft_printf("editor: %s\n", fc.editor);

	fc_vars_init(&fc);
	if ((ret = fc_parse_options(cmd, &fc)) < 1)
	{
		if (ret == -1)
			ft_putendl_fd("fc: usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", 2);
		return (1);
	}
	if (!(fc_parse_range(cmd, &fc)))
	{
		ft_putendl_fd("42sh: fc: history specification out of range", 2);
		return (1);
	}
	fc_proceed(&fc);
	return (0);
}
