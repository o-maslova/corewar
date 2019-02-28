/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:49:33 by omaslova          #+#    #+#             */
/*   Updated: 2018/03/30 19:38:45 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if (s1 != NULL && s2 != NULL)
	{
		while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		{
			s1++;
			s2++;
		}
		if (*s1 == '\0' && *s2 != '\0')
			return ((unsigned char)*s2);
		else if (*s1 != '\0' && *s2 == '\0')
			return ((unsigned char)*s1);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
