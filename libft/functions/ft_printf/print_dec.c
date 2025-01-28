/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:22:01 by jwhitley          #+#    #+#             */
/*   Updated: 2024/05/09 11:22:15 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*fill_uint_array(char *temp)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(temp) - 1;
	result = malloc((ft_strlen(temp) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (j >= 0)
	{
		result[i] = temp[j];
		i++;
		j--;
	}
	result[i] = '\0';
	return (result);
}

static	char	*ft_uitoa(unsigned int n)
{
	char	temp[11];
	int		i;

	i = 0;
	if (n == 0)
	{
		temp[i] = '0';
		i++;
	}
	while (n > 0)
	{
		temp[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	temp[i] = '\0';
	return (fill_uint_array(temp));
}

void	ft_print_uint(unsigned int num, size_t *char_count)
{
	char	*result;

	result = ft_uitoa(num);
	ft_print_str(result, char_count);
	free(result);
}

void	ft_print_int(int num, size_t *char_count)
{
	char	*result;

	result = ft_itoa(num);
	ft_print_str(result, char_count);
	free(result);
}
