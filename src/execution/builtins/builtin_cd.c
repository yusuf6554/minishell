/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:18 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/07 13:23:46 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	update_pwd_env(char ***env, char *old_pwd, char *new_pwd)
{
	if (old_pwd)
	{
		if (set_env_var(env, "OLDPWD", old_pwd) == -1)
		{
			perror_msg("cd");
			return (-1);
		}
	}
	if (new_pwd)
	{
		if (set_env_var(env, "PWD", new_pwd) == -1)
		{
			perror_msg("cd");
			return (-1);
		}
	}
	return (0);
}

static int	handle_cd_path(char **argv, char *old_pwd)
{
	char	*path;

	if (!argv || !argv[1])
		path = getenv("HOME");
	else
		path = argv[1];
	if (!path)
	{
		error_msg("cd", NULL, "HOME not set");
		if (old_pwd)
			free(old_pwd);
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror_msg("cd");
		if (old_pwd)
			free(old_pwd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **argv, char ***env)
{
	char	*old_pwd;
	char	*new_pwd;
	int		result;

	if (argv && argv[1] && argv[2])
	{
		error_msg("cd", NULL, "too many arguments");
		return (2);
	}
	old_pwd = getcwd(NULL, 0);
	result = handle_cd_path(argv, old_pwd);
	if (result != EXIT_SUCCESS)
		return (result);
	new_pwd = getcwd(NULL, 0);
	update_pwd_env(env, old_pwd, new_pwd);
	if (old_pwd)
		free(old_pwd);
	if (new_pwd)
		free(new_pwd);
	return (EXIT_SUCCESS);
}
