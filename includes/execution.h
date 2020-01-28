/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:56 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/27 14:10:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

int			exec_all(t_shell *shell, t_anode *ast);
int			exec_command(t_cmd *cmd);
int			exe_specials(t_cmd *cmd);
int			exec_assign_vars(t_cmd *cmd);
int			exec_child_fork(t_cmd *cmd, char **env);
int			exec_fork_builtin(t_cmd *cmd);

t_redirect	*parse_redirections(t_token *tok);
int			handle_redirections(t_redirect *redir, int create_only);
int			get_here_doc(t_redirect *redir, t_shell *shell);
void		apply_here_doc(t_redirect *redir);
void		close_here_docs(t_redirect *redir);
int			exec_get_pipes_docs(t_shell *shell, t_pipel *pipes);

int			exec_pipes(t_anode *node, t_shell *shell, t_anode **cn);
int			exec_pipe_builtin(t_pipel *pline, t_fd *fd, t_shell *shell);
int			exec_pipe_cmd(t_pipel *pline, t_fd *fd);
t_pipel		*exec_build_pipeline(t_anode *node, t_shell *shell,
														t_anode **cn);
t_pipel		*exec_pipeline_alloc(t_pipel *prev, t_cmd *cmd, t_shell *shell);
int			exec_end_pipes(t_pipel *pline, t_fd *fd);
void		exec_del_pipeline(t_pipel *pline);
int			exec_is_pipe_bg(t_pipel *pipeline);
void		exec_signal_pipe(t_pipel *pipeline, int signal);
t_pipel		*exec_dup_pipeline(t_pipel *src);

char		*get_exe(t_shell *shell, char *name, int verbose);
char		*get_exe_path(t_shell *shell, char *name);
int			is_exe(t_shell *shell, char *name, int verbose);
char		*exec_get_file(t_cmd *cmd, int *errno, int verbose);

#endif
