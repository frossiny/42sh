/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:59:10 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:35:35 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>

# include "structs.h"
# include "termcaps.h"
# include "variables.h"
# include "utils.h"

# define MAX_HISTORY	30
# define HT_SIZE		150
# define EXP_SPECIAL	"?$!0"
# define MAX_PWD_LEN	8192

extern t_shell		g_shell;
extern t_cursor_pos	g_pos;
extern int			g_child;
extern int			g_pipe_pid;
extern int			g_lstatus;
extern int			g_clear_buffer;
extern int			g_ignore_signals;
extern int			g_return;
extern int			g_lpid;
extern char			*g_pwd;

int					handle_input(t_shell *shell, char **input, int history);
int					eval_exec(char **input, int history);
int					shell(void);
void				prompt(void);
int					prompt_len(void);
int					check_quotes(char *str, char c);
int					eval_exec(char **input, int history);

char				**dup_argv(int argc, char **args, char ***argv);
int					replace_vars(t_token *curr, t_var *vars);
size_t				get_var_size(char *key);

void				register_signals(void);
void				unregister_signals(void);
int					display_signal(int sigid);

void				load_42shrc(void);

#endif
