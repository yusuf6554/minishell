/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:06 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/01 09:09:25 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

sig_atomic_t	g_signal = 0;

static t_minishell	setup_shell(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": cannot execute binary file\n", 2);
		exit(EXIT_CANT_EXEC);
	}
	init_shell(envp, &ms);
	return (ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	setup_signals();
	ms = setup_shell(argc, argv, envp);
	init_shell(envp, &ms);
	shell_loop(&ms);
	cleanup_shell(&ms);
	return (EXIT_SUCCESS);
}
