/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:22:06 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/20 14:43:12 by ehabes           ###   ########.fr       */
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
