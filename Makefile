# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 07:24:02 by dsohn             #+#    #+#              #
#    Updated: 2021/09/27 08:19:48 by dsohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex
CC=gcc
FLAG=-Wall -Wextra -Werror
MSRCS= \
	mandatory/cmd.c \
	mandatory/findpath.c \
	mandatory/ft_split.c \
	mandatory/ft_strjoin.c \
	mandatory/ft_strlen.c \
	mandatory/ft_strncmp.c \
	mandatory/pipex.c \
	mandatory/strutils.c
MHEADER= -I./mandatory/
MOBJS = ${MSRCS:.c=.o}

BSRCS= \
	bonus/cmd_bonus.c \
	bonus/findpath_bonus.c \
	bonus/ft_split_bonus.c \
	bonus/ft_strjoin_bonus.c \
	bonus/ft_strlen_bonus.c \
	bonus/ft_strncmp_bonus.c \
	bonus/pipex_bonus.c \
	bonus/strutils_bonus.c \
	bonus/heredoc_bonus.c \
	bonus/ft_gnl.c
BHEADER= -I./bonus/
BOBJS = ${BSRCS:.c=.o}

all: $(NAME)

$(NAME): $(MOBJS)
	$(CC) $(FLAG) $(MHEADER) $^ -o $(NAME)

bonus: $(BOBJS)
	$(CC) $(FLAG) $(BHEADER) $^ -o $(NAME)

%.o: %.c
	$(CC) $(FLAG) $(MHEADER) $(BHEADER) -o $@ -c $<

clean:
	rm -f $(MOBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all