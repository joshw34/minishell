/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:19:39 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:09:57 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	size_t			s_len;
	char			*str;
	char			*result;

	str = (char *) s;
	i = 0;
	s_len = ft_strlen(str);
	result = NULL;
	if (c > 127)
		return ((char *) s);
	while (i <= s_len)
	{
		if (str[i] == c)
		{
			result = &str[i];
		}
		i++;
	}
	return (result);
}
