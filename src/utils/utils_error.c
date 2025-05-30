/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:29 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 22:56:10 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(char *cmd, char *arg, char *msg)
{
	if (!msg)
		return ;
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	perror_msg(char *cmd)
{
	char	*msg;

	if (!cmd)
	{
		perror("minishell");
		return ;
	}
	msg = ft_strjoin("minishell: ", cmd);
	if (!msg)
	{
		perror("minishell");
		return ;
	}
	perror(msg);
	free(msg);
}
