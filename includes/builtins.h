/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/08 12:09:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

t_builtin	get_builtin(char *name);
int			is_builtin(char *name);

/*
** Builtins functions
*/
int			handle_builtin(t_cmd *cmd, t_shell *shell);
int			b_set(t_cmd *cmd, t_shell *shell);
int			b_unset(t_cmd *cmd, t_shell *shell);
int			b_exit(t_cmd *cmd, t_shell *shell);
int			b_cd(t_cmd *cmd, t_shell *shell);
int			b_echo(t_cmd *cmd, t_shell *shell);
int			b_export(t_cmd *cmd, t_shell *shell);
int			b_history(t_cmd *cmd, t_shell *shell);
int			b_type(t_cmd *cmd, t_shell *shell);
int			b_alias(t_cmd *cmd, t_shell *shell);
int			b_unalias(t_cmd *cmd, t_shell *shell);
int			b_hash(t_cmd *cmd, t_shell *shell);
int			b_jobs(t_cmd *cmd, t_shell *shell);
int			b_fg(t_cmd *cmd, t_shell *shell);
int			b_fc(t_cmd *cmd, t_shell *shell);
int			b_bg(t_cmd *cmd, t_shell *shell);

/*
** Cd internal functions
*/
char		*cd_buildpath(char *path);

/*
** history internal functions
*/
void		delete_elem_hist(t_history *hist, t_histo_lst *elem);
int			print_hist(t_shell *shell, int size);
void		replace_curr_hist(t_cmd *cmd, t_shell *shell);
int			empty_hist(t_shell *shell);
int			delone_hist(t_history *hist, char *value);
void		append_hist(t_histo_lst *hist);

/*
** Jobs internal functions
*/
int			job_check_valid_number(t_shell *shell, t_cmd *cmd, int j);
int			job_percent(char *percent, char *builtins);
/*
** Utils functions
*/
void		restore_fd(int fd[]);

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
	{ "history", &b_history},
	{ "hash", &b_hash},
	{ "jobs", &b_jobs},
	{ "fg", &b_fg},
	{ "bg", &b_bg},
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
	int				from_a;
	int				to_a;
	int				list;
	int				exec;
	int				rm;
	int				rv;
	char			*editor;
	char			**ed_args;
	char			*s_cmd;
	int				i;
	t_histo_lst_fc	*lst;
	char			**tab;
	int				tab_len;
}				t_fc_vars;

void			fc_list(t_fc_vars *fc);
int				fc_parse_options(t_cmd *cmd, t_fc_vars *fc);
int				fc_parse_range(t_cmd *cmd, t_fc_vars *fc);
int				fc_build_tab(t_fc_vars *fc);
void			fc_edit(t_fc_vars *fc);
void			fc_exec_tab(t_fc_vars *fc);
void			fc_exec_file(void);
int				fc_get_mode(t_fc_vars *fc);
int				fc_edit_run_editor(t_fc_vars *fc);
void			fc_edit_remove_file(void);
void			fc_set_exec_cmd(t_fc_vars *fc);

#endif
