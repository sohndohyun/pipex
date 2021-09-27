/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:16:25 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/26 20:47:28 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countblock(const char *s1, char c)
{
	int	cnt;
	int	isf;

	cnt = 0;
	isf = 1;
	while (*s1)
	{
		if (*s1 == c)
			isf = 1;
		else
		{
			if (isf)
				cnt++;
			isf = 0;
		}
		s1++;
	}
	return (cnt);
}

static int	ft_blocklen(const char *s1, char c)
{
	const char	*p;

	p = s1;
	while (*s1 && *s1 != c)
		s1++;
	return (s1 - p);
}

static char	*ft_deallocresult(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (dest == 0 || src == 0)
		return (0);
	while (src[size])
		size++;
	if (n > 0)
	{
		while (src[i] != 0 && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (size);
}

char	**ft_split(const char *s1, char c)
{
	int		bcnt;
	int		blen;
	char	**result;
	int		i;

	if (s1 == NULL)
		return (NULL);
	bcnt = ft_countblock(s1, c);
	result = (char **)malloc(sizeof(char *) * (bcnt + 1));
	if (!result)
		return (NULL);
	result[bcnt] = 0;
	i = 0;
	while (i < bcnt)
	{
		while (*s1 && *s1 == c)
			s1++;
		blen = ft_blocklen(s1, c);
		result[i] = (char *)malloc(sizeof(char) * (blen + 1));
		if (!result[i])
			return ((char **)ft_deallocresult(result, i));
		ft_strlcpy(result[i++], s1, blen + 1);
		s1 += blen;
	}
	return (result);
}
