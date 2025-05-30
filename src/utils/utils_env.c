/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:55:52 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 21:29:18 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		len;
	char	*eq_pos;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = -1;
	while (env[++i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos && (eq_pos - env[i]) == len)
			if (ft_strncmp(name, env[i], len) == 0)
				return (eq_pos + 1);
	}
	return (NULL);
}

int	env_find_index(char **env, char *name)
{
	int		i;
	int		len;
	char	*eq_pos;

	if (!name || !env)
		return (-1);
	len = ft_strlen(name);
	i = -1;
	while (env[++i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos && (eq_pos - env[i]) == len)
			if (ft_strncmp(name, env[i], len) == 0)
				return (i);
	}
	return (-1);
}

int	env_validate_name(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (0);
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}

void	env_free(char **env)
{
	if (env)
		free_string_array(env);
}

char	**env_copy(char **env)
{
	char	**new_env;

	if (!env)
		return (NULL);
	new_env = copy_string_array(env);
	if (!new_env)
		return (NULL);
	return (new_env);
}
