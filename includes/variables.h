/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:39:34 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 13:26:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include "structs.h"

t_var	*var_init(char *envp[]);
t_var	*var_new(char *key, char *value, int export);
int		var_set(t_var **vars, char *key, char *value, int export);
int		var_replace(t_var *var, char *value);
char	*var_get_value(t_var *vars, char *key);
t_var	*var_get(t_var *vars, char *key);
char	*var_value(t_var *vars, char *key);
char	**var_build_env(t_var *vars);
int		var_delete(t_var **vars, char *key);
void	var_destroy(t_var **vars);
int		var_display(t_var *vars);
int		var_disp_env(t_var *vars);
int		var_is_key_valid(char *str, size_t len);
void	var_merge(t_var **dst, t_var *src);
int		var_export(t_var *vars, char *key);
t_var	*var_dup(t_var *src);

#endif
