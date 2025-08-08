/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:35 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 16:58:08 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_exit(char **argv)
{
	int	exit_status;
	int	argc;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	exit_status = EXIT_SUCCESS;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (argv && argv[1])
		exit_status = ft_atoi(argv[1]);
	exit(exit_status);
}
