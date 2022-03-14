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

void	copy_line_env(char **new_env, char **env, int new_env_i, int env_i)
{
	int	len;

	len = ft_strlen(env[env_i]);
	new_env[new_env_i] = (char *)ft_calloc((len + 1), sizeof(char));
	ft_check_malloc(new_env[new_env_i], "copy_line_env");
	ft_strcpy(new_env[new_env_i], env[env_i], len);
}

static int	check_export_error(char *arg, int i)
{
	while (arg[i] && ft_strchr("\'\"\\$ ,.:/[{]}+=-?&*^%#@!~", arg[i]))
		i++;
	if (ft_isalpha(arg[i]) || ft_isalnum(arg[i]))
		return (EXIT_SUCCESS);
	else if (!arg[i])
		return (EXIT_FAILURE);
	else
	{
		i++;
		return (check_export_error(arg, i));
	}
}

static char	*change_arg(char *arg, char **env, int *i)
{
	int		row;
	char	*env_name;
	char	*arg_var;
	char	*env_var;
	char	*new_arg_var;

	row = search_in_env(arg, env, NULL, '+');
	if (row < 0)
		return (arg);
	env_name = ft_calloc(*i + 2, sizeof(char));
	ft_check_malloc(env_name, "change_arg");
	ft_strcpy(env_name, arg, *i);
	env_var = get_env_value(env, env_name);
	env_name[*i] = '=';
	arg_var = ft_strdup(&arg[*i + 2]);
	new_arg_var = ft_strjoin(env_var, arg_var);
	free(arg);
	arg = ft_strjoin(env_name, new_arg_var);
	free(env_name);
	free(arg_var);
	free(new_arg_var);
	return (arg);
}

int	check_for_error(char *arg, int type, char **env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (EXIT_FAILURE);
	while (arg[i] && !ft_strchr("\'\"\\$ ,.:/[{]}+=-?&*^%#@!~", arg[i]))
		i++;
	if (arg[i] == '+' && arg[i + 1] == '=')
		arg = change_arg(arg, env, &i);
	if (arg[i] == '=' && type == EXPORT)
	{
		if (!arg[i + 1])
			return (EXIT_SUCCESS);
		else
		{
			i++;
			return (check_export_error(arg, i));
		}
	}
	else if (arg[i] == '\0')
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
