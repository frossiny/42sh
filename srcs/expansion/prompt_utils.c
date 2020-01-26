/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:36:31 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/26 18:47:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expansion.h"

void	handle_options_h_prompt(char **expanded_prompt, int *i, int mode)
{
	char	*first_point;
	char	hostname[4096];

	gethostname(hostname, 4096);
	if (mode == 1)
		exec_option_prompt(expanded_prompt, hostname, i);
	else
	{
		first_point = extract_first(hostname, '.');
		exec_option_prompt(expanded_prompt, first_point, i);
		ft_strdel(&first_point);
	}
}

void	reduce_pwd_size(char **expanded_prompt, char *pwd, int *i)
{
	t_var	*home;
	char	*extracted;
	char	*copy;

	if (!(home = var_get(g_shell.vars, "HOME")))
		exec_option_prompt(expanded_prompt, pwd, i);
	if (ft_strstr(pwd, home->value))
	{
		extracted = ft_strsub(pwd, ft_strlen(home->value), ft_strlen(pwd) -
		ft_strlen(home->value));
		copy = ft_strjoin("~", extracted);
		ft_strdel(&extracted);
		exec_option_prompt(expanded_prompt, copy, i);
		ft_strdel(&copy);
	}
}

void	handle_options_num_prompt(char **expanded_prompt, int num, int *i)
{
	char *number;

	number = ft_itoa(num);
	exec_option_prompt(expanded_prompt, number, i);
	ft_strdel(&number);
}

int		color_prompt(char *prompt, int *i)
{
	if (prompt[*i] == '{' && prompt[*i + 4] == '}'
	&& prompt[*i + 1] == 'r' && prompt[*i + 2] == 'e' && prompt[*i + 3] == 'd')
	{	ft_putstr(RED); *i += 5; return (1);}
	if (prompt[*i] == '{' && prompt[*i + 6] == '}'
	&& prompt[*i + 1] == 'w' && prompt[*i + 2] == 'h' && prompt[*i + 3] == 'i'
	&& prompt[*i + 4] == 't' && prompt[*i + 5] == 'e')
	{	ft_putstr(WHITE); *i += 7; return (1);}
	if (prompt[*i] == '{' && prompt[*i + 5] == '}'
	&& prompt[*i + 1] == 'c' && prompt[*i + 2] == 'y' && prompt[*i + 3] == 'a'
	&& prompt[*i + 4] == 'n')
	{	ft_putstr(CYAN); *i += 6; return (1);}
	return (0);
}

void	add_other_char_prompt(char **expanded_prompt, char *prompt, int *i)
{
	char	*copy;

	if (color_prompt(prompt, i) == 0)
	{
		copy = ft_stradd(*expanded_prompt, prompt[(*i)++]);
		if (ft_strcmp(*expanded_prompt, ""))
			ft_strdel(expanded_prompt);
		*expanded_prompt = ft_strdup(copy);
		ft_strdel(&copy);
	}
}
