/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:36:02 by yukoc             #+#    #+#             */
/*   Updated: 2025/03/21 13:01:50 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

unsigned int	ft_word_counter(const char *s, char c)
{
	unsigned int	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s)
			{
				s++;
			}
			word_count++;
		}
	}
	return (word_count);
}

static unsigned int	ft_charlen(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**words;
	unsigned int	i;
	unsigned int	a;

	words = (char **)malloc((ft_word_counter(s, c) + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	a = -1;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words[++a] = (char *)malloc((ft_charlen(s, c) + 1) * sizeof(char));
			if (words[a] == NULL)
				return (ft_free_all(words));
			i = 0;
			while (*s && *s != c)
				words[a][i++] = *s++;
			words[a][i] = '\0';
		}
	}
	words[++a] = NULL;
	return (words);
}
