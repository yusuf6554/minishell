/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <yukoc@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:46:36 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/20 15:24:55 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	is_empty_input(char *input)
{
	char	*trimmed;

	if (!input)
		return (1);
	trimmed = ft_strtrim(input, "\t \n");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free_string(trimmed);
		return (1);
	}
	free_string(trimmed);
	return (0);
}

static int	has_unclosed_quotes(char *input)
{
	int		in_single_quote;
	int		in_double_quote;
	char	*current;

	if (!input)
		return (0);
	in_single_quote = 0;
	in_double_quote = 0;
	current = input;
	while (*current)
	{
		if (*current == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*current == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		current++;
	}
	return (in_single_quote || in_double_quote);
}

static void	multiline_sigint_handler(int sig)
{
	extern volatile sig_atomic_t	g_signal;

	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
}

static char	*read_multiline_input(char *initial_input)
{
	char	*line;
	char	*result;
	char	*temp;
	extern volatile sig_atomic_t	g_signal;
	void	(*old_handler)(int);

	result = ft_strdup(initial_input);
	if (!result)
		return (NULL);
	rl_catch_signals = 0;
	old_handler = signal(SIGINT, multiline_sigint_handler);
	while (has_unclosed_quotes(result))
	{
		g_signal = 0;
		line = readline("> ");
		if (!line || g_signal == SIGINT)
		{
			free_string(result);
			if (line)
				free_string(line);
			rl_catch_signals = 1;
			signal(SIGINT, old_handler);
			g_signal = 0;
			return (ft_strdup(""));
		}
		temp = ft_strjoin(result, "\n");
		free_string(result);
		if (!temp)
		{
			free_string(line);
			rl_catch_signals = 1;
			signal(SIGINT, old_handler);
			return (NULL);
		}
		result = ft_strjoin(temp, line);
		free_string(temp);
		free_string(line);
		if (!result)
		{
			rl_catch_signals = 1;
			signal(SIGINT, old_handler);
			return (NULL);
		}
	}
	rl_catch_signals = 1;
	signal(SIGINT, old_handler);
	return (result);
}

char	*read_input(void)
{
	char	*input;
	char	*final_input;
	extern volatile sig_atomic_t	g_signal;

	g_signal = 0;
	input = readline(PROMPT);
	if (!input)
	{
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			return (ft_strdup(""));
		}
		return (NULL);
	}
	if (has_unclosed_quotes(input))
	{
		final_input = read_multiline_input(input);
		free_string(input);
		if (!final_input)
		{
			if (g_signal == SIGINT)
			{
				g_signal = 0;
				return (ft_strdup(""));
			}
		}
		return (final_input);
	}
	return (input);
}
