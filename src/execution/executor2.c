/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:58:59 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/07 13:59:20 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"


int	wait_for_processes(pid_t *pids, int count)
{
	int	status;
	int	last_exit_status;
	int	i;

	if (!pids || count <= 0)
		return (EXIT_FAILURE);
	last_exit_status = EXIT_SUCCESS;
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_exit_status);
}

int	execute_command_main(t_pipeline *pipeline, t_minishell *ms)
{
	int	exit_status;

	if (handle_heredocs(pipeline, ms) == -1)
		return (ms->exit_status);
	if (pipeline->cmd_count > 1)
	{
		exit_status = execute_pipeline(pipeline, &ms->env);
		ms->exit_status = exit_status;
		return (exit_status);
	}
	return (execute_single_command(pipeline->commands, ms));
}
