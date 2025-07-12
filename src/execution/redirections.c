/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:45:31 by ehabes            #+#    #+#             */
/*   Updated: 2025/06/24 17:41:24 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	handle_redirect_type(t_redirect *redirect)
{
	if (redirect->type == REDIRECT_IN)
		return (handle_input_redirect(redirect->file));
	else if (redirect->type == REDIRECT_OUT)
		return (handle_output_redirect(redirect->file, 0));
	else if (redirect->type == REDIRECT_APPEND)
		return (handle_output_redirect(redirect->file, 1));
	else if (redirect->type == REDIRECT_HEREDOC)
		return (handle_heredoc(redirect->file));
	return (-1);
}

int	setup_redirections(t_redirect *redirects)
{
	t_redirect	*current;

	if (!redirects)
		return (0);
	current = redirects;
	while (current)
	{
		if (handle_redirect_type(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	handle_input_redirect(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror_msg(file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror_msg("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirect(char *file, int append)
{
	int	fd;
	int	flags;

	if (!file)
		return (-1);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		perror_msg(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror_msg("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	(void)delimiter;
	return (0);
}
