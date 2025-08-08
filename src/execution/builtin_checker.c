/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:51:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 14:44:26 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	check_basic_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		return (1);
	return (0);
}

static int	check_env_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		return (1);
	return (0);
}

static int	check_exit_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (check_basic_builtins(cmd))
		return (1);
	if (check_env_builtins(cmd))
		return (1);
	if (check_exit_builtin(cmd))
		return (1);
	return (0);
}
