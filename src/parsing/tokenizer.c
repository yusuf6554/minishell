/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:43:37 by yukoc             #+#    #+#             */
/*   Updated: 2025/09/21 14:03:38 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"
static t_token_type	tokenize_type(char *value);
static char			*remove_quotes(char *str);
static char			**quote_aware_split(char *input);
static t_token		*add_token(t_token *tokens, t_token *new_token);
static t_token		*add_expanded_tokens(t_token *tokens, char *expanded);

static t_token	*process_tokens(char **split)
{
	t_token			*tokens;
	t_token			*new_tokens;
	t_token			*current;
	t_token_type	type;
	int				i;

	tokens = NULL;
	i = 0;
	while (split[i])
	{
		type = tokenize_type(split[i]);
		new_tokens = create_token(split[i], type);
		if (!new_tokens)
		{
			free_string_array(split);
			free_tokens(&tokens);
			return (NULL);
		}
		if (!tokens)
			tokens = new_tokens;
		else
		{
			current = tokens;
			while (current->next)
				current = current->next;
			current->next = new_tokens;
		}
		i++;
	}
	return (tokens);
}

t_token	*tokenize(char *input)
{
	char	**split;
	t_token	*tokens;

	split = quote_aware_split(input);
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
			tokens = add_expanded_tokens(tokens, expanded);
			free_string(expanded);
		}
		else
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
		}
		i++;
	}
	return (tokens);
}

t_token	*tokenize_with_expansion(char *input, char **env, int exit_status)
{
	char	**split;
	t_token	*tokens;
	int		i;

	split = quote_aware_split(input);
	if (!split)
		return (NULL);
	if (split[0][0] == '|')
	{
		if (split[0][1] == '|')
			error_msg("minishell", NULL, "syntax error near unexpected token `||'");
		else
			error_msg("minishell", NULL, "syntax error near unexpected token `|'");
		free_string_array(split);
		return (NULL);
	}
	i = count_string_array(split);
	if (split[i - 1][0] == '|')
	{
		if (split[i - 1][1] == '|')
			error_msg("minishell", NULL, "syntax error near unexpected token `||'");
		else
			error_msg("minishell", NULL, "syntax error near unexpected token `|'");
		free_string_array(split);
		return (NULL);
	}
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

static char	*remove_quotes(char *str)
{
	char	*result;
	char	*current;
	char	*write_pos;
	int		in_double_quotes;
	int		in_single_quotes;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	current = str;
	write_pos = result;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while (*current)
	{
		if (!in_single_quotes && *current == '"')
		{
			in_double_quotes = !in_double_quotes;
		}
		else if (!in_double_quotes && *current == '\'')
		{
			in_single_quotes = !in_single_quotes;
		}
		else
		{
			*write_pos = *current;
			write_pos++;
		}
		current++;
	}
	*write_pos = '\0';
	return (result);
}

t_token *create_token(char *value, t_token_type type)
{
	t_token *new_token;
	char *processed_value;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (value)
	{
		if (type == TOKEN_WORD)
		{
			processed_value = remove_quotes(value);
			new_token->value = processed_value;
			new_token->type = type;
			new_token->next = NULL;
		}
		else
		{
			new_token->value = ft_strdup(value);
			new_token->type = type;
			new_token->next = NULL;
		}
	}
	else
	{
		new_token->value = NULL;
		new_token->type = type;
		new_token->next = NULL;
	}
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

static char	**quote_aware_split(char *input)
{
	char	**result;
	char	*start;
	char	*current;
	int		count;
	int		in_quotes;
	char	quote_char;

	if (!input)
		return (NULL);
	count = 0;
	current = input;
	in_quotes = 0;
	quote_char = 0;
	while (*current)
	{
		while (*current == ' ' && !in_quotes)
			current++;
		if (!*current)
			break;
		start = current;
		while (*current)
		{
			if (!in_quotes && (*current == '"' || *current == '\''))
			{
				in_quotes = 1;
				quote_char = *current;
			}
			else if (in_quotes && *current == quote_char)
			{
				in_quotes = 0;
				quote_char = 0;
			}
			else if (!in_quotes && *current == ' ')
				break;
			current++;
		}
		count++;
		if (*current)
			current++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	current = input;
	count = 0;
	in_quotes = 0;
	quote_char = 0;
	while (*current)
	{
		while (*current == ' ' && !in_quotes)
			current++;
		if (!*current)
			break;
		start = current;
		while (*current)
		{
			if (!in_quotes && (*current == '"' || *current == '\''))
			{
				in_quotes = 1;
				quote_char = *current;
			}
			else if (in_quotes && *current == quote_char)
			{
				in_quotes = 0;
				quote_char = 0;
			}
			else if (!in_quotes && *current == ' ')
				break;
			current++;
		}
		result[count] = ft_substr(start, 0, current - start);
		count++;
		if (*current)
			current++;
	}
	result[count] = NULL;
	return (result);
}

static t_token	*add_expanded_tokens(t_token *tokens, char *expanded)
{
	char			**expanded_split;
	t_token			*new_token;
	t_token_type	type;
	int				i;

	if (!expanded || ft_strchr(expanded, ' '))
	{
		expanded_split = quote_aware_split(expanded);
		if (!expanded_split)
			return (tokens);
		i = 0;
		while (expanded_split[i])
		{
			type = tokenize_type(expanded_split[i]);
			new_token = create_token(expanded_split[i], type);
			if (new_token)
				tokens = add_token(tokens, new_token);
			i++;
		}
		free_string_array(expanded_split);
		return (tokens);
	}
	type = tokenize_type(expanded);
	new_token = create_token(expanded, type);
	if (new_token)
		tokens = add_token(tokens, new_token);
	return (tokens);
}