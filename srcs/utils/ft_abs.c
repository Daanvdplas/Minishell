/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 11:16:09 by rcappend      #+#    #+#                 */
/*   Updated: 2021/05/27 11:36:07 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
