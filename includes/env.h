/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:32:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:47:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*copy_env(char **envp, int inc);
t_env				*get_enve(t_env *env, char *key);
t_env				*new_envl(t_env **env, char *key, char *value, int inc);
t_env				*dup_env(t_env *env, int option);
int					delete_env(t_env **env, char *key);
char				**build_env(t_env *env);
void				free_env(t_env **env);
int					disp_free_env(t_env **env);
size_t				count_env(t_env *env);
int					exists_env(t_env *env, char *key);
t_env				*replace_env(t_env *env, char *key, char *new);

#endif
