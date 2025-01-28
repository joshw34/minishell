/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:13:09 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:10:32 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	char	*minimum_int(int n)
{
	char	*result;
	int		i;

	i = 9;
	result = malloc(12 * sizeof(char));
	result[0] = '-';
	result[10] = '8';
	n = (n / 10) * -1;
	while (n > 0)
	{
		result[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	result [11] = '\0';
	return (result);
}

static	char	*fill_array(char *temp, int n)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(temp) - 1;
	if (n < 0)
		result = malloc((ft_strlen(temp) + 2) * sizeof(char));
	else
		result = malloc((ft_strlen(temp) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n < 0)
	{
		result[i] = '-';
		i++;
	}
	while (j >= 0)
	{
		result[i] = temp[j];
		i++;
		j--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	temp[12];
	int		num;
	int		i;

	i = 0;
	num = n;
	if (n == -2147483648)
		return (minimum_int(n));
	if (n < 0)
		num = num * -1;
	if (n == 0)
	{
		temp[i] = '0';
		i++;
	}
	while (num > 0)
	{
		temp[i] = (num % 10) + 48;
		num = num / 10;
		i++;
	}
	temp[i] = '\0';
	return (fill_array(temp, n));
}
