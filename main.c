/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:06 by yukoc             #+#    #+#             */
/*   Updated: 2025/09/21 12:59:21 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	setup_signals();
	init_shell(envp, &ms);
	shell_loop(&ms);
	cleanup_shell(&ms);
	return (EXIT_SUCCESS);
}
