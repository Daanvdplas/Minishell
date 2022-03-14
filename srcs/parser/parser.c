/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 11:56:29 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 11:08:00 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	syntax_error(const t_type type, t_mini_vars *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token \'", STDERR_FILENO);
	if (type == PIPE)
		ft_putchar_fd('|', STDERR_FILENO);
	else if (type == OUTPUT_S || type == OUTPUT_D)
		ft_putchar_fd('>', STDERR_FILENO);
	else if (type == INPUT_S || type == INPUT_D)
		ft_putchar_fd('<', STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	vars->last_pid = 258;
	return (EXIT_FAILURE);
}

static int	parse_pipes(t_cmd **cmd_list, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;

	cmd = new_cmd();
	head = cmd;
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
		{
			cmd->next = new_cmd();
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	*cmd_list = head;
	return (EXIT_SUCCESS);
}

t_cmd	*parser(t_token *tokens, char **env, t_mini_vars *vars)
{
	t_cmd	*cmd_list;

	if (tokens->type == TOKEN_EOF)
		return (NULL);
	cmd_list = NULL;
	if (parse_quotes_and_expand(tokens, env, vars))
		return (free_tokens(&tokens));
	if (parse_pipes(&cmd_list, tokens))
		cmd_list = free_cmd_list(&cmd_list);
	if (cmd_list && parse_redirects(cmd_list, &tokens, vars))
		cmd_list = free_cmd_list(&cmd_list);
	if (cmd_list && parse_words(cmd_list, tokens, vars))
		cmd_list = free_cmd_list(&cmd_list);
	free_tokens(&tokens);
	return (cmd_list);
}
