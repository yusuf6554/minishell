/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:02 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:18:10 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	execute_builtin(char **argv, char ***env)
{
	if (!argv || !argv[0])
		return (EXIT_FAILURE);
	if (ft_strncmp(argv[0], "echo", 4) == 0 && argv[0][4] == '\0')
		return (builtin_echo(argv));
	if (ft_strncmp(argv[0], "cd", 2) == 0 && argv[0][2] == '\0')
		return (builtin_cd(argv, env));
	if (ft_strncmp(argv[0], "pwd", 3) == 0 && argv[0][3] == '\0')
		return (builtin_pwd());
	if (ft_strncmp(argv[0], "export", 6) == 0 && argv[0][6] == '\0')
		return (builtin_export(argv, env));
	if (ft_strncmp(argv[0], "unset", 5) == 0 && argv[0][5] == '\0')
		return (builtin_unset(argv, env));
	if (ft_strncmp(argv[0], "env", 3) == 0 && argv[0][3] == '\0')
		return (builtin_env(*env));
	if (ft_strncmp(argv[0], "exit", 4) == 0 && argv[0][4] == '\0')
		return (builtin_exit(argv));
	return (EXIT_FAILURE);
}
