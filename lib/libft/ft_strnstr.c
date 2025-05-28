/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:37:53 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/22 12:37:11 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	const char	*str1;
	const char	*str2;

	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		str1 = haystack;
		str2 = needle;
		i = 0;
		while (str2[i] == str1[i] && str2[i] && len - i > 0)
			i++;
		if (str2[i] == '\0')
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
