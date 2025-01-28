/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:19:48 by jwhitley          #+#    #+#             */
/*   Updated: 2024/05/09 11:21:17 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_type(va_list args, char *str, size_t *char_count)
{
	if (*str == 'c')
		ft_print_char(va_arg(args, int), char_count);
	else if (*str == 's')
		ft_print_str(va_arg(args, char *), char_count);
	else if (*str == 'p')
		ft_print_ptr(va_arg(args, void *), char_count);
	else if (*str == 'd' || *str == 'i')
		ft_print_int(va_arg(args, int), char_count);
	else if (*str == 'u')
		ft_print_uint(va_arg(args, unsigned int), char_count);
	else if (*str == 'x')
		ft_print_hex(va_arg(args, unsigned int), char_count, HEX_LOW);
	else if (*str == 'X')
		ft_print_hex(va_arg(args, unsigned int), char_count, HEX_UPP);
	else if (*str == '%')
		ft_print_char(*str, char_count);
}

int	ft_printf(const char *str, ...)
{
	size_t	char_count;

	char_count = 0;
	va_list(args);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *str + 1)
		{
			str++;
			ft_format_type(args, (char *)str, &char_count);
		}
		else
			ft_print_char(*str, &char_count);
		str++;
	}
	va_end(args);
	return (char_count);
}
