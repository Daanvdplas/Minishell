/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:40:37 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:40:38 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <parser.h>
# include <executor.h>

# define EXPORT 1
# define UNSET 0
# define NOT_FOUND -1
# define ADD_NEW -2

int			built_in(t_cmd *cmds, char *cmd, t_mini_vars *vars);
int			is_special_builtin(char *cmd);
int			mini_unset(char **args, t_mini_vars *vars);
int			mini_echo(char **arg, t_mini_vars *vars);
int			mini_export(char **args, t_mini_vars *vars);
char		**ft_export(char *arg, char **env, t_mini_vars *vars);
int			search_in_env(char *args, char **env, t_mini_vars *vars, char c);
int			check_for_error(char *arg, int type, char **env);
void		copy_line_env(char **new_env, char **env, int new_env_i, int env_i);
int			mini_cd(char **args, t_mini_vars *vars);
int			mini_exit(t_exec *exec, t_mini_vars *vars);
void		set_new_paths(char *new_pwd, char *old_pwd, t_mini_vars *vars);
char		*get_env_value(char **env, char *item);
void		mini_single_export(char **env);
void		error_message(char *arg, t_mini_vars *vars);

#endif
