/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/21 18:07:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static t_list	*(*g_func_tab[4])(char *, t_shell *, int *) =\
{
	NULL,
	compl_cmd,
	compl_file,
	compl_var,
};

static char	*find_compl_word(t_cursor_pos *pos)
{
	int		i;
	int		beg;

	beg = 0;
	i = pos->x_rel - 1;
	while (--i >= 0)
		if (ft_strchr(" |&<>'\"", pos->str[i]))
		{
			beg = i + 1;
			break ;
		}
		else if (pos->str[i] == '$')
		{
			beg = i;
			break ;
		}
	return (ft_strsub(pos->str, beg, pos->x_rel - beg));
}

static void	del_compl_lst(void *content, size_t content_size)
{
	content_size = 0;
	ft_strdel((char **)&content);
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	int		mode;
	char	*compl;
	int		len;
	t_list	*compl_lst;

	len = 0;
	if (pos->visual_mode || !str || !*str || !ft_strlen(*str))
		return ;
	if (!(mode = lite_parser(pos, 0)))
		return ;
	if (mode == CMD && pos->str[0] == '.')
		mode = FILE;
	if (!(compl = find_compl_word(pos)))
		return ;
	compl_lst = g_func_tab[mode](compl, shell, &len);
	if (mode == CMD)
		compl_lst = compl_alias_builtins(compl_lst, compl, shell);
	ft_strdel(&compl);
	if (!compl_lst)
		return ;
	disp_compl(pos, str, compl_lst, len);
	ft_lstdel(&compl_lst, del_compl_lst);
}
