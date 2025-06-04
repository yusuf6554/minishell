/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:51:19 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/04 22:24:38 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	count_string_array(char **arr)
{
	int	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**copy_string_array(char **arr)
{
	char	**new_arr;
	char	*copy_str;
	int		i;
	int		arr_len;

	if (!arr)
		return (NULL);
	arr_len = count_string_array(arr);
	if (arr_len < 1)
		return (NULL);
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		copy_str = ft_strdup(arr[i]);
		if (!copy_str)
			return (free_string_array(new_arr), NULL);
		new_arr[i] = copy_str;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
