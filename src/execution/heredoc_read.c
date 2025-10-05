/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:59:37 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/05 18:04:14 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*read_heredoc_content(int fd)
{
	char	*content;
	int		size;
	char	*line;

	content = NULL;
	size = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		content = ft_strjoin_gnl(content, line);
		if (!content)
			return (free_string(line), NULL);
		size += ft_strlen(line) + 1;
		free_string(line);
		line = get_next_line(fd);
	}
	if (size == 0)
		return (ft_strdup(""));
	return (content);
}
