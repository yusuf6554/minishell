/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:34:21 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/27 21:39:58 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_pipeline	*parse_pipeline(t_token *tokens)
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = NULL;
	while (tokens)
	{
		cmd = parse_command(&tokens);
		if (!cmd)
		{
			free_pipeline(&pipeline);
			return (NULL);
		}
		add_command(pipeline, cmd);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (pipeline);
}

void	free_pipeline(t_pipeline **pipeline)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!pipeline || !*pipeline)
		return ;
	current = (*pipeline)->commands;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
	free(*pipeline);
	*pipeline = NULL;
}

void	add_command(t_pipeline *pipeline, t_cmd *cmd)
{
	t_cmd	*current;

	if (!pipeline || !cmd)
		return ;
	if (!pipeline->commands)
	{
		pipeline->commands = cmd;
	}
	else
	{
		current = pipeline->commands;
		while (current->next)
			current = current->next;
		current->next = cmd;
	}
	pipeline->cmd_count++;
}
