/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:40 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 17:08:12 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	export_single_var(char *arg, char ***env)
{
	char	*eq_pos;
	char	*name;
	char	*value;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	name = ft_substr(arg, 0, eq_pos - arg);
	value = ft_strdup(eq_pos + 1);
	if (name && value)
		*env = env_add_var(*env, name, value);
	if (name)
		free(name);
	if (value)
		free(value);
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
