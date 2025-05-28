/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:41:57 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/19 01:00:03 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_final;
	size_t	i;

	if (s)
	{
		if (start >= ft_strlen(s) || len == 0 || ft_strlen(s) == 0)
			return (ft_strdup(""));
		i = 0;
		while (i < len && s[i + start])
			i++;
		str_final = malloc((sizeof(char) * i) + 1);
		if (str_final == NULL)
			return (NULL);
		i = 0;
		while (s[i] && i < start)
			i++;
		while (s[i] && i < start + len)
		{
			str_final[i - start] = s[i];
			i++;
		}
		str_final[i - start] = '\0';
		return (str_final);
	}
	return (NULL);
}
