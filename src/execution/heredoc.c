/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:50:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 14:49:44 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	read_heredoc_input(int pipe_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipe_fd, line);
		free(line);
	}
}

static void	heredoc_child_process(int *pipe_fd, char *delimiter)
{
	close(pipe_fd[0]);
	read_heredoc_input(pipe_fd[1], delimiter);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static int	setup_heredoc_parent(int *pipe_fd, pid_t pid)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (close(pipe_fd[0]), perror_msg("dup2"), -1);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!delimiter)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (perror_msg("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), perror_msg("fork"), -1);
	if (pid == 0)
		heredoc_child_process(pipe_fd, delimiter);
	return (setup_heredoc_parent(pipe_fd, pid));
}
