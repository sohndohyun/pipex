/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:07:04 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 07:16:54 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dup = (char *)malloc(len1 + len2 + 1);
	if (dup)
	{
		ft_memcpy(dup, s1, len1);
		ft_memcpy(dup + len1, s2, len2);
		dup[len1 + len2] = 0;
	}
	return (dup);
}

char	*ft_freejoin(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dup;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dup = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (dup)
	{
		ft_memcpy(dup, s1, len1);
		free(s1);
		ft_memcpy(dup + len1, s2, len2);
		dup[len1 + len2] = 0;
	}
	return (dup);
}
