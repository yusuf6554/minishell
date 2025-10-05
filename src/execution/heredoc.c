/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:50:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/05 18:32:08 by yukoc            ###   ########.fr       */
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

static int	heredoc_read_parent(int	*pipe_fd, t_redirect *rdr)
{
	char	*content;

	close(pipe_fd[1]);
	content = read_heredoc_content(pipe_fd[0]);
	close(pipe_fd[0]);
	if (!content)
		return (-1);
	if (rdr->content)
		free_string(rdr->content);
	rdr->content = content;
	return (0);
}

static int	setup_heredoc_parent(int *pipe_fd, pid_t pid, t_redirect *rdr)
{
	int	status;
	int result;

	result = heredoc_read_parent(pipe_fd, rdr);
	waitpid(pid, &status, 0);
	setup_signals();
	if (result == -1)
		return (-1);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		if (rdr->content)
			return (free_string(rdr->content), rdr->content = NULL, 130);
		else
			return (130);
	}
	return (0);
}

int	handle_heredoc(t_redirect *rdr, t_minishell *ms)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*exp_delimiter;

	if (!rdr || !rdr->file || !ms)
		return (-1);
	exp_delimiter = expand_variables(rdr->file, ms->env, ms->exit_status);
	if (!exp_delimiter)
		exp_delimiter = ft_strdup(rdr->file);
	if (pipe(pipe_fd) == -1)
		return (free(exp_delimiter), perror_msg("pipe"), -1);
	pid = fork();
	if (pid == -1)
	{
		free(exp_delimiter);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror_msg("fork"), -1);
	}
	if (pid == 0)
		heredoc_child_process(pipe_fd, exp_delimiter, ms->env, ms->exit_status);
	free_string(exp_delimiter);
	return (setup_heredoc_parent(pipe_fd, pid, rdr));
}
