/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:50:44 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/30 13:26:58 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include <dirent.h>

int				file_globbing(t_globbing *glob,
					t_globbing_list *list, t_list *file)
{
	int				x;

	x = 0;
	if (is_glob_str(list->content))
	{
		while (file)
		{
			if (complete_str(list->content, file->content))
			{
				if (list->next)
					dir_globbing(glob, list->next,
						ft_strpathfile(list->path, file->content));
				else
					add_token(glob, ft_strpathfile(list->path, file->content));
			}
			file = file->next;
		}
		if (!glob->nb_file)
			return (0);
	}
	else
		dir_globbing(glob, list->next,
			ft_strpathfile(list->path, list->content));
	return (1);
}

t_list			*get_file(DIR *dirp)
{
	struct dirent	*dirc;
	t_list			*tab;
	t_list			*beg;

	beg = NULL;
	while ((dirc = readdir(dirp)) != NULL)
	{
		if (!beg)
		{
			if (!(tab = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			tab->content = ft_strdup(dirc->d_name);
			tab->next = NULL;
			beg = tab;
		}
		else
		{
			if (!(tab->next = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			tab = tab->next;
			tab->content = ft_strdup(dirc->d_name);
			tab->next = NULL;
		}
	}
	return (beg);
}

int				dir_globbing(t_globbing *glob,
					t_globbing_list *list, char *path)
{
	DIR		*dirp;
	t_list	*file;

	if (list == NULL)
		return (1);
	list->path = path;
	if ((dirp = opendir(path)) == NULL)
		return (0);
	else
	{
		file = get_file(dirp);
		ft_lstsort(&file);
		if (file_globbing(glob, list, file) == 0)
			return (0);
		ft_freelst(&file);
	}
	return (1);
}
