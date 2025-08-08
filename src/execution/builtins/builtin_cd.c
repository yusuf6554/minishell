/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:18 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:17:21 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	update_pwd_env(char ***env, char *old_pwd, char *new_pwd)
{
	(void)env;
	(void)old_pwd;
	(void)new_pwd;
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
