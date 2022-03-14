/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/03/03 13:38:03 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

static int	mini_pwd(t_mini_vars *vars)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("");
		vars->last_pid = errno;
		exit(errno);
	}
	else
		ft_putendl_fd(str, STDOUT_FILENO);
	free(str);
	vars->last_pid = 0;
	return (EXIT_SUCCESS);
}

static int	mini_env(char **env, t_mini_vars *vars)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	vars->last_pid = 0;
	return (EXIT_SUCCESS);
}

int	is_special_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	built_in(t_cmd *cmds, char *cmd, t_mini_vars *vars)
{
	if (!cmd)
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd, "echo", 5))
		return (mini_echo(cmds->exec->args, vars));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (mini_cd(cmds->exec->args, vars));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (mini_pwd(vars));
	else if (!ft_strncmp(cmd, "export", 7))
		return (mini_export(cmds->exec->args, vars));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (mini_unset(cmds->exec->args, vars));
	else if (!ft_strncmp(cmd, "env", 4))
		return (mini_env(vars->env, vars));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (mini_exit(cmds->exec, vars));
	return (EXIT_FAILURE);
}
