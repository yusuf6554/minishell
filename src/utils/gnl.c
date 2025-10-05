/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:47:24 by yukoc             #+#    #+#             */
/*   Updated: 2025/10/05 18:28:30 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_read_file(int fd, char *str)
{
	char	*tmp;
	int		bytes;

	tmp = malloc(2 * sizeof(char));
	if (tmp == NULL)
		return (free(str), NULL);
	bytes = 1;
	while (!ft_strchr_gnl(str, '\n') && (bytes != 0))
	{
		bytes = read(fd, tmp, 1);
		if (bytes == -1)
			return (free(str), free(tmp), NULL);
		tmp[bytes] = '\0';
		str = ft_strjoin_gnl(str, tmp);
		if (str == NULL)
			return (free(str), free(tmp), NULL);
	}
	free(tmp);
	return (str);
}

static char	*ft_get_line(char *full_str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!full_str[i])
		return (NULL);
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (full_str[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (full_str[++i] != '\n' && full_str[i])
		line[i] = full_str[i];
	if (full_str[i] == '\n')
	{
		line[i] = full_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_get_rof(char *full_str)
{
	size_t	i;
	size_t	j;
	char	*rof;

	i = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (!full_str[i])
		return (free(full_str), NULL);
	rof = (char *)malloc(sizeof(char) * (ft_strlen(full_str) - i));
	if (rof == NULL)
		return (free(full_str), NULL);
	i++;
	j = 0;
	while (full_str[i])
		rof[j++] = full_str[i++];
	rof[j] = '\0';
	free(full_str);
	return (rof);
}

char	*get_next_line(int fd)
{
	static char	*full_str[4096];
	char		*line;

	if (fd < 0)
		return (NULL);
	full_str[fd] = ft_read_file(fd, full_str[fd]);
	if (!full_str[fd])
		return (NULL);
	line = ft_get_line(full_str[fd]);
	if (!line)
	{
		free(full_str[fd]);
		full_str[fd] = NULL;
		return (NULL);
	}
	full_str[fd] = ft_get_rof(full_str[fd]);
	return (line);
}
