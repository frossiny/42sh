/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/07 19:28:49 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "shell.h"
# include <stdio.h>

void				add_to_history(char *str, t_history *history)
{
	t_histo_lst			*item;

	if (!history || !str || !str[0]
		|| (history->lst && ft_strcmp(str, history->lst->str) == 0))
		return ;
	item = new_link(ft_strdup(str));
	item->index = history->index++;
	//printf("Je lis {%zu %s}\n", item->index, item->str);
	if (history->lst)
	{
		item->next = history->lst;
		//printf("%s next pointe vers %s\n", item->str, history->lst->str);
		history->lst->prev = item;
		//printf("%s prev pointe vers %s\n", history->lst->str, item->str);
	}
	history->lst = item;
	history->size++;
}

t_histo_lst			*read_history(int fd, size_t *history_size, size_t *history_index)
{
	t_histo_lst			*last;
	t_histo_lst			*item;
	int					ret;
	char				*buf;

	last = NULL;
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		item = new_link(buf);
		item->index = (*history_index)++;
		(*history_size)++;
		printf("Je lis {%zu %s}\n", item->index, item->str);
		if (last)
		{
			item->next = last;
			//printf("%s next pointe vers %s\n", item->str, last->str);
			item->next->prev = item;
			//printf("%s prev pointe vers %s\n", last->str, item->str);
			last = item;
		}
		else
			last = item;
	}
	return (ret == -1 ? (NULL) : (last));
}

t_history			get_history(void)
{
	t_history	histo;
	int			fd;
	char		*path;

	histo.lst = NULL;
	histo.size = 0;
	histo.index = 1;
	histo.histsize = 500;
	if (!isatty(0))
		return (histo);
	path = NULL;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (access(path, F_OK) || access(path, X_OK))
	{
		free(path);
		return (histo);
	}
	if ((fd = open(path, O_RDONLY)))
	{
		histo.lst = read_history(fd, &(histo.size), &(histo.index));
		close(fd);
	}
	free(path);
	return (histo);
}

void				overwrite_history(t_histo_lst *histo)
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
		if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)))
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
