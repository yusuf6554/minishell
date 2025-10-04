/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:01:27 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/01 10:13:19 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	handle_heredocs(t_pipeline *pipeline, t_minishell *ms)
{
	t_cmd		*current;
	int			result;

	current = pipeline->commands;
	while (current)
	{
		result = handle_heredoc_in_command(current, ms, pipeline);
		if (result != 0)
			return (-1);
		current = current->next;
	}
	return (1);
}

static int	handle_heredoc_in_command(t_cmd *cmd, t_minishell *ms, \
	t_pipeline *pipeline)
{
	t_redirect	*current;
	int			result;

	if (!cmd->redirects)
		return (0);
	current = cmd->redirects;
	while (current)
	{
		if (current->type == REDIRECT_HEREDOC)
		{
			ms->in_heredoc = 1;
			result = handle_single_heredoc(current->file, &ms->env, ms->exit_status);
			ms->in_heredoc = 0;
			if (result != 0)
			{
				cleanup_heredoc(pipeline);
				ms->exit_status = result;
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}
