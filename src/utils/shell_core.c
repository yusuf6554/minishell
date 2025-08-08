/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:15:28 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/20 16:59:30 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"
#include "../../includes/execution.h"

void	init_shell(char **envp, t_minishell *ms)
{
	ft_memset(ms, 0, sizeof(t_minishell));
	ms->env = env_copy(envp);
	if (!ms->env)
	{
		error_msg(NULL, NULL, "memory allocation failed");
		exit(EXIT_FAILURE);
	}
	ms->exit_status = 0;
	ms->in_heredoc = 0;
	ms->pid_count = 0;
	ms->pids = NULL;
}

void	cleanup_shell(t_minishell *ms)
{
	if (ms->env)
	{
		env_free(ms->env);
		ms->env = NULL;
	}
	if (ms->pids)
	{
		free_pids(ms->pids);
		ms->pids = NULL;
	}
	rl_clear_history();
}

void	shell_loop(t_minishell *ms)
{
	char		*input;
	t_token		*tokens;
	t_pipeline	*pipeline;

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		if (is_empty_input(input))
		{
			free_string(input);
			continue ;
		}
		add_history(input);
		tokens = tokenize_with_expansion(input, ms->env, ms->exit_status);
		free_string(input);
		pipeline = parse_pipeline(tokens);
		free_tokens(&tokens);
		ms->exit_status = execute_pipeline(pipeline, &ms->env);
		free_pipeline(&pipeline);
	}
}
