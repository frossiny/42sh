/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:33:26 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/14 20:30:26 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_list		*find_file(char *path, char *file)
{
	DIR			*dir;
	t_dirent	*dir_content;
	t_list		*new;
	t_list		*begin;

	begin = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((dir_content = readdir(dir)))
	{
		if (ft_strncmp(file, dir_content->d_name, ft_strlen(file))
				|| (dir_content->d_name[0] == '.' && file[0] != '.'))
			continue ;
		new = ft_lstnew(dir_content->d_name,
				ft_strlen(dir_content->d_name) + 1);
		if (!begin)
			begin = new;
		else
			ft_lstend(&begin, new);
	}
	closedir(dir);
	return (begin);
}

t_list		*compl_file(char *compl, t_shell *shell)
{
	t_list		*compl_list;
	char		*slash_ptr;
	char		*file;
	char		*path;
	int			beg;

	(void)shell;
	if (!(slash_ptr = ft_strrchr(compl, '/')))
		beg = 0;
	else
		beg = (int)(slash_ptr - compl) + 1;
	if (!(file = ft_strsub(compl, beg, ft_strlen(compl) - beg)))
		return (NULL);
	if (!(path = ft_strsub(compl, 0, beg)))
		return (NULL);
	if (beg == 0)
		path = ft_strdup(".");
	compl_list = find_file(path, file);
	return (compl_list);
}
