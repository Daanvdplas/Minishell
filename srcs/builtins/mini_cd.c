/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_cd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/03/03 13:40:04 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

static int	home_path(char **env, t_mini_vars *vars, char *path)
{
	char	*home_path_str;
	char	*curr_pwd;

	home_path_str = get_env_value(env, "HOME");
	if (!home_path_str)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	curr_pwd = get_env_value(env, "PWD");
	if (chdir(home_path_str) == -1)
		return (file_error(path));
	set_new_paths(home_path_str, curr_pwd, vars);
	return (EXIT_SUCCESS);
}

static int	oldpwd_path(char **env, t_mini_vars *vars, char *path)
{
	char	*old_pwd;
	char	*curr_pwd;

	old_pwd = get_env_value(env, "OLDPWD");
	ft_check_malloc(old_pwd, "oldpwd_path");
	curr_pwd = get_env_value(env, "PWD");
	ft_check_malloc(curr_pwd, "oldpwd_path");
	if (chdir(old_pwd) == -1)
		return (file_error(path));
	set_new_paths(old_pwd, curr_pwd, vars);
	return (EXIT_SUCCESS);
}

static int	relative_path(t_mini_vars *vars, char *path)
{
	char	*curr_pwd;
	char	*new_pwd;

	curr_pwd = getcwd(NULL, 0);
	ft_check_malloc(curr_pwd, "relative_path");
	if (chdir(path) == -1)
		return (file_error(path));
	new_pwd = getcwd(NULL, 0);
	ft_check_malloc(new_pwd, "relative_path");
	set_new_paths(new_pwd, curr_pwd, vars);
	free(curr_pwd);
	free(new_pwd);
	return (EXIT_SUCCESS);
}

static int	absolute_path(char **env, t_mini_vars *vars, char *path)
{
	char	*home_path_str;

	home_path_str = get_env_value(env, "PWD");
	if (chdir(path) == -1)
		return (file_error(path));
	set_new_paths(path, home_path_str, vars);
	return (EXIT_SUCCESS);
}

int	mini_cd(char **args, t_mini_vars *vars)
{
	if (!args[1])
		vars->last_pid = home_path(vars->env, vars, args[1]);
	else if (!ft_strncmp(args[1], "-", 1))
		vars->last_pid = oldpwd_path(vars->env, vars, args[1]);
	else if (args[1][0] == '/')
		vars->last_pid = absolute_path(vars->env, vars, args[1]);
	else
		vars->last_pid = relative_path(vars, args[1]);
	return (EXIT_SUCCESS);
}
