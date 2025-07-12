/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:46:22 by ehabes            #+#    #+#             */
/*   Updated: 2025/06/24 17:42:44 by ehabes           ###   ########.fr       */
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
