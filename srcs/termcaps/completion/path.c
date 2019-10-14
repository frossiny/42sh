/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:28:40 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:59:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "structs.h"
#include "hashtable.h"
#include "termcaps.h"

static int	complete_ht(t_compl_info *ci, t_shell *shell)
{
	int		i;

	i = -1;
	if (!shell->bin_ht.table)
		return (0);
	while (++i < shell->bin_ht.size)
	{
		if (ft_strnequ(ci->word, shell->bin_ht.table[i].key,
														ft_strlen(ci->word)))
		{
			if (ci->index == 0)
			{
				include_word(shell->bin_ht.table[i].key, ci->str, ci->pos);
				return (1);
			}
			else
				ci->index--;
		}
	}
	return (0);
}

static int	check_files(DIR *dirp, t_compl_info *ci, t_shell *shell)
{
	struct dirent	*dirc;

	while ((dirc = readdir(dirp)))
	{
		if (ht_exists(shell, dirc->d_name))
			return (0);
		if (ft_strnequ(ci->word, dirc->d_name, ft_strlen(ci->word)))
		{
			if (ci->index == 0)
			{
				include_word(dirc->d_name, ci->str, ci->pos);
				return (1);
			}
			else
				ci->index--;
		}
	}
	return (0);
}

int			complete_path(t_compl_info *ci, t_shell *shell)
{
	DIR				*dirp;
	t_env			*path_env;
	char			**array;
	int				i;

	if (complete_ht(ci, shell))
		return (1);
	if (!(path_env = get_enve(shell->env, "PATH")))
		return (0);
	array = ft_strsplit(path_env->value, ':');
	i = -1;
	while (array[++i] != NULL)
	{
		if (!(dirp = opendir(array[i])))
			break ;
		if (check_files(dirp, ci, shell))
		{
			closedir(dirp);
			ft_strddel(&array);
			return (1);
		}
		closedir(dirp);
	}
	ft_strddel(&array);
	return (0);
}
