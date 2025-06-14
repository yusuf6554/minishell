/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:06 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/04 23:05:03 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	init_shell(envp, &ms);
	shell_loop(&ms);
	cleanup_shell(&ms);
	return (EXIT_SUCCESS);
}
