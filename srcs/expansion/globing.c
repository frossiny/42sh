/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:49:27 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/23 19:27:34 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expansion.h"
#include "lexer.h"
#include "utils.h"

#include <dirent.h>

void			strswitch(char **dest, char *new)
{
	char *tmp;

	if (!dest || !*dest || !new || *dest == new)
		return ;
	tmp = *dest;
	*dest = new;
	free(tmp);
}

int			is_glob_char(char c)
{
	return (c == '*' || c == '[' || c == '?');
}

int			is_glob_str(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (is_glob_char(str[i]))	
			return (1);
	return (0);	
}

char			*pull_multi_occ(char *str, char occ)
{
	int	i;
	int	j;
	char	*tmp;
	char	*curr;

	curr = ft_strdup(str);
	i = -1;
	while (curr[++i])
	{
		j = i;
		while (curr[j] == occ)
			j++;	
		if (j > i + 1)
		{
			tmp = ft_strndup(curr, i + 1);
			curr = ft_strfjoin(tmp, curr + j, curr);
			free(tmp);
		}
	}
	return (curr);
}

void			free_token(t_token *token)
{
	free(token->content);
	free(token);
}

void			free_globing(t_globing_list *list)
{
	t_globing_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		free(list->path);
		free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

t_globing_list		*create_globing(char *str)
{
	char		**tab;
	t_globing_list	*list;
	t_globing_list	*begin;
	int		i;

	if ((tab = ft_strsplit(str, '/')) == NULL)
		return (NULL);
	free(str);
	if (!(list = (t_globing_list *)malloc(sizeof(t_globing_list))))
		return (NULL);
	i = 0;
	list->content = ft_strdup(tab[i]);
	list->next = NULL;
	begin = list;
	while (tab[++i])
	{
		if (!(list->next = (t_globing_list *)malloc(sizeof(t_globing_list))))
			return (NULL);
		list = list->next;
		list->content = ft_strdup(tab[i]);
		list->path = NULL;
		list->next = NULL;
	}
	ft_strddel(&tab);
	return (begin);
}

int			check_last_occ(char *cmp, char *file)
{
	int	x;
	int	y;

	x = 0;
	while (cmp[x])
		x++;
	y = 0;
	while (file[y])
		y++;
	while (x > -1 && y > -1 && cmp[x] != '*' && cmp[x] == file[y])
	{
		x--;
		y--;
	}
	if (x >= 0 && cmp[x] == '*')
		return (1);
	return (0);
}

int			find_occ(char *cmp, char *file, int *x, int *y)
{
	int	x2;
	int	diff;
	char	*occ;

	x2 = *x;
	while (cmp[x2] && !is_glob_char(cmp[x2]))
		x2++;
	occ = ft_strndup(cmp + *x, x2 - *x);
	ft_printf("occ = %s, file = %s\n", occ, file);
	cmp = ft_strstr(file + *y, occ);
	free(occ);
	if (!cmp)
		return (0);
	*x = x2;
	*y += cmp - file + 1;
	return (1);
}

int			wildcard_bracket(char *cmp, char *file, int *x, int *y)
{
	int	find;

	find = 0;
	if (cmp[*x + 1] == ']')
	{
		if (file[*y] == ']')
			find = 1;
		(*x)++;
	}
	while (cmp[++(*x)] && cmp[*x] != ']')
	{
		if (cmp[*x] && cmp[*x + 1] && cmp[*x + 1] == '-' && cmp[*x + 2] && cmp[*x + 2] != ']' && cmp[*x] <= cmp[*x + 2])
		{
			int i;
			i = 0;
			while (cmp[*x] + i <= cmp[*x + 2])
			{
				if (cmp[*x] + i == file[*y] && cmp[*x] != '/')
					find = 1;
				i++;
			}
			*x = *x + 2;
		}
		else if (cmp[*x] == file[*y])
			find = 1;
	}
	if (!cmp[*x] || !find)
		return (0);
	(*x)++;
	(*y)++;
	return (2);
}

int			wildcard_star(char *cmp, char *file, int *x, int *y)
{
	(*x)++;
	if (!cmp[*x])
		return (1);
	if (!find_occ(cmp, file, x, y))
		return (0);
	if (!cmp[*x] && check_last_occ(cmp, file))
		return (1);
	else if (!cmp[*x])
		return (0);
	return (2);
}

int			wildcard_question(char *cmp, char *file, int *x, int *y)
{
	//ft_printf("cmp = %s, file = %s, x = %c, y = %c\n", cmp, file, cmp[*x], file[*y]);
	(*x)++;
	(*y)++;
	while (cmp[*x] && file[*y] && !is_glob_char(cmp[*x]))
	{
		if (cmp[*x] != file[*y])
			return (0);
		(*x)++;
		(*y)++;
	}
	return (2);
}
int			complete_str(char *cmp, char *file)
{
	int	x;
	int	y;
	int	ret;

	if (!file || file[0] == '.')
		return (0);
	x = -1;
	y = -1;
	while (cmp[++x] && file[++y] && !is_glob_char(cmp[x]))
		if (cmp[x] != file[y])
			return (0);
	while (cmp[x] && file[y] && is_glob_char(cmp[x]))
	{
		if (cmp[x] == '*' && (ret = wildcard_star(cmp, file, &x, &y)) < 2)
			return (ret);
		else if (cmp[x] == '?' && (ret = wildcard_question(cmp, file, &x, &y)) < 2)
			return (ret);
		else if (cmp[x] == '[' && (ret = wildcard_bracket(cmp, file, &x, &y)) < 2)
			return (ret);
	}
	if ((cmp[x]  && !(cmp[x] == '*' && !cmp[x + 1]) && !file[y]) || (!cmp[x] && x > 0 && cmp[x - 1] != '*' && file[y]))
		return (0);
	return (1);
}

void			add_token(t_globing *glob, char *content)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return ;
	if (!glob->root)
		new->content = ft_strdup(content + 2);
	else
		new->content = ft_strdup(content);
	new->next = glob->token->next;
	new->len = ft_strlen(new->content);
	new->type = TOKEN_NAME;
	glob->token->next = new;
	glob->token = new;
	free(content);
	glob->nb_file++;
}

