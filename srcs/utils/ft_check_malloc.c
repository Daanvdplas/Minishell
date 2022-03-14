/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:38:09 by rcappend          #+#    #+#             */
/*   Updated: 2022/01/25 10:08:22 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	ft_check_malloc(void *ptr, char *func)
{
	if (!ptr)
	{
		errno = ENOMEM;
		exit_error(errno, func, NULL);
	}
	return ;
}
