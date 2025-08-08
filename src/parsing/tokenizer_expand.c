/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:11:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/07/20 17:17:56 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*expand_exit_status(char *str, int exit_status)
{
	char	*status_str;
	char	*result;
	char	*temp;

	status_str = ft_itoa(exit_status);
	if (!status_str)
		return (NULL);
	if (ft_strlen(str) == 2)
		result = ft_strdup(status_str);
	else
	{
		temp = ft_strjoin(status_str, str + 2);
		result = temp;
	}
	free_string(status_str);
	return (result);
}

char	*expand_variables(char *str, char **env, int exit_status)
{
	char	*result;
	char	*expanded;

	if (!str || !ft_strchr(str, '$'))
		return (NULL);
	if (ft_strncmp(str, "$?", 2) == 0)
		return (expand_exit_status(str, exit_status));
	result = ft_strdup(str);
	expanded = expand_env_vars(result, env);
	free_string(result);
	return (expanded);
}

static char	*build_result(char *prefix, char *var_value, char *suffix)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(prefix, var_value);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, suffix);
	free_string(temp);
	return (result);
}

static void	extract_var_name(char *var_start, char **var_end, char **name)
{
	*var_end = var_start + 1;
	while (**var_end && (ft_isalnum(**var_end) || **var_end == '_'))
		(*var_end)++;
	*name = ft_substr(var_start + 1, 0, *var_end - var_start - 1);
}

static char	*process_single_var(char *result, char *var_start, char **env)
{
	char	*var_end;
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;

	extract_var_name(var_start, &var_end, &var_name);
	if (var_end == var_start + 1)
		return (result);
	*var_start = '\0';
	prefix = ft_strdup(result);
	*var_start = '$';
	var_value = ft_getenv(var_name, env);
	if (!var_value)
		var_value = "";
	suffix = ft_strdup(var_end);
	free_string(result);
	result = build_result(prefix, var_value, suffix);
	free_string(prefix);
	free_string(suffix);
	free_string(var_name);
	return (result);
}

char	*expand_env_vars(char *str, char **env)
{
	char	*result;
	char	*var_start;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup(str);
	var_start = ft_strchr(result, '$');
	while (var_start)
	{
		result = process_single_var(result, var_start, env);
		var_start = ft_strchr(result, '$');
	}
	return (result);
}
