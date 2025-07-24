/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:23:31 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/24 13:38:46 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_string(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_pids(pid_t *pids)
{
	if (!pids)
		return ;
	free(pids);
}
/*
void	free_tokens(t_token **token)
{
	t_token	*cur;
	t_token	*tmp;

	if (!token || !(*token))
		return ;
	cur = *token;
	while (cur)
	{
		tmp = cur->next;
		free_string(cur->value);
		free(cur);
		cur = tmp;
	}
	*token = NULL;
}
*/

/*
void	free_pipeline(t_pipeline **pipeline)
{
	
}
*/