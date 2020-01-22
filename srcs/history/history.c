/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:28 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/22 15:22:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "history.h"

void			delete_entry_hist(t_history *history)
{
	t_histo_lst *to_delete;

	to_delete = NULL;
	if (history->size > history->histsize)
	{
		to_delete = history->first_element;
		history->first_element = history->first_element->prev;
		history->first_element->next = NULL;
		ft_strdel(&to_delete->str);
		free(to_delete);
	}
}

void			add_to_history(char *str, t_history *history)
{
	t_histo_lst			*item;

	if (!history || !str || !str[0])
		return ;
	item = new_link(ft_strdup(str));
	item->index = history->index++;
	if (history->lst)
	{
		item->next = history->lst;
		history->lst->prev = item;
	}
	history->lst = item;
	history->size++;
	if (history->size == 1)
		history->first_element = item;
	delete_entry_hist(history);
}

static void		read_history(int fd, t_history *hist)
{
	t_histo_lst			*last;
	int					ret;
	char				*buf;

	last = NULL;
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		if (ft_strisascii(buf) && ft_strcmp(buf, ""))
			add_to_history(buf, hist);
		ft_strdel(&buf);
	}
	return ;
}

void			get_history(void)
{
	int			fd;
	char		*path;

	if (!isatty(0))
		return ;
	path = NULL;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (access(path, F_OK) || access(path, R_OK))
		free(path);
	if ((fd = open(path, O_RDONLY)))
	{
		read_history(fd, &g_shell.history);
		close(fd);
	}
	free(path);
}

void			overwrite_history(t_histo_lst *histo)
{
	t_histo_lst	*curr;
	char		*path;
	int			fd;

	if (!histo)
		return ;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if ((fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0666)) != -1)
	{
		curr = histo;
		while (curr->next)
			curr = curr->next;
		while (curr)
		{
			write(fd, curr->str, curr->len);
			write(fd, "\n", 1);
			curr = curr->prev;
		}
		close(fd);
	}
	free(path);
}
