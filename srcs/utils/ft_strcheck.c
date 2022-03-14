/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcheck.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rutgercappendijk <rutgercappendijk@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 11:19:00 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/20 11:35:23 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	ft_strcheck(char const *s, int (*f)(int))
{
	int	i;

	if (!s || !f)
		return (EXIT_FAILURE);
	i = 0;
	while (s[i])
	{
		if (!f(s[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
