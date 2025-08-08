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

char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		return (NULL);
	return (input);
}
