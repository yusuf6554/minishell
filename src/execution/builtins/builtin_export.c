/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:40 by ehabes            #+#    #+#             */
/*   Updated: 2025/08/13 14:56:24 by ehabes           ###   ########.fr       */
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
	if ((str[start] == '"' && str[end] == '"') ||
		(str[start] == '\'' && str[end] == '\''))
	{
		if (len == 2)
			return (ft_strdup(""));
		result = ft_substr(str, 1, len - 2);
	}
	else
		result = ft_strdup(str);
	return (result);
}

static int	export_single_var(char *arg, char ***env)
{
	char	*eq_pos;
	char	*name;
	char	*value;
	char	*unquoted_value;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	name = ft_substr(arg, 0, eq_pos - arg);
	value = ft_strdup(eq_pos + 1);
	unquoted_value = remove_quotes(value);
	if (name && unquoted_value)
		*env = env_add_var(*env, name, unquoted_value);
	if (name)
		free(name);
	if (value)
		free(value);
	if (unquoted_value)
		free(unquoted_value);
	return (1);
}

int	builtin_export(char **argv, char ***env)
{
	int	i;

	if (!argv || !env)
		return (EXIT_FAILURE);
	if (!argv[1])
	{
		builtin_env(*env);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (argv[i])
	{
		export_single_var(argv[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
