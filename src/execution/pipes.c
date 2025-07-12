/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:34 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:18:37 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (close_pipes(pipes, i), NULL);
		if (pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			return (close_pipes(pipes, i), NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

int	setup_pipe_redirection(int **pipes, int cmd_index, int total_cmds)
{
	if (!pipes)
		return (-1);
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd_index < total_cmds - 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}
