/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:58:21 by omaslova          #+#    #+#             */
/*   Updated: 2018/04/10 11:47:55 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*str;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if ((str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
	{
		if (s1 != NULL)
			while (*s1 != '\0')
			{
				str[i++] = *s1;
				s1++;
			}
		if (s2 != NULL)
			while (*s2 != '\0')
			{
				str[i++] = *s2;
				s2++;
			}
		str[i] = '\0';
	}
	return (str);
}
