/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/02 19:34:50 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "opt.h"
#include <fcntl.h>
# include <stdio.h>

/*
** Will clear hist and free linked list
*/

void	empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	history = shell->history.lst;
	while (history)
	{
		hist_tmp = history;
		history = history->prev;
		ft_strdel(&history->str);
		free(history);
		history = NULL;
	}
	shell->history.index = 1;
	shell->history.lst = NULL;
}

void	append_hist(t_histo_lst *histo)
{
	t_histo_lst	*curr;
	char		*path;
	int			fd;

	if (!histo)
		return ;
	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (!access(path, F_OK))
		if (access(path, X_OK))
			return ;
	if (fd != -1)
		if ((fd = open(path, O_WRONLY | O_APPEND)))
		{
			curr = histo;
			while (curr)
			{
				write(fd, curr->str, curr->len);
				write(fd, "\n", 1);
				curr = curr->next;
			}
			close(fd);
		}
	free(path);
}

int		print_hist(t_shell *shell)
{
	t_histo_lst		*history;
	size_t			counter;

	counter = 0;
	history = shell->history.lst;
	printf("history.histsize = %zu\n", shell->history.histsize);
	while (history->next && counter != shell->history.histsize)
	{
		printf("Je remonte {%zu %s}\n",  history->index, history->str);
		history = history->next;
		//printf("counter = %zu\n", counter);
		counter++;
	}
	printf("[sortie de boucle] Je remonte {%zu %s}, ses valeurs sont NEXT=%p , PREV=%p\n",  history->index, history->str, history->next, history->prev);
	while (history)
	{
		ft_printf("  %zu  %s\n", history->index, history->str);
		history = history->prev;
	}
	return (0);
}

/*
** Will print last hist var depending on $HISTSIZE
*/

int		b_history(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	(void)cmd;
	(void)shell;
	opts = opt_parse(cmd, "cdanrwps", "history");
	printf("RET = %d, last = %zu\n", opts->ret, opts->last);
	/*while (opts->opts)
	{
		printf("option {%s = %s}\n", opts->opts->opt,  opts->opts->value);
		opts->opts = opts->opts->next;
	}*/
	if (cmd->argc == 1)
	{
		printf("Printing basic history\n");
		print_hist(shell);
	}
	else
	{
		while (opts->opts)
		{
			printf("option {%s = %s}\n", opts->opts->opt,  opts->opts->value);
			if (!ft_strcmp(opts->opts->opt, "c"))
			{
				printf("Je vide mon history\n");
				empty_hist(shell);
			}
			else if (!ft_strcmp(opts->opts->opt, "w"))
			{
				printf("Je vais overwrite mon history\n");
				overwrite_history(shell->history.lst);
			}
			else if (!ft_strcmp(opts->opts->opt, "a"))
			{
				printf("Je vais append mon history\n");
				append_hist(shell->history.lst);
			}
			else if (!ft_strcmp(opts->opts->opt, "r"))
			{
				printf("Je vais load mon history\n"); // probably overwriting it. have to see
				shell->history = get_history();
			}
			opts->opts = opts->opts->next;
		}
	}
	opt_free(opts);
	return (0);
}
