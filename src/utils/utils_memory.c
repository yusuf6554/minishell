/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:51:19 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/24 13:31:02 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_copy_array(char **dest, char **src, int count);

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

char	**ft_add_str_to_array(char **array, char *str)
{
	int		count;
	char	**new_array;

	if (!array)
	{
		new_array = malloc(2 * sizeof(char *));
		if (!new_array)
			return (NULL);
		new_array[0] = ft_strdup(str);
		new_array[1] = NULL;
		return (new_array);
	}
	count = 0;
	while (array[count])
		count++;
	new_array = malloc((count + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	ft_copy_array(new_array, array, count);
	new_array[count] = ft_strdup(str);
	new_array[count + 1] = NULL;
	free(array);
	return (new_array);
}

static void	ft_copy_array(char **dest, char **src, int count)
{
	int	i;

	if (!dest || !src || count <= 0)
		return ;
	i = -1;
	while (++i < count)
		dest[i] = ft_strdup(src[i]);
}
