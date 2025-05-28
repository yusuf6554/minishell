/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:50:10 by yukoc             #+#    #+#             */
/*   Updated: 2024/10/22 12:35:15 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*temp_dst;
	char	*temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_dst = (char *)dst;
	temp_src = (char *)src;
	i = -1;
	if (temp_dst >= temp_src)
	{
		while (++i < len)
			temp_dst[len - i - 1] = temp_src[len - i - 1];
	}
	else
	{
		while (++i < len)
			temp_dst[i] = temp_src[i];
	}
	return (dst);
}
