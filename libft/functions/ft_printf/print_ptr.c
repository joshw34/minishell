/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:23:12 by jwhitley          #+#    #+#             */
/*   Updated: 2024/05/09 11:23:45 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_find_len_ptr(unsigned long num)
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

void	ft_print_hex_ptr(unsigned long num, size_t *char_count, char *hex_type)
{
	char	*rev;
	size_t	len;
	size_t	i;

	if (num <= 15)
	{
		ft_print_char(hex_type[num], char_count);
		return ;
	}
	len = ft_find_len_ptr(num);
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

void	ft_print_ptr(void *ptr, size_t *char_count)
{
	unsigned long	addr;

	addr = (unsigned long) ptr;
	if (addr == 0)
	{
		ft_print_str("(nil)", char_count);
		return ;
	}
	ft_print_str("0x", char_count);
	ft_print_hex_ptr(addr, char_count, HEX_LOW);
}
