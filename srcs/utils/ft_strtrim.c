/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutgercappendijk <rutgercappendijk@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:42:06 by rcappend          #+#    #+#             */
/*   Updated: 2022/01/08 12:00:24 by rutgercappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	size_t		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len - 1]) != NULL && len > 1)
		len--;
	while (ft_strchr(set, *s1) != NULL && len > 0)
	{
		s1++;
		len--;
	}
	ret = ft_substr(s1, 0, len);
	if (!ret)
		return (NULL);
	return (ret);
}
