/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:14:55 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:08:39 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	cpy_backward(unsigned char *d, const unsigned char *s, size_t n)
{
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
}

void	cpy_forward(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	i = 0;
	if (dest + i == NULL && src + i == NULL)
		return (NULL);
	if (d < s)
		cpy_forward(d, s, n);
	else
		cpy_backward(d, s, n);
	return (dest);
}
