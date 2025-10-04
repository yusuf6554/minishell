/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:50:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/01 09:39:34 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/parsing.h"

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static char	*read_line_simple(void)
{
	char	buffer[1024];
	int		i;
	int		ret;
	char	c;

	i = 0;
	while (i < 1023)
	{
		ret = read(0, &c, 1);
		if (ret <= 0)
			return (NULL);
		if (c == '\n')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

static void	read_heredoc_input(int pipe_fd, char *delim, char **env, int es)
{
	char	*line;
	char	*expanded_line;
	char	*expanded_input;

	while (1)
	{
		write(1, "> ", 2);
		line = read_line_simple();
		if (!line)
			break ;
		expanded_input = expand_variables(line, env, es);
		if (!expanded_input)
			expanded_input = ft_strdup(line);
		if (ft_strncmp(expanded_input, delim, ft_strlen(delim)) == 0 &&
			ft_strlen(expanded_input) == ft_strlen(delim))
		{
			free(line);
			free(expanded_input);
			break ;
		}
		expanded_line = expanded_input;
		write_heredoc_line(pipe_fd, expanded_line);
		free(expanded_line);
		free(line);
	}
}

static void	heredoc_child_process(int *pfd, char *delim, char **env, int es)
{
	setup_child_signals();
	close(pfd[0]);
	read_heredoc_input(pfd[1], delim, env, es);
	close(pfd[1]);
	exit(EXIT_SUCCESS);
}

static int	setup_heredoc_parent(int *pipe_fd, pid_t pid)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror_msg("dup"), -1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(original_stdin);
		return (close(pipe_fd[0]), perror_msg("dup2"), -1);
	}
	close(pipe_fd[0]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	setup_signals();
	return (original_stdin);
}

int	handle_heredoc(char *delimiter, char **env, int exit_status)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*expanded_delimiter;

	if (!delimiter)
		return (-1);
	expanded_delimiter = expand_variables(delimiter, env, exit_status);
	if (!expanded_delimiter)
		expanded_delimiter = ft_strdup(delimiter);
	if (pipe(pipe_fd) == -1)
		return (free(expanded_delimiter), perror_msg("pipe"), -1);
	pid = fork();
	if (pid == -1)
	{
		free(expanded_delimiter);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror_msg("fork"), -1);
	}
	if (pid == 0)
		heredoc_child_process(pipe_fd, expanded_delimiter, env, exit_status);
	free(expanded_delimiter);
	return (setup_heredoc_parent(pipe_fd, pid));
}

