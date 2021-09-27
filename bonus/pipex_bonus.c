/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:43:49 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 08:57:44 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	closecmdfd(t_cmd *cmd)
{
	close(cmd->fdin);
	close(cmd->fdout);
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
			ret = execve(findpath(cmds[i].argv[0], env), cmds[i].argv, env);
			if (ret < 0)
				write(2, "execve error!\n", 14);
			exit(1);
		}
		waitpid(pid, &ret, WNOHANG);
		closecmdfd(&cmds[i]);
	}
}

int	openout(char *filename, int hd)
{
	if (hd)
		return (open(filename, O_WRONLY | O_APPEND, 0666));
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666));
}

int	main(int argc, char **argv, char **env)
{
	int		fdin;
	t_cmd	*cmds;
	int		cnt;
	int		hd;

	hd = (argc > 5 && ft_strcmp(argv[1], "here_doc") == 0);
	if (argc < 5 || (hd && argc < 6))
	{
		write(2, "Invalid number of arguments.\n", 29);
		return (1);
	}
	if (hd)
		fdin = here_document(argv[2]);
	else
		fdin = open(argv[1], O_RDONLY);
	if (fdin < 0)
	{
		write(2, "wrong infile\n", 13);
		return (1);
	}
	cnt = argc - 3 - hd;
	cmds = getcmds(fdin, openout(argv[argc - 1], hd), cnt, argv + 2 + hd);
	runcmd(cmds, cnt, env);
	freecmds(cmds, cnt, NULL);
}