int			file_globing(t_globing *glob, t_globing_list *list, t_list *file)
{
	int		x;
	
	x = 0;
	if (is_glob_str(list->content))
	{
		while (file)
		{
			if (complete_str(list->content, file->content))
			{
				if (list->next)
					dir_globing(glob, list->next, ft_strpathfile(list->path, file->content));
				else
					add_token(glob, ft_strpathfile(list->path, file->content));
			}
			file = file->next;
		}
		if (!glob->nb_file)
			return (0);
	}
	else
		dir_globing(glob, list->next, ft_strpathfile(list->path, list->content));
	return (1);
}

t_list			*get_file(DIR *dirp)
{
	struct dirent	*dirc;
	t_list		*tab;
	t_list		*beg;

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

int			dir_globing(t_globing *glob, t_globing_list *list, char *path)
{
	DIR		*dirp;		
	t_list		*file;

	if (list == NULL)
		return (1);
	list->path = path;
	if ((dirp = opendir(path)) == NULL)
		return (0);
	else
	{
		file = get_file(dirp);	
		ft_lstsort(&file);
		if (file_globing(glob, list, file) == 0)
			return (0);
		ft_freelst(&file);
	}
	return (1);
}

void			remove_token(t_token *curr)
{
	t_token *prev;

	prev = NULL;
	while (curr)
	{
		if (is_glob_str(curr->content) && curr->is_glob_sub)
		{
			prev->next = curr->next;
			free_token(curr);
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int			replace_globing(t_token *token, t_var *vars)
{
	t_token		*begin;
	t_token		*token_next;
	char		*tmp;
	t_globing	glob;
	int		ret;

	begin = token;
	while (token)
	{
		ret = 0;
		token_next = token->next;
		if (is_word_token(token) && is_glob_str(token->content))
		{
			glob.nb_file = 0;
			glob.token = token;
			glob.root = (token->content[0] == '/');
			glob.list = create_globing(pull_multi_occ(token->content, '*'));	
			ret = dir_globing(&glob, glob.list, glob.root ? ft_strdup("/") : ft_strdup("./"));
			token->is_glob_sub = glob.nb_file;
			free_globing(glob.list);
		}
		token = token_next;
	}
	remove_token(begin);
	return (ret);
}
