/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:01:27 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/05 18:20:22 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	cleanup_heredoc(t_pipeline *pipeline)
{
	t_cmd		*cmd;
	t_redirect	*rdr;

	if (!pipeline)
		return ;
	cmd = pipeline->commands;
	while (cmd)
	{
		rdr = cmd->redirects;
		if (cmd->redirects)
		{
			while (rdr)
			{
				if (rdr->type == REDIRECT_HEREDOC && rdr->content)
				{
					free_string(rdr->content);
					rdr->content = NULL;
				}
				rdr = rdr->next;
			}
		}
		cmd = cmd->next;
	}
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
			result = handle_heredoc(current, ms);
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
