/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:39:49 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/24 13:35:49 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_cmd	*create_command(void);
static t_redirect	*create_redirect(t_token_type type, char *file);
static void	free_redirects(t_redirect **redirects);

t_cmd	*parse_command(t_token **tokens)
{
	t_cmd		*cmd;
	t_redirect	*redirect;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_EOF)
	{
		if ((*tokens)->type == TOKEN_WORD)
			cmd->argv = ft_add_str_to_array(cmd->argv, (*tokens)->value);
		else if ((*tokens)->type != TOKEN_WORD)
		{
			redirect = create_redirect((*tokens)->type, (*tokens)->value);
			if (!redirect)
				return (free_command(cmd), NULL);
			redirect->next = cmd->redirects;
			cmd->redirects = redirect;
		}
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

	if (!cmd)
		return ;
	if (cmd->argv)
		free_string_array(cmd->argv);
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
	redirect->type = ((t_redirect_type)((int)type - 2));
	redirect->file = NULL;
	redirect->fd = -1;
	redirect->next = NULL;
	if (file)
	{
		redirect->file = ft_strdup(file);
		if (!redirect->file)
		{
			free_redirects(&redirect);
			return (NULL);
		}
	}
	return (redirect);
}

static void	free_redirects(t_redirect **redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	if (!redirects || !*redirects)
		return ;
	current = *redirects;
	while (current)
	{
		next = current->next;
		free_string(current->file);
		free(current);
		current = next;
	}
	*redirects = NULL;
}
