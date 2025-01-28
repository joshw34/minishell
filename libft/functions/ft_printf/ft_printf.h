/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:21:42 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:43:19 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../../libft.h"

# define HEX_LOW "0123456789abcdef"
# define HEX_UPP "0123456789ABCDEF"

int		ft_printf(const char *str, ...);
void	ft_format_type(va_list args, char *str, size_t *char_count);
void	ft_print_char(char c, size_t *char_count);
void	ft_print_str(char *str, size_t *char_count);
void	ft_print_ptr(void *ptr, size_t *char_count);
void	ft_print_hex(unsigned int num, size_t *char_count, char *hex_type);
void	ft_print_int(int num, size_t *char_count);
void	ft_print_uint(unsigned int num, size_t *char_count);

#endif
