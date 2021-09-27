/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:14:51 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 08:55:44 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	catch_ctrld_heredoc(char **line)
{
	char	*line_buf;
	int		flag_exit;

	line_buf = ft_strdup("");
	flag_exit = 1;
	while (ft_gnl(STDIN_FILENO, line) == 0)
	{
		line_buf = ft_freejoin(line_buf, *line);
		if (**line == '\0' && flag_exit == 1)
		{
			free(*line);
			free(line_buf);
			write(1, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		write(1, "  \b\b", 4);
		free(*line);
		flag_exit = 0;
	}
	if (flag_exit == 0)
	{
		free(*line);
		*line = ft_strdup(line_buf);
	}
	free(line_buf);
}

int	get_herdoc_input(char **line)
{
	catch_ctrld_heredoc(line);
	if (*line == NULL || ft_strcmp(*line, "") == 0)
	{
		free(*line);
		return (0);
	}
	return (1);
}

int	here_document(char *value)
{
	char	*line;
	char	*doc;
	int		fds[2];

	if (pipe(fds) < 0)
		return (-1);
	doc = ft_strdup("");
	while (1)
	{
		if (get_herdoc_input(&line))
		{
			if (ft_strcmp(value, line) == 0)
			{
				free(line);
				break ;
			}
			doc = ft_freejoin(doc, line);
			free(line);
		}
		doc = ft_freejoin(doc, "\n");
	}
	write(fds[1], doc, ft_strlen(doc));
	free(doc);
	close(fds[1]);
	return (fds[0]);
}
