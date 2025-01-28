/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:18:49 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:09:43 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	cmp_1;
	unsigned char	cmp_2;

	i = 0;
	while (i < n)
	{
		cmp_1 = (unsigned char) s1[i];
		cmp_2 = (unsigned char) s2[i];
		if (cmp_1 != cmp_2)
		{
			return (cmp_1 - cmp_2);
		}
		if (cmp_1 == '\0')
			break ;
		i++;
	}
	return (0);
}
