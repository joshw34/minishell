/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_processing_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:07:24 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/10 14:48:07 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	waiting_sons_processes(t_cmd *command_array, int *status)
{
	while (command_array)
	{
		while (waitpid(command_array->pid, status, 0) == -1)
			;
		command_array = command_array->next;
	}
	g_last_signal = WEXITSTATUS(*status);
}
