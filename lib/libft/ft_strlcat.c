/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:28:55 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/20 12:34:30 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	if (dstsize - 1 > len && dstsize > 0)
	{
		while (src[i] && dstsize - 1 > len + i)
		{
			dst[i + len] = src[i];
			i++;
		}
		dst[len + i] = '\0';
	}
	if (len >= dstsize)
		len = dstsize;
	return (len + ft_strlen(src));
}
