/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:22:28 by jwhitley          #+#    #+#             */
/*   Updated: 2024/05/09 11:23:00 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	size_t	ft_find_len(unsigned int num)
{
	size_t	i;

	i = 0;
	while (num > 0)
	{
		num /= 16;
		i++;
	}
	return (i);
}

void	ft_print_hex(unsigned int num, size_t *char_count, char *hex_type)
{
	char	*rev;
	size_t	len;
	size_t	i;

	if (num <= 15)
	{
		ft_print_char(hex_type[num], char_count);
		return ;
	}
	len = ft_find_len(num);
	i = len - 1;
	rev = ft_calloc(len + 1, sizeof(char));
	if (rev == NULL)
		return ;
	while (num > 0)
	{
		rev[i] = hex_type[num % 16];
		num /= 16;
		i--;
	}
	ft_print_str(rev, char_count);
	free(rev);
}
