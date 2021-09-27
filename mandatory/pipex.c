/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:43:49 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 10:29:18 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	closecmdfd(t_cmd *cmd, int cnt, int i)
{
	close(cmd->fdin);
	close(cmd->fdout);
	if (i < cnt - 1)
		close((cmd + 1)->fdin);
	cmd->fdin = -1;
	cmd->fdout = -1;
}

void	runcmd(t_cmd *cmds, int cnt, char **env)
{
	int		i;
	pid_t	pid;
	int		ret;

	i = -1;
	while (++i < cnt)
	{
		pid = fork();
		if (pid < 0)
			freecmds(cmds, cnt, "fork error\n");
		else if (pid == 0)
		{
			dup2(cmds[i].fdin, 0);
			dup2(cmds[i].fdout, 1);
			closecmdfd(&cmds[i], cnt, i);
			ret = execve(findpath(cmds[i].argv[0], env), cmds[i].argv, env);
			if (ret < 0)
				write(2, "execve error!\n", 14);
			exit(1);
		}
		closecmdfd(&cmds[i], cnt, cnt);
	}
	while (wait(&ret) != -1)
	{
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fdin;
	int		fdout;
	t_cmd	*cmds;
	int		cnt;

	if (argc != 5)
	{
		write(2, "Invalid number of arguments.\n", 29);
		return (1);
	}
	fdin = open(argv[1], O_RDONLY);
	if (fdin < 0)
	{
		write(2, "wrong infile\n", 13);
		return (1);
	}
	fdout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	cnt = argc - 3;
	cmds = getcmds(fdin, fdout, cnt, argv + 2);
	runcmd(cmds, cnt, env);
	freecmds(cmds, cnt, NULL);
}
