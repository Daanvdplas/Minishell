/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 08:00:34 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:33:26 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	copy_check(char c, bool s_quote, bool d_quote)
{
	if (c != '\'' && c != '\"')
		return (EXIT_SUCCESS);
	else if (d_quote == true && c == '\'')
		return (EXIT_SUCCESS);
	else if (s_quote == true && c == '\"')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static void	new_text(t_token *token, char *old, bool s_quote, bool d_quote)
{
	char	*new;
	int		i;

	new = ft_calloc(token->len + 1, 1);
	ft_check_malloc(new, "new_text");
	i = 0;
	while (*old)
	{
		if (d_quote == false && *old == '\'')
			s_quote = !s_quote;
		else if (s_quote == false && *old == '\"')
			d_quote = !d_quote;
		if (!copy_check(*old, s_quote, d_quote))
		{
			new[i] = *old;
			i++;
		}
		old++;
	}
	free(token->text);
	token->text = new;
	token->len = ft_strlen(token->text);
}

static void	remove_quotes(t_token *token)
{
	bool	s_quote;
	bool	d_quote;
	int		i;

	s_quote = false;
	d_quote = false;
	i = 0;
	while (token->text[i])
	{
		if (d_quote == false && token->text[i] == '\'')
			s_quote = !s_quote;
		else if (s_quote == false && token->text[i] == '\"')
			d_quote = !d_quote;
		if ((d_quote == false && token->text[i] == '\'') || \
			(s_quote == false && token->text[i] == '\"'))
			token->len--;
		i++;
	}
	new_text(token, token->text, s_quote, d_quote);
}

static int	parse_quotes(t_token *token, char **env, int last_pid)
{
	bool	s_quote;
	bool	d_quote;
	long	i;

	s_quote = false;
	d_quote = false;
	i = 0;
	while (i < token->len)
	{
		if (d_quote == false && token->text[i] == '\'')
			s_quote = !s_quote;
		else if (s_quote == false && token->text[i] == '\"')
			d_quote = !d_quote;
		else if (s_quote == false && token->text[i] == '$')
			i -= expander(token, env, last_pid, i);
		i++;
	}
	if (s_quote == true || d_quote == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_quotes_and_expand(t_token *token, char **env, t_mini_vars *vars)
{
	while (token->type != TOKEN_EOF)
	{
		if (token->text)
		{
			if (parse_quotes(token, env, vars->last_pid))
				return (syntax_error(7, vars));
			if (ft_strchr(token->text, ' '))
				resplit_args(token);
			remove_quotes(token);
			if (ft_strlen(token->text) == 0)
			{
				free(token->text);
				token->text = NULL;
			}
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
