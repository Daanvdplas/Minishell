/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 11:13:27 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:35:18 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/*
	Bash overflowt met exit codes vanaf 255
	if no arguments > exit with last pid
*/
static void	error(char *arg, char *error, int code, t_mini_vars *vars)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	vars->last_pid = code;
}

static bool	find_numeric_arg(t_exec *exec)
{
	int	i;

	i = 2;
	while (i < exec->len)
	{
		if (!ft_strcheck(exec->args[i], ft_isdigit))
			return (true);
		i++;
	}
	return (false);
}

static bool	help_mini_exit(t_exec *exec, t_mini_vars *vars)
{
	if (!ft_strcheck(exec->args[1], ft_isdigit))
	{
		if (exec->len > 2)
		{
			error(NULL, "too many arguments", 1, vars);
			return (false);
		}
		else
			vars->last_pid = ft_atoi(exec->args[1]);
	}
	else
	{
		error(exec->args[1], ": numeric argument required", 255, vars);
		return (find_numeric_arg(exec));
	}
	return (true);
}

int	mini_exit(t_exec *exec, t_mini_vars *vars)
{
	bool	should_exit;

	ft_putendl_fd("exit", STDERR_FILENO);
	should_exit = true;
	if (exec->len > 1)
		should_exit = help_mini_exit(exec, vars);
	if (should_exit)
		exit((unsigned char)vars->last_pid);
	return (vars->last_pid);
}
