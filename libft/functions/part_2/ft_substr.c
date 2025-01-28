/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:15 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:11:35 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	new_len;
	char	*result;

	s_len = ft_strlen(s);
	if (start > ft_strlen(s) || ft_strlen(s) == 0)
		return (ft_strdup(""));
	new_len = s_len - start;
	if (new_len > len)
		new_len = len;
	result = malloc((new_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, new_len + 1);
	return (result);
}
