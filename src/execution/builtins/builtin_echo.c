/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:24 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:17:26 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	if (!argv)
		return (EXIT_FAILURE);
	newline = 1;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0 && argv[1][2] == '\0')
	{
		newline = 0;
		i = 2;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
