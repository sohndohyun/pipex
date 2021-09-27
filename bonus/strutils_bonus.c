/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:14:50 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 07:16:20 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_strarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char		*s = src;
	unsigned char			*d;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*dup;

	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (dup)
		ft_memcpy(dup, s1, len);
	return (dup);
}
