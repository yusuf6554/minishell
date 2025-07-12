/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:35 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/12 16:17:37 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_exit(char **argv)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argv && argv[1])
		exit_status = ft_atoi(argv[1]);
	exit(exit_status);
}
