/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/03/03 13:36:08 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

static char	**edit_env_export(char **env, char *args, int row_nr, int size_env)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((size_env + 1) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_export");
	i = 0;
	while (env[i])
	{
		if (i == row_nr)
			copy_line_env(new_env, &args, i, 0);
		else
			copy_line_env(new_env, env, i, i);
		i++;
	}
	if (i == row_nr)
	{
		copy_line_env(new_env, &args, i, 0);
		i++;
	}
	new_env[i] = NULL;
	ft_free_char_array(env);
	return (new_env);
}

int	search_in_env(char *args, char **env, t_mini_vars *vars, char c)
{
	int		orig_len;
	int		len;
	int		i;

	len = 0;
	orig_len = ft_strlen(args);
	while (args[len] && args[len] != c)
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], args, len) == 0)
		{
			if (env[i][len] == '=')
				return (i);
		}
		i++;
	}
	if (len == 0)
		error_message(args, vars);
	if (len < orig_len)
		return (ADD_NEW);
	return (NOT_FOUND);
}

char	**ft_export(char *arg, char **env, t_mini_vars *vars)
{
	int		row_nr;
	int		size_env;
	char	**new_env;

	size_env = 0;
	while (env[size_env])
		size_env++;
	row_nr = search_in_env(arg, env, vars, '=');
	if (row_nr == NOT_FOUND)
		return (env);
	else if (row_nr == ADD_NEW)
	{
		size_env++;
		row_nr = size_env - 1;
	}
	new_env = edit_env_export(env, arg, row_nr, size_env);
	ft_check_malloc(new_env, "ft_export");
	vars->last_pid = 0;
	return (new_env);
}

int	mini_export(char **args, t_mini_vars *vars)
{
	int	i;

	if (!args[1])
		mini_single_export(vars->env);
	i = 1;
	while (args[i])
	{
		if (check_for_error(args[i], EXPORT, vars->env))
			error_message(args[i], vars);
		else
			vars->env = ft_export(args[i], vars->env, vars);
		i++;
	}
	return (EXIT_SUCCESS);
}
