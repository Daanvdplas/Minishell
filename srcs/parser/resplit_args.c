/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resplit_args.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 10:29:40 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 12:21:47 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	insert_token(t_token *dest, t_token *new)
{
	new->next = dest->next;
	new->prev = dest;
	dest->next = new;
	if (dest->next)
	{
		dest = dest->next;
		dest->prev = new;
	}
}

static void	update_text(t_token *token, int len)
{
	char	*new;

	new = malloc(len + 1);
	ft_check_malloc(new, "update_text");
	new[len] = '\0';
	ft_strcpy(new, token->text, len);
	free(token->text);
	token->text = new;
	token->len = ft_strlen(token->text);
}

static void	add_new_token(t_token *token, int i)
{
	t_token	*new;
	char	*new_text;
	int		len;

	len = ft_strlen(token->text + i);
	new_text = malloc(len + 1);
	ft_check_malloc(new_text, "add_new_token");
	new_text[len] = '\0';
	ft_strcpy(new_text, token->text + i, len);
	new = new_token(NULL, WORD);
	new->text = new_text;
	new->len = ft_strlen(new->text);
	insert_token(token, new);
}

static void	split_token(t_token *token, int i)
{
	int	skip;

	skip = i;
	while (ft_isspace(token->text[skip]))
		skip++;
	if (!token->text[skip])
		return ;
	add_new_token(token, skip);
	update_text(token, i);
}

void	resplit_args(t_token *token)
{
	bool	in_string;
	int		i;

	i = 0;
	while (token->text[i])
	{
		if (token->text[i] == '\'' || token->text[i] == '\"')
			in_string = !in_string;
		else if (!in_string && token->text[i] == ' ')
		{
			split_token(token, i);
			return ;
		}
		i++;
	}
}
