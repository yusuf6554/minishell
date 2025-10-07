/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:15 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/07 13:59:32 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	execute_pipeline(t_pipeline *pipeline, char ***env)
{
	int		**pipes;
	pid_t	*pids;

	if (!pipeline || !pipeline->commands || pipeline->cmd_count <= 0)
		return (EXIT_FAILURE);
	if (pipeline->cmd_count == 1)
		return (execute_command(pipeline->commands, env));
	if (setup_pipeline_resources(pipeline, &pipes, &pids) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (execute_pipeline_commands(pipeline, pipes, pids, env) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (finalize_pipeline(pipes, pids, pipeline->cmd_count));
}

static void	restore_fds(int original_stdin, int original_stdout)
{
	if (original_stdin > 0)
	{
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
	}
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

static int	setup_and_execute(t_cmd *cmd, char ***env, int *orig_stdout)
{
	int	original_stdin;
	int	exit_status;

	original_stdin = setup_redirections(cmd->redirects, *env, 0);
	if (original_stdin == -1)
	{
		close(*orig_stdout);
		return (EXIT_FAILURE);
	}
	if (is_builtin(cmd->argv[0]))
		exit_status = execute_builtin(cmd->argv, env);
	else
		exit_status = execute_external_command(cmd, env);
	restore_fds(original_stdin, *orig_stdout);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, char ***env)
{
	int	original_stdout;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
		return (EXIT_FAILURE);
	return (setup_and_execute(cmd, env, &original_stdout));
}

int	execute_single_command(t_cmd *cmd, t_minishell *ms)
{
	int	original_stdin;
	int	original_stdout;
	int	exit_status;

	if (!cmd)
		return (EXIT_FAILURE);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdin == -1 || original_stdout == -1)
		return (EXIT_FAILURE);
	exit_status = execute_command(cmd, &ms->env);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	ms->exit_status = exit_status;
	return (exit_status);
}

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	return (pid);
}
