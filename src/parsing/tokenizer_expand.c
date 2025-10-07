/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:11:00 by ehabes            #+#    #+#             */
/*   Updated: 2025/10/07 13:53:11 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*expand_exit_status(char *str, int exit_status)
{
	char				*status_str;
	char				*result;
	char				*temp;
	unsigned long		var_pos;

	status_str = ft_itoa(exit_status);
	if (!status_str)
		return (NULL);
	if (ft_strlen(str) == 2)
		result = ft_strdup(status_str);
	else
	{
		var_pos = (unsigned long)ft_strnstr(str, "$?", ft_strlen(str));
		if (!var_pos)
			return (free_string(status_str), NULL);
		temp = ft_substr(str, 0, var_pos - (unsigned long)str);
		temp = ft_strjoin(temp, status_str);
		result = ft_strjoin(temp, (char *)(var_pos + 2));
		free_string(temp);
	}
	free_string(status_str);
	return (result);
}

static int	should_expand_at_position(char *str, int pos)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (i < pos)
	{
		if (!in_double_quotes && str[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && str[i] == '"')
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (!in_single_quotes);
}

char	*expand_variables(char *str, char **env, int exit_status)
{
	char	*result;
	char	*expanded;
	char	*dollar_pos;

	if (!str || !ft_strchr(str, '$'))
		return (NULL);
	dollar_pos = ft_strchr(str, '$');
	if (!should_expand_at_position(str, dollar_pos - str))
		return (NULL);
	expanded = str;
	if (ft_strncmp(dollar_pos, "$?", 2) == 0)
		expanded = expand_exit_status(str, exit_status);
	result = ft_strdup(expanded);
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

char	*expand_env_vars(char *input, char **env)
{
	char	*var_pos;
	char	*result;

	result = ft_strdup(input);
	if (!result)
		return (NULL);
	var_pos = ft_strchr(result, '$');
	while (var_pos)
	{
		result = process_single_var(result, var_pos, env);
		if (!result)
			return (NULL);
		var_pos = ft_strchr(var_pos + 1, '$');
	}
	return (result);
}
