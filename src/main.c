/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:54:48 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 18:10:17 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_last_signal;

void	minishell_non_int(char **env, char *av2)
{
	t_data	*data;

	data = init_data_struct(env);
	if (process_user_input_non_int(data, av2) == true)
	{
		if (data->cmds->cmd_n == 1 && is_a_builtin(data->cmds))
			redirection_and_execution_builtin(data->cmds);
		else
			shell_execution(data->cmds);
	}
	free_data_struct(data, false);
}

void	minishell(char **env)
{
	t_data	*data;

	data = init_data_struct(env);
	while (1)
	{
		signal(SIGINT, standard_behavior);
		signal(SIGQUIT, SIG_IGN);
		if (process_user_input(data) == true)
		{
			if (data->cmds->cmd_n == 1 && is_a_builtin(data->cmds))
				redirection_and_execution_builtin(data->cmds);
			else
				shell_execution(data->cmds);
		}
		free_data_struct(data, true);
	}
	free_data_struct(data, false);
}

int	main(int ac, char **av, char **env)
{
	g_last_signal = 0;
	if (ac == 1)
		minishell(env);
	if (ac > 1)
	{
		if (command_option(av[1]) == true)
		{
			if (av[2] != NULL)
				minishell_non_int(env, av[2]);
			else
				ft_putstr_fd(ERROR_6, 2);
		}
	}
	return (g_last_signal);
}
