/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:33:39 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 17:31:08 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	is_only_digit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1] && cmd->args[1][i] && (cmd->args[1][i] == '-'
		|| cmd->args[1][i] == '+'))
		++i;
	while (cmd->args[1] && cmd->args[1][i])
	{
		if (!(cmd->args[1][i] <= '9' && cmd->args[1][i] >= '0'))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			free_data_struct(cmd->data, false);
			exit(2);
		}
		++i;
	}
	return (1);
}

void	exit_cmd(t_data *data)
{
	char	exit_code[2048];
	int		len;

	if (!data->cmds->next && !data->cmds->prev)
		printf("exit\n");
	if (!data->cmds->args[1])
	{
		free_data_struct(data, false);
		exit(g_last_signal);
	}
	if (data->cmds->args[1]
		&& is_only_digit(data->cmds) && !data->cmds->args[2])
	{
		len = ft_strlen(data->cmds->args[1]) + 1;
		ft_strlcpy(exit_code, data->cmds->args[1], len);
		free_data_struct(data, false);
		exit(ft_atoi(exit_code));
	}
	if (data->cmds->args[2])
	{
		printf("minishell : exit: too many arguments\n");
		g_last_signal = 1;
		return ;
	}
}
