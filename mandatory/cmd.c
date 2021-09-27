/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:30:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 06:08:04 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	setcmdargv(t_cmd *cmd, char *cmdstr, int *pfd)
{
	cmd->argv = ft_split(cmdstr, ' ');
	if (cmd->argv == NULL)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (0);
	}
	return (1);
}

t_cmd	*getcmds(int fdin, int fdout, int cnt, char **cmdstr)
{
	t_cmd	*cmds;
	int		i;
	int		pfd[2];

	cmds = malloc(sizeof(t_cmd) * cnt);
	i = -1;
	while (++i < cnt)
	{
		cmds[i].fdin = fdin;
		if (i != cnt - 1)
		{
			if (pipe(pfd) == -1)
				freecmds(cmds, i, "pipe error!\n");
			cmds[i].fdout = pfd[1];
			fdin = pfd[0];
		}
		else
			cmds[i].fdout = fdout;
		if (!setcmdargv(&cmds[i], cmdstr[i], pfd))
			freecmds(cmds, i, "split error!\n");
	}
	return (cmds);
}

void	freecmds(t_cmd *cmds, int cnt, char *str)
{
	int	i;

	i = -1;
	while (++i < cnt)
	{
		if (cmds[i].fdin != -1)
			close(cmds[i].fdin);
		if (cmds[i].fdout != -1)
			close(cmds[i].fdout);
		free_strarr(cmds[i].argv);
	}
	if (str)
	{
		write(2, str, ft_strlen(str));
		exit(1);
	}
	exit(0);
}
