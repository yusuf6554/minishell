/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:18:04 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/15 14:27:37 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_final;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str_final = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str_final == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_final[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str_final[len1 + i] = s2[i];
		i++;
	}
	str_final[len1 + i] = '\0';
	return (str_final);
}
