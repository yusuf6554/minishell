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
	int		exit_status;

	if (!pipeline || !pipeline->commands || pipeline->cmd_count <= 0)
		return (EXIT_FAILURE);
	if (pipeline->cmd_count == 1)
		return (execute_command(pipeline->commands, env));
	pipes = create_pipes(pipeline->cmd_count - 1);
	if (!pipes)
		return (EXIT_FAILURE);
	pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!pids)
	{
		close_pipes(pipes, pipeline->cmd_count - 1);
		return (EXIT_FAILURE);
	}
	close_pipes(pipes, pipeline->cmd_count - 1);
	exit_status = wait_for_processes(pids, pipeline->cmd_count);
	free(pids);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, char ***env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	if (setup_redirections(cmd->redirects) == -1)
		return (EXIT_FAILURE);
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(cmd->argv, env));
	return (execute_external_command(cmd, env));
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

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		return (1);
	return (0);
}
