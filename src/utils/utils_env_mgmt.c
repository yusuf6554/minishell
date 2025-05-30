/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:56:14 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 22:29:12 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**env_add_var_copy(char **env, char *variable)
{
	char	**new_env;
	char	*copy_str;
	int		i;
	int		arr_len;

	arr_len = count_string_array(env);
	if (arr_len < 1)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * (arr_len + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i] && i < arr_len)
	{
		copy_str = ft_strdup(env[i]);
		if (!copy_str)
			return (free_string_array(new_env), NULL);
		new_env[i] = copy_str;
	}
	new_env[i] = variable;
	new_env[i + 1] = NULL;
	free_string_array(env);
	return (new_env);
}

char	**env_add_var(char **env, char *name, char *value)
{
	int		index;
	char	*variable;
	char	*temp;

	if (!env || !name || !env_validate_name(name))
		return (env);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	if (value)
		variable = ft_strjoin(temp, value);
	else
		variable = ft_strdup(temp);
	free(temp);
	if (!variable)
		return (NULL);
	index = env_find_index(env, name);
	if (index >= 0)
	{
		free(env[index]);
		env[index] = variable;
		return (env);
	}
	else
		return (env_add_var_copy(env, variable));
}

static char	**env_remove_var_copy(char **env, int index, int env_len)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * (env_len));
	if (!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (env_free(new_env), NULL);
			j++;
		}
	}
	new_env[j] = NULL;
	env_free(env);
	return (new_env);
}

char	**env_remove_var(char **env, char *name)
{
	int		index;
	int		env_len;
	char	**new_env;

	if (!env || !name)
		return (env);
	index = env_find_index(env, name);
	if (index < 0)
		return (env);
	env_len = count_string_array(env);
	if (env_len <= 1)
		return (env_free(env), NULL);
	new_env = env_remove_var_copy(env, index, env_len);
	if (!new_env)
		return (NULL);
	return (new_env);
}
