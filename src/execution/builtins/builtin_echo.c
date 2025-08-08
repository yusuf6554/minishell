/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:24 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 17:08:34 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static char	*remove_quotes(char *str)
{
	char	*result;
	int		len;
	int		start;
	int		end;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	start = 0;
	end = len - 1;
	if ((str[0] == '"' && str[end] == '"') || \
		(str[0] == '\'' && str[end] == '\''))
	{
		start = 1;
		end = len - 2;
	}
	result = ft_substr(str, start, end - start + 1);
	return (result);
}

int	builtin_echo(char **argv)
{
	int		i;
	int		newline;
	char	*unquoted;

	if (!argv)
		return (EXIT_FAILURE);
	newline = 1;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0 && argv[1][2] == '\0')
	{
		newline = 0;
		i = 2;
	}
	while (argv[i])
	{
		unquoted = remove_quotes(argv[i]);
		ft_putstr_fd(unquoted, STDOUT_FILENO);
		free(unquoted);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
