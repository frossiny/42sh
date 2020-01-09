/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/09 14:52:17 by vsaltel          ###   ########.fr       */
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

/*
** Cd internal functions
*/
char		*cd_buildpath(char *path);

/*
** Type internal functions
*/
int			type_path(char *arg, size_t *find);
int			type_env_path(char *arg, size_t *find, t_var *vars);
int			type_hashtable(char *arg, size_t *find);
int			type_builtin(char *arg, size_t *find);
int			type_alias(char *arg, size_t *find, t_alias *alias);
int			is_executable(char *arg);
char		*check_path(char *path, char *arg);

/*
** history internal functions
*/
void		delete_elem_hist(t_history *hist, t_histo_lst *elem);
int			print_hist(t_shell *shell, int size);
void		replace_curr_hist(t_cmd *cmd, t_shell *shell);
void		empty_hist(t_shell *shell);
int			delone_hist(t_history *hist, char *value);
void		append_hist(t_histo_lst *hist);

/*
** Jobs internal functions
*/
int			job_check_valid_number(t_shell *shell, t_cmd *cmd, int j);
int			job_percent(char *percent, char *builtins);
/*
**	Utils functions
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
	{ NULL, NULL }
};

#endif
