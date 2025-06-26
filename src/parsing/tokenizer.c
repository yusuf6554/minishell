/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:43:37 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/26 14:08:37 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*tokenize(char *input)
{
	t_token			*tokens;
	char			*current;
	char			**split;
	t_token_type	type;

	tokens = NULL;
	current = input;
	split = ft_split(current, " ");
	while (*split)
	{
		type = tokenize_type(*split);
		tokens = create_token(*split, type);
		split++;
	}
	return (tokens);
}

static t_token_type	tokenize_type(char *value)
{
	if (strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (strcmp(value, "<<") == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else if (strcmp(value, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	else if (strcmp(value, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_WORD);
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (value)
		new_token->value = strdup(value);
	else
		new_token->value = NULL;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}
