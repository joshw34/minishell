/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:17:04 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/09 14:57:31 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	new_len;
	char	*result;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	new_len = len_1 + len_2;
	result = malloc(sizeof(char) * (new_len + 1));
	if (result == NULL)
		return (NULL);
	ft_bzero(result, new_len + 1);
	ft_strlcpy(result, s1, new_len + 1);
	ft_strlcat(result, s2, new_len + 1);
	return (result);
}
