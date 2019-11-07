/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/07 21:13:04 by pcharrie         ###   ########.fr       */
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

void	fc_print_history(int min, int max)
{
	int			i;
	t_histo_lst	*lst;

	i = 0;
	lst = g_shell.history.lst;
	while (lst)
	{
		i++;
		if (i >= min && (max < 0 ? 1 : i <= max))
			ft_printf("%d     %s\n", i, lst->str);
		lst = lst->next;
	}
}

void	fc_options_parse(t_cmd *cmd)
{

}

void	fc_edit_history_exec(char *path, char *editor)
{
	int pid;
	char *args[3];
	
	if (access(editor, F_OK | X_OK))
		return ;
	pid = fork();
	if (!pid)
	{
		args[0] = editor;
		args[1] = path;
		args[2] = NULL;
		execve(editor, args, NULL);
		exit(0);
	}
	else if (pid != -1)
	{
		waitpid(pid, NULL, 0);
		ft_strdel(&path);	
	}
}

void	fc_edit_history_file(char **tab, char *editor)
{
	char	*path;
	int		i;
	int		fd;

	path = ft_strpathfile(getenv("HOME"), ".42sh_fc");
	if ((fd = open(path, O_CREAT | O_WRONLY, 0777)) < 0)
		return (ft_strdel(&path));
	i = 0;
	while (tab[i])
	{
		write(fd, tab[i], ft_strlen(tab[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	fc_edit_history_exec(path, editor);
}

void	fc_edit_history(int min, int max, char *editor)
{
	char		**tab;
	int			i;
	int			j;
	t_histo_lst	*lst;
	
	if (!(tab = ft_2dstrnew(max > 0 ? max - min + 1 : 1)))
		return ;
	i = 0;
	j = 0;
	lst = g_shell.history.lst;
	while (lst)
	{
		i++;
		if (max < 0 && i == min)
		{
			if (!(tab[j++] = ft_strdup(lst->str)))
				return ft_2dstrdel(&tab);
			break ;
		}
		else if (i >= min && i <= max)
			if (!(tab[j++] = ft_strdup(lst->str)))
				return ft_2dstrdel(&tab);
		lst = lst->next;
	}
	fc_edit_history_file(tab, editor);
}

int		b_fc(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	int			list;
	char		*editor;

	// if (!(editor = fc_get_editor(cmd)))
	// {

	// }
	// if (cmd->argc == 1)
	// {
		
	// }
	
	//fc_print_history(10, 15);
	fc_edit_history(10, 15, "/usr/bin/vim");

	return (0);
}
