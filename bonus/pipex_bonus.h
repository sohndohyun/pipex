/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:57:29 by dsohn             #+#    #+#             */
/*   Updated: 2021/09/27 08:21:03 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_cmd
{
	char	**argv;
	int		fdin;
	int		fdout;
}t_cmd;

void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s1, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_freejoin(char *s1, const char *s2);
void	free_strarr(char **arr);
char	*ft_strdup(const char *s1);
int		ft_strcmp(char *s1, char *s2);

t_cmd	*getcmds(int fdin, int fdout, int cnt, char **cmdstr);
void	freecmds(t_cmd *cmds, int cnt, char *str);

char	*findpath(char *cmd, char **env);
int		here_document(char *value);

int		ft_gnl(int fd, char **line);

#endif