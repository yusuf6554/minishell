/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:29 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:17:31 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_env(char **env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
