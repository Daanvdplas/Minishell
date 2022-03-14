/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_char.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 07:48:56 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 09:41:34 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

static void	append_to_text(t_token *token, char c)
{
	char	*new;

	if ((token->len + 1) % BUFF_SIZE == 1)
	{
		new = ft_calloc(token->len + BUFF_SIZE + 1, 1);
		if (!new)
		{
			errno = ENOMEM;
			exit_error(errno, "append_to_text", NULL);
		}
		ft_strcpy(new, token->text, token->len);
		free(token->text);
		token->text = new;
	}
	token->text[token->len] = c;
	token->len++;
}

static void	brackets(t_token *token, t_line *line, char c, t_type type)
{
	char	next;

	next = peek_char(line);
	if (c == next)
	{
		next = next_char(line);
		type++;
	}
	append_to_tokens(token, type);
}

static void	word(t_token *token, t_line *line)
{
	char	c;

	c = current_char(line);
	if (token->type == TOKEN_EOF)
	{
		token->type = WORD;
		free(token->text);
		token->text = NULL;
		token->len = 0;
	}
	else if (token->type != WORD)
	{
		token->next = new_token(token, WORD);
		token = token->next;
	}
	append_to_text(token, c);
}

static void	quotes(char c, bool *s_quote, bool *d_quote)
{
	if (*d_quote == false && c == '\'')
		*s_quote = !*s_quote;
	else if (*s_quote == false && c == '\"')
		*d_quote = !*d_quote;
}

void	process_char(t_token *token, t_line *line, bool *s_quote, bool *d_quote)
{	
	char	c;

	c = current_char(line);
	if (c == '\'' || c == '\"')
		quotes(c, s_quote, d_quote);
	if (!in_string(*s_quote, *d_quote) && ft_strchr("<>| ", c))
	{	
		if (ft_isspace(c))
		{
			skip_white_spaces(line);
			append_to_tokens(token, TOKEN_EOF);
		}
		else if (c == '>')
			brackets(token, line, c, OUTPUT_S);
		else if (c == '<')
			brackets(token, line, c, INPUT_S);
		else if (c == '|')
			append_to_tokens(token, PIPE);
	}
	else
		word(token, line);
}
