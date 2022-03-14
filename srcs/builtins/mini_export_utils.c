/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_export_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/03/03 13:35:58 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

void	error_message(char *arg, t_mini_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\'', 2);
	ft_putendl_fd(": not a valid identifier", 2);
	vars->last_pid = 1;
	return ;
}

static void	print_w_second_quote(char *line)
{
	while (*line && *line != '=')
		line++;
	line++;
	while (*line)
	{
		ft_putchar_fd(*line, STDOUT_FILENO);
		line++;
	}
	ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_w_first_quote(char *line)
{
	while (*line && *line != '=')
	{
		ft_putchar_fd(*line, STDOUT_FILENO);
		line++;
	}
	ft_putchar_fd(*line, STDOUT_FILENO);
	ft_putchar_fd('\"', STDOUT_FILENO);
}

void	mini_single_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_w_first_quote(env[i]);
		print_w_second_quote(env[i]);
		i++;
	}
	return ;
}
