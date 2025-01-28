/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:15:43 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:11:03 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	void	free_mem(char **new, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(new[i]);
		i++;
	}
	free(new);
}

static	int	alloc_st(char const *s, char **n, size_t j, size_t c)
{
	n[j] = malloc((c + 1) * sizeof(char));
	if (n[j] == NULL)
	{
		free_mem(n, j);
		return (-1);
	}
	ft_strlcpy(n[j], s, c + 1);
	return (1);
}

static	int	create_strings(char const *str, char **new, char c)
{
	size_t	i;
	size_t	char_count;
	size_t	j;

	i = 0;
	char_count = 0;
	j = 0;
	while (str[i])
	{
		char_count = 0;
		while (str[i + char_count] && str[i + char_count] != c)
			char_count++;
		if (char_count > 0)
		{
			if (alloc_st(str + i, new, j, char_count) == -1)
				return (-1);
			j++;
			i = i + char_count;
		}
		else
			i++;
	}
	new[j] = 0;
	return (0);
}

static	size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	word_count;

	word_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			word_count++;
		i++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**new;

	words = count_words(s, c);
	new = malloc((words + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	if (create_strings(s, new, c) == -1)
		return (NULL);
	return (new);
}
