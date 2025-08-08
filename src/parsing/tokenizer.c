/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:43:37 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/20 17:16:08 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static t_token_type	tokenize_type(char *value);
static t_token		*add_token(t_token *tokens, t_token *new_token);

static t_token	*process_tokens(char **split)
{
	t_token			*tokens;
	t_token			*new_token;
	t_token_type	type;
	int				i;

	tokens = NULL;
	i = 0;
	while (split[i])
	{
		type = tokenize_type(split[i]);
		new_token = create_token(split[i], type);
		if (!new_token)
		{
			free_string_array(split);
			free_tokens(&tokens);
			return (NULL);
		}
		tokens = add_token(tokens, new_token);
		i++;
	}
	return (tokens);
}

t_token	*tokenize(char *input)
{
	char	**split;
	t_token	*tokens;

	split = ft_split(input, ' ');
	if (!split)
		return (NULL);
	tokens = process_tokens(split);
	free_string_array(split);
	return (tokens);
}

static t_token	*process_expanded_tokens(char **split, char **env, int es)
{
	t_token			*tokens;
	t_token			*new_token;
	char			*expanded;
	t_token_type	type;
	int				i;

	tokens = NULL;
	i = 0;
	while (split[i])
	{
		expanded = expand_variables(split[i], env, es);
		if (expanded)
		{
			type = tokenize_type(expanded);
			new_token = create_token(expanded, type);
		}
		else
		{
			type = tokenize_type(split[i]);
			new_token = create_token(split[i], type);
		}
		if (expanded)
			free_string(expanded);
		if (!new_token)
		{
			free_string_array(split);
			free_tokens(&tokens);
			return (NULL);
		}
		tokens = add_token(tokens, new_token);
		i++;
	}
	return (tokens);
}

t_token	*tokenize_with_expansion(char *input, char **env, int exit_status)
{
	char	**split;
	t_token	*tokens;

	split = ft_split(input, ' ');
	if (!split)
		return (NULL);
	tokens = process_expanded_tokens(split, env, exit_status);
	free_string_array(split);
	return (tokens);
}



static t_token_type	tokenize_type(char *value)
{
	if (ft_strncmp(value, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(value, ">>", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(value, "<<", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(value, ">", 2) == 0)
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
		new_token->value = ft_strdup(value);
	else
		new_token->value = NULL;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static t_token	*add_token(t_token *tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens)
		return (new_token);
	current = tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (tokens);
}