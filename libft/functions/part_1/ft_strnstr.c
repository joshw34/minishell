/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:19:15 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:09:51 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	if (len_little > len)
		return (NULL);
	while (big[i] && i <= (len - len_little))
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(big + i, little, len_little) == 0)
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
