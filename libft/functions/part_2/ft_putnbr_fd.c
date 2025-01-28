/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:30 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:10:51 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	void	write_num(char *temp, int n, int fd)
{
	int	i;

	i = ft_strlen(temp) - 1;
	if (n < 0)
		write(fd, "-", 1);
	while (i >= 0)
	{
		write(fd, &temp[i], 1);
		i--;
	}
}

static	void	convert_num(int n, int fd)
{
	char	temp[12];
	size_t	i;
	size_t	num;

	i = 0;
	num = n;
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
	write_num(temp, n, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
		convert_num(n, fd);
}
