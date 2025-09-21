/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:24 by ehabes            #+#    #+#             */
/*   Updated: 2025/09/21 13:33:20 by yukoc            ###   ########.fr       */
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

static int	check_for_n_flags(char **argv, int *index)
{
	int	i;
	int	j;
	int	flag_found;

	i = 1;
	j = 0;
	flag_found = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			break ;
		j = 1;
		while (argv[i][j] && argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0' || j == 1)
			break ;
		flag_found++;
		i++;
	}
	*index = i;
	return (flag_found);
}

int	builtin_echo(char **argv)
{
	int		i;
	int		newline;
	char	*unquoted;
	int		dash_skipped;

	if (!argv)
		return (EXIT_FAILURE);
	newline = 1;
	i = 1;
	dash_skipped = 0;
	if (argv[1] && check_for_n_flags(argv, &i))
		newline = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-' && !dash_skipped)
		{
			if (argv[i][1] == '\0')
				i++;
			dash_skipped = 1;
		}
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
