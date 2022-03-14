/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 11:30:51 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

static char	**edit_env_unset(char **env, int exl_row, int size_old_env)
{
	char	**new_env;
	int		env_i;
	int		new_env_i;

	new_env = (char **)malloc((size_old_env) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_unset");
	env_i = 0;
	new_env_i = 0;
	while (env[env_i])
	{
		if (env_i == exl_row)
		{
			env_i++;
			continue ;
		}
		copy_line_env(new_env, env, new_env_i, env_i);
		env_i++;
		new_env_i++;
	}
	new_env[new_env_i] = NULL;
	ft_free_char_array(env);
	return (new_env);
}

static char	**ft_unset(char *arg, char **env, t_mini_vars *vars)
{
	int		exl_row;
	int		size_old_env;
	char	**new_env;

	exl_row = search_in_env(arg, env, vars, '=');
	if (exl_row == -1)
		return (env);
	size_old_env = 0;
	while (env[size_old_env])
		size_old_env++;
	new_env = edit_env_unset(env, exl_row, size_old_env);
	ft_check_malloc(new_env, "ft_unset");
	vars->last_pid = 0;
	return (new_env);
}

int	mini_unset(char **args, t_mini_vars *vars)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_for_error(args[i], UNSET, vars->env))
			error_message(args[i], vars);
		else
			vars->env = ft_unset(args[i], vars->env, vars);
		i++;
	}
	return (EXIT_SUCCESS);
}
