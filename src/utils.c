/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:08:51 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 17:16:57 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	command_option(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	else
		return (ft_putstr_fd(ERROR_5, 2), false);
	while (str[i])
	{
		if (str[i] != 'c')
			return (ft_putstr_fd(ERROR_5, 2), false);
		i++;
	}
	return (true);
}

bool	is_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 7 && str[i] <= 13) && str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

char	*get_realpwd(void)
{
	char	*ret;

	ret = ft_calloc(1024, sizeof(char));
	getcwd(ret, 1024);
	return (ret);
}
