/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:49:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/25 16:53:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>

#include "libft.h"
#include "shell.h"
#include "utils.h"

static int	handle_home_spec(t_token *token, t_var *vars)
{
	char	*path;
	t_var	*var;

	if (!vars || token->content[1] == '\0')
		return (0);
	if ((token->content[1] == '+' || token->content[1] == '-')
			&& (token->content[2] == '\0' || token->content[2] == '/'))
	{
		if (!(var = var_get(vars, token->content[1] == '+'
					? "PWD" : "OLDPWD")))
			return (1);
		if (!(path = ft_strjoin(var->value, token->content + 2)))
			return (0);
	}
	else
		return (1);
	free(token->content);
	token->content = path;
	return (1);
}

static int	handle_home_own(t_token *token, t_var *vars)
{
	char	*path;
	t_var	*tmp;

	if (!vars)
		return (0);
	path = NULL;
	if ((tmp = var_get(vars, "HOME")))
		path = ft_strjoin(tmp->value, token->content + 1);
	else if ((tmp = var_get(vars, "USER")))
		path = ft_strjoint("/Users/", tmp->value, token->content + 1);
	if (!path && !(path = ft_strdup("")))
		return (0);
	free(token->content);
	token->content = path;
	return (1);
}

int			handle_home(t_token *token, t_var *vars)
{
	char			*path;
	struct passwd	*pwd;

	path = NULL;
	if (!token)
		return (0);
	if (token->content[1] == '\0' || token->content[1] == '/')
		return (handle_home_own(token, vars));
	else if (token->content[1] == '+' || token->content[1] == '-')
		return (handle_home_spec(token, vars));
	else if (!ft_isalnum(token->content[1]))
		return (1);
	else
	{
		if (!(pwd = getpwnam(token->content + 1)))
			return (1);
		path = ft_strdup(pwd->pw_dir);
	}
	ft_printf("%s\n", path);
	path = path ? path : ft_strdup("n->content");
	path ? token->content = path : 0;
	return (1);
}
