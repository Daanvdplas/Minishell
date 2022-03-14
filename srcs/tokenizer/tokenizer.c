/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 12:19:38 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:44:50 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

void	append_to_tokens(t_token *last, t_type type)
{	
	if (last->type == TOKEN_EOF)
		last->type = type;
	else
		last->next = new_token(last, type);
}

void	make_tokens(t_token *token, t_line *line)
{
	bool		s_quote;
	bool		d_quote;	
	char		c;

	c = 0;
	s_quote = false;
	d_quote = false;
	while (true)
	{
		c = next_char(line);
		if (c == CMD_EOF)
		{
			append_to_tokens(token, TOKEN_EOF);
			break ;
		}
		process_char(token, line, &s_quote, &d_quote);
		while (token->next != NULL)
			token = token->next;
	}
}

t_token	*tokenizer(char *raw_line)
{
	t_token	*tokens;
	t_line	line;

	line.text = raw_line;
	line.len = ft_strlen(line.text);
	line.position = -1;
	tokens = new_token(NULL, TOKEN_EOF);
	make_tokens(tokens, &line);
	return (tokens);
}
