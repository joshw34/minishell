/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:40:04 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/23 18:13:46 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_error_finding_command(t_cmd *command_array)
{
	if (access(command_array->args[0], F_OK != 0))
	{
		ft_putstr_fd(command_array->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else if (access(command_array->args[0], X_OK) != 0)
	{
		ft_putstr_fd(command_array->args[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_last_signal = 126;
	}
}

int	execute_command(t_cmd *command_array)
{
	char	**fullpath;
	char	**anchor;

	if (!command_array->cmd)
		return (-1);
	if (access(command_array->args[0], X_OK) == 0)
		execve(command_array->args[0], command_array->args, command_array->env);
	if (redirection_and_execution_builtin(command_array))
		return (0);
	fullpath = get_path_array(command_array->env, (command_array->args)[0]);
	if (!fullpath)
		return (print_error_finding_command(command_array), -1);
	anchor = fullpath;
	while (*fullpath)
	{
		if (execve(*fullpath, command_array->args, command_array->env) == -1)
			++fullpath;
	}
	print_error_finding_command(command_array);
	free_array(anchor);
	return (-1);
}

void	fork_redirection_and_execution(t_cmd *command_array)
{
	command_array->pid = fork();
	if (!command_array->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		redirection_and_execution(command_array);
	}
	signal(SIGINT, SIG_IGN);
}

void	processing_commands(t_cmd *command_array)
{
	while (command_array)
	{
		if (command_array->prev)
		{
			command_array->fd_in = command_array->prev->pipe_fd[0];
			if (command_array->prev->fd_in)
				close(command_array->prev->fd_in);
		}
		if (command_array->next)
		{
			if (pipe(command_array->pipe_fd) == -1)
				perror("pipe");
			command_array->fd_out = command_array->pipe_fd[1];
		}
		fork_redirection_and_execution(command_array);
		if (command_array->next)
			close(command_array->pipe_fd[1]);
		else if (!command_array->next && command_array->fd_in)
			close(command_array->fd_in);
		command_array = command_array->next;
	}
}

void	shell_execution(t_cmd *command_array)
{
	int	status;

	processing_commands(command_array);
	waiting_sons_processes(command_array, &status);
}
