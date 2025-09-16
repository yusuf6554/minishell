/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:50:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/08/15 15:44:07 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/parsing.h"

static char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (!full_path)
			return (free_string_array(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_string_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	if (!result)
		free_string_array(paths);
	return (result);
}

static int	execute_child_process(char *executable, t_cmd *cmd, char ***env)
{
	setup_child_signals();
	if (execve(executable, cmd->argv, *env) == -1)
	{
		perror_msg("execve");
		free(executable);
		exit(EXIT_CANT_EXEC);
	}
	return (EXIT_SUCCESS);
}

int	execute_external_command(t_cmd *cmd, char ***env)
{
	pid_t	pid;
	char	*executable;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	executable = find_executable(cmd->argv[0], *env);
	if (!executable)
	{
		command_not_found(cmd->argv[0]);
		return (EXIT_NOT_FOUND);
	}
	pid = create_process();
	if (pid == -1)
		return (free(executable), EXIT_FAILURE);
	if (pid == 0)
		return (execute_child_process(executable, cmd, env));
	free(executable);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}
