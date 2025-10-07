/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:52:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/07 13:12:02 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/parsing.h"

int	setup_pipeline_resources(t_pipeline *pipeline, int ***pipes, pid_t **pids)
{
	*pipes = create_pipes(pipeline->cmd_count - 1);
	if (!*pipes)
		return (EXIT_FAILURE);
	*pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!*pids)
	{
		close_pipes(*pipes, pipeline->cmd_count - 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	execute_child_command(int **pipes, int i, int cmd_count, \
	t_cmd *cmd, char ***env)
{
	int			exit_status;
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_HEREDOC)
		{
			handle_heredoc_redirect(redir);
			break ;
		}
		redir = redir->next;
	}
	setup_pipe_redirection(pipes, i, cmd_count);
	close_all_pipes(pipes, cmd_count - 1);
	setup_child_signals();
	exit_status = execute_command(cmd, env);
	exit(exit_status);
}

int	execute_pipeline_commands(t_pipeline *pipeline, int **pipes, pid_t *pids, \
	char ***env)
{
	int		i;
	t_cmd	*current;

	current = pipeline->commands;
	i = 0;
	while (i < pipeline->cmd_count && current)
	{
		pids[i] = create_process();
		if (pids[i] == -1)
		{
			close_pipes(pipes, pipeline->cmd_count - 1);
			free(pids);
			return (EXIT_FAILURE);
		}
		if (pids[i] == 0)
			execute_child_command(pipes, i, pipeline->cmd_count, current, env);
		current = current->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	finalize_pipeline(int **pipes, pid_t *pids, int cmd_count)
{
	int	exit_status;

	close_pipes(pipes, cmd_count - 1);
	exit_status = wait_for_processes(pids, cmd_count);
	free(pids);
	return (exit_status);
}
