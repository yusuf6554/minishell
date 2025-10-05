/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:42 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/05 18:10:36 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	handle_redirect_type(t_redirect *redirect, char **env, int es)
{
	(void)env;
	(void)es;
	if (redirect->type == REDIRECT_IN)
		return (handle_input_redirect(redirect->file));
	else if (redirect->type == REDIRECT_OUT)
		return (handle_output_redirect(redirect->file, 0));
	else if (redirect->type == REDIRECT_APPEND)
		return (handle_output_redirect(redirect->file, 1));
	/*else if (redirect->type == REDIRECT_HEREDOC)
		return (handle_heredoc(redirect->file, env, es));*/
	return (-1);
}

int	setup_redirections(t_redirect *redirects, char **env, int exit_status)
{
	t_redirect	*current;
	int			result;

	if (!redirects)
		return (0);
	current = redirects;
	while (current)
	{
		result = handle_redirect_type(current, env, exit_status);
		if (result == -1)
			return (-1);
		if (result > 0 && current->type == REDIRECT_HEREDOC)
			return (result);
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
