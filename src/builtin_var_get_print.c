/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var_get_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:32 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/21 17:49:39 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '=') != 0)
			printf("%s\n", data->env[i]);
		i++;
	}
	g_last_signal = 0;
}

char	*get_var(char **env, char *var)
{
	char	*ret;

	ret = find_var(env, var);
	if (!ret)
		return (NULL);
	if (ft_strchr(ret, '=') == 0)
		return (NULL);
	return (ft_strchr(ret, '=') + 1);
}
