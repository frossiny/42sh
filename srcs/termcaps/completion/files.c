/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:33:26 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/07 17:54:41 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void	improve_compl(t_list *new, char *path)
{
	t_stat	infos;
	char	*file_name;
	char	*tmp;

	if (!(file_name = ft_strjoin(path, "/")))
		return ;
	tmp = file_name;
	if (!(file_name = ft_strjoin(file_name, new->content)) || stat(file_name,
				&infos))
	{
		ft_strdel(&tmp);
		ft_strdel(&file_name);
		return ;
	}
	ft_strdel(&tmp);
	tmp = new->content;
	if (S_ISDIR(infos.st_mode))
		new->content = ft_strjoin(new->content, "/");
	else
		new->content = ft_strjoin(new->content, " ");
	ft_strdel(&tmp);
	ft_strdel(&file_name);
}

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
		improve_compl(new, path);
	}
	closedir(dir);
	return (begin);
}

static char	*expand_tilde(char *path, t_shell *shell)
{
	t_var	*home_var;

	if (!(home_var = var_get(shell->vars, "HOME")))
		return (path);
	path = ft_strdelpart(path, 0, 1);
	path = ft_insert_str(path, ft_strdup(home_var->value), 0);
	return (path);
}

t_list		*compl_file(char *compl, t_shell *shell, int *len)
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
	if (beg && !(path = ft_strsub(compl, 0, beg)))
		return (NULL);
	if (beg && !ft_strncmp(path, "~/", 2))
		path = expand_tilde(path, shell);
	if (beg == 0)
		path = ft_strdup(".");
	*len = ft_strlen(file);
	compl_list = find_file(path, file);
	ft_strdel(&path);
	ft_strdel(&file);
	return (compl_list);
}
