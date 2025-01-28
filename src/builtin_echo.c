/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:33:47 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 11:27:35 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	echo_print(t_cmd *cmd, int i)
{
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
}

static int	only_n_after_minus(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	echo_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
	{
		printf("\n");
		g_last_signal = 0;
		return ;
	}
	while (cmd->args[i] && only_n_after_minus(cmd->args[i]) == 1)
		++i;
	echo_print(cmd, i);
	if (i <= 1)
		printf("\n");
	g_last_signal = 0;
}
