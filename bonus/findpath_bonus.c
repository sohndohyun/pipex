/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:41:00 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 07:17:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*searchpath(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		++i;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*findpath(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*temp;
	char	*path;

	temp = searchpath(env);
	if (!temp)
		return (cmd);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free_strarr(paths);
			return (path);
		}
		free(path);
	}
	free_strarr(paths);
	return (cmd);
}
