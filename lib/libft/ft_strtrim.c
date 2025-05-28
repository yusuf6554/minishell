/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:33:34 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/16 14:43:18 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_check_trimset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*str_final;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_check_trimset(s1[start], set))
		start++;
	while (end > start && ft_check_trimset(s1[end - 1], set))
		end--;
	str_final = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (str_final == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		str_final[i++] = s1[start++];
	str_final[i] = '\0';
	return (str_final);
}
