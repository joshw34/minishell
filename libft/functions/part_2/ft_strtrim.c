/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:19:58 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:11:30 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	size_t	check_char(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	count_backward(char const *s1, char const *set)
{
	int	i;
	int	count;

	i = ft_strlen(s1) - 1;
	count = 0;
	while (i >= 0)
	{
		if (check_char(s1[i], set) == 1)
			count++;
		else if (check_char(s1[i], set) == 0)
			return (count);
		i--;
	}
	return (count);
}

static	int	count_forward(char const *s1, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		if (check_char(s1[i], set) == 1)
			count++;
		else if (check_char(s1[i], set) == 0)
			return (count);
		i++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	new_size;
	char	*result;

	start = count_forward(s1, set);
	end = count_backward(s1, set);
	if (start >= ft_strlen(s1))
		new_size = 0;
	else if (start + end > ft_strlen(s1))
		new_size = 0;
	else
		new_size = ft_strlen(s1) - start - end;
	result = malloc((new_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (new_size > 0)
		ft_strlcpy(result, s1 + start, new_size + 1);
	else
		result[0] = '\0';
	return (result);
}
