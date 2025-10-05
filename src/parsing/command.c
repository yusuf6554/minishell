/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:39:49 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/05 18:25:13 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_cmd			*create_command(void);
static t_redirect		*create_redirect(t_token_type type, char *file);
static t_redirect_type	token_to_redirect_type(t_token_type token_type);
static char				**ft_add_str_to_array(char **array, char *str);

static t_redirect_type	token_to_redirect_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	else if (token_type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	else if (token_type == TOKEN_REDIRECT_APPEND)
		return (REDIRECT_APPEND);
	else if (token_type == TOKEN_REDIRECT_HEREDOC)
		return (REDIRECT_HEREDOC);
	return (REDIRECT_IN);
}

static char	**ft_add_str_to_array(char **array, char *str)
{
	char	**new_array;
	int		i;
	int		count;

	count = 0;
	if (array)
		while (array[count])
			count++;
	new_array = malloc(sizeof(char *) * (count + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[count] = ft_strdup(str);
	new_array[count + 1] = NULL;
	if (array)
		free(array);
	return (new_array);
}

static int	handle_redirect(t_cmd *cmd, t_token **tokens)
{
	t_redirect		*redirect;
	t_token_type	redirect_type;

	redirect_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (0);
	redirect = create_redirect(redirect_type, (*tokens)->value);
	if (!redirect)
		return (0);
	redirect->next = cmd->redirects;
	cmd->redirects = redirect;
	return (1);
}

t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_EOF)
	{
		if ((*tokens)->type == TOKEN_WORD)
			cmd->argv = ft_add_str_to_array(cmd->argv, (*tokens)->value);
		else if (!handle_redirect(cmd, tokens))
			return (free_command(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	if (!cmd->argv || !*cmd->argv)
		return (free_command(cmd), NULL);
	return (cmd);
}

static t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_command(t_cmd *cmd)
{
	t_redirect	*current;
	t_redirect	*next;
	int			i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	current = cmd->redirects;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
	free(cmd);
}

static t_redirect	*create_redirect(t_token_type type, char *file)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = token_to_redirect_type(type);
	redirect->file = NULL;
	redirect->fd = -1;
	redirect->next = NULL;
	redirect->content = NULL;
	redirect->quoted = 0;
	if (file)
	{
		redirect->file = ft_strdup(file);
		if (!redirect->file)
		{
			free(redirect);
			return (NULL);
		}
	}
	return (redirect);
}
