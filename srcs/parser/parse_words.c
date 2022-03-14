/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_words.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 08:47:01 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 12:22:45 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	append_to_arguments(t_exec *exec, char	*new_arg)
{
	char	**args;
	int		i;

	args = ft_calloc(exec->len + 2, sizeof(char *));
	if (!args)
	{
		errno = ENOMEM;
		exit_error(errno, "append_to_arguments", NULL);
	}
	i = 0;
	while (i < exec->len)
	{
		args[i] = exec->args[i];
		i++;
	}
	args[i] = new_arg;
	exec->len++;
	free(exec->args);
	exec->args = args;
	exec->cmd = exec->args[0];
}

void	add_argument(t_exec *exec, t_token *token)
{
	char	*new;

	if (!exec->args)
	{
		exec->args = ft_calloc(1, sizeof(char *));
		if (!exec->args)
		{
			errno = ENOMEM;
			exit_error(errno, "append argument", NULL);
		}
	}
	new = NULL;
	if (token->text)
	{
		new = ft_strdup(token->text);
		if (!new)
		{
			errno = ENOMEM;
			exit_error(errno, "append argument", NULL);
		}	
	}
	append_to_arguments(exec, new);
}

int	parse_words(t_cmd *cmd, t_token *tokens, t_mini_vars *vars)
{	
	while (true)
	{
		if (tokens->type == TOKEN_EOF)
		{
			if (tokens->prev && tokens->prev->type != WORD)
				return (syntax_error(tokens->prev->type, vars));
			break ;
		}
		if (tokens->type == PIPE)
		{
			if (cmd->exec->len || cmd->input || cmd->output)
				cmd = cmd->next;
			else
			{
				syntax_error(tokens->type, vars);
				return (EXIT_FAILURE);
			}
		}
		else
			add_argument(cmd->exec, tokens);
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
