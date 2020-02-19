/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_get_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:52:06 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/19 18:51:04 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"
#include "lexer.h"

char	*job_get_command(t_cmd *cmd)
{
	int			len;
	t_token		*tok;
	char		*ret;

	if (!cmd || !cmd->tokens)
		return (NULL);
	len = 0;
	tok = cmd->tokens;
	while (tok_is_cmd_comp(tok))
	{
		len += tok->len + tok_is_cmd_comp(tok->next);
		tok = tok->next;
	}
	if (!(ret = ft_strnew(len)))
		return (NULL);
	tok = cmd->tokens;
	while (tok_is_cmd_comp(tok))
	{
		ft_strcat(ret, tok->content);
		if (tok_is_cmd_comp(tok->next))
			ft_strcat(ret, " ");
		tok = tok->next;
	}
	return (ret);
}

char	*job_get_pipe_command(t_pipel *pline)
{
	char	*ret;
	char	*cmd;
	char	*tmp;

	if (!pline)
		return (NULL);
	ret = ft_strdup("");
	while (pline && pline->cmd)
	{
		if (!(cmd = job_get_command(pline->cmd)))
			return (ret);
		if (!(tmp = ft_strjoint(ret, ft_strlen(ret) ? " | " : "", cmd)))
		{
			free(cmd);
			return (ret);
		}
		ft_strdel(&ret);
		ft_strdel(&cmd);
		ret = tmp;
		pline = pline->next;
	}
	return (ret);
}
