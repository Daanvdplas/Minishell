/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:31:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 11:08:37 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

void	delete_token(t_token **ref)
{
	t_token	*i;
	t_token	*prev;
	t_token	*next;

	if (!ref || !*ref)
	{
		errno = ENODATA;
		return ;
	}
	i = *ref;
	next = i->next;
	prev = i->prev;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(i->text);
	free(i);
}

void	*free_tokens(t_token **ref)
{
	t_token	*i;
	t_token	*next;

	if (!ref || !*ref)
	{
		errno = ENODATA;
		return (NULL);
	}
	i = *ref;
	while (i != NULL)
	{
		next = i->next;
		delete_token(&i);
		i = next;
		if (i)
			i->prev = NULL;
	}
	return (NULL);
}

t_token	*new_token(t_token *last, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	ft_check_malloc(new, "init_token");
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->type = type;
	return (new);
}
