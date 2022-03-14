/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_cd_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/22 17:03:18 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

char	*get_env_value(char **env, char *key)
{
	int	len;
	int	i;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	set_new_paths(char *new_pwd, char *old_pwd, t_mini_vars *vars)
{
	char	*new_curr_pwd;
	char	*new_old_pwd;

	new_curr_pwd = ft_strjoin("PWD=", new_pwd);
	ft_check_malloc(new_curr_pwd, "home_path");
	new_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	ft_check_malloc(new_old_pwd, "home_path");
	vars->env = ft_export(new_curr_pwd, vars->env, vars);
	vars->env = ft_export(new_old_pwd, vars->env, vars);
	free(new_curr_pwd);
	free(new_old_pwd);
	return ;
}
