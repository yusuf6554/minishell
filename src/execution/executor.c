/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:15 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:18:15 by ehabes           ###   ########.fr       */
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

int	execute_command(t_cmd *cmd, char ***env)
{
	int	original_stdin;
	int	original_stdout;
	int	exit_status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
		return (EXIT_FAILURE);
	original_stdin = setup_redirections(cmd->redirects, *env, 0);
	if (original_stdin == -1)
	{
		close(original_stdout);
		return (EXIT_FAILURE);
	}
	if (is_builtin(cmd->argv[0]))
		exit_status = execute_builtin(cmd->argv, env);
	else
		exit_status = execute_external_command(cmd, env);
	if (original_stdin > 0)
	{
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
	}
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	return (exit_status);
}

int	execute_single_command(t_cmd *cmd, char ***env)
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
	exit_status = execute_command(cmd, env);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
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
