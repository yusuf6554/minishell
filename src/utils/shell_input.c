/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:46:36 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/04 23:09:56 by yukoc            ###   ########.fr       */
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
		return (1);
	free_string(trimmed);
	return (0);
}

char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (is_empty_input(input))
		return (free_string(input), NULL);
	return (input);
}
