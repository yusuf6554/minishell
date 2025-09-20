/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:15:28 by yukoc             #+#    #+#             */
/*   Updated: 2025/09/20 13:16:34 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"
#include "../../includes/execution.h"
#include <readline/readline.h>
#include <readline/history.h>

void	init_shell(char **envp, t_minishell *ms)
{
	int	i;

	i = 0;
	ft_memset(ms, 0, sizeof(t_minishell));
	ms->env = env_copy(envp);
	if (!ms->env)
	{
		error_msg(NULL, NULL, "memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = ft_atoi(ft_getenv("SHLVL", ms->env)) + 1;
	if (i <= 1)
		i = 1;
	else if (i > 1000)
	{
		i = 1;
		error_msg("minishell", "SHLVL", "warning: shell level too high, resetting to 1");
	}
	ms->env = env_add_var(ms->env, "SHLVL", ft_itoa(i));
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
	char				*input;
	t_token				*tokens;
	t_pipeline			*pipeline;

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
		if (!tokens)
			continue; // Parse error
		pipeline = parse_pipeline(tokens);
		free_tokens(&tokens);
		if (!pipeline)
			continue; // Parse error
		ms->exit_status = execute_pipeline(pipeline, &ms->env);
		free_pipeline(&pipeline);
	}
}
