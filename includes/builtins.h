/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/12 04:28:14 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int				handle_builtin(t_cmd *cmd, t_shell *shell);
t_builtin		get_builtin(char *name);
int				is_builtin(char *name);
int				b_set(t_cmd *cmd, t_shell *shell);
int				b_unset(t_cmd *cmd, t_shell *shell);
int				b_exit(t_cmd *cmd, t_shell *shell);
int				b_cd(t_cmd *cmd, t_shell *shell);
int				b_echo(t_cmd *cmd, t_shell *shell);
int				b_export(t_cmd *cmd, t_shell *shell);
int				b_test(t_cmd *cmd, t_shell *shell);
int				b_fc(t_cmd *cmd, t_shell *shell);
int				b_type(t_cmd *cmd, t_shell *shell);
int				b_alias(t_cmd *cmd, t_shell *shell);
int				b_unalias(t_cmd *cmd, t_shell *shell);

static const t_builtin g_builtins[] =
{
	{ "echo", &b_echo },
	{ "cd", &b_cd },
	{ "set", &b_set },
	{ "unset", &b_unset },
	{ "exit", &b_exit },
	{ "export", &b_export },
	{ "type", &b_type },
	{ "alias", &b_alias },
	{ "unalias", &b_unalias },
	{ "fc", &b_fc },
	{ NULL, NULL }
};

char			*cd_buildpath(char *path);
int				cd_getpath(t_cmd *cmd, t_options *opts);
char			*cd_cdpath(t_var *cdpath, char *path);
int				cd_pathcheck(char *path, char *arg);

int				test_unary(t_cmd *cmd);
int				test_binary(t_cmd *cmd);

typedef struct		s_histo_lst_fc
{
	int					id;
	char				*str;
	struct s_histo_lst	*next;
	struct s_histo_lst	*prev;
}					t_histo_lst_fc;

typedef struct	t_fc_vars
{
	int				from;
	int				to;
	int				list;
	int				exec;
	int				rm;
	int				rv;
	char			*editor;
	int				i;
	t_histo_lst_fc	*lst;
	char			**tab;
	int				tab_len;
}				t_fc_vars;

void			fc_list(t_fc_vars *fc);
int				fc_parse_options(t_cmd *cmd, t_fc_vars *fc);
int				fc_parse_range(t_cmd *cmd, t_fc_vars *fc);

#endif
