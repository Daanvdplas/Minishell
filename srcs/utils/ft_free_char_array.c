/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_char_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:32:36 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 12:19:06 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	*ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}
