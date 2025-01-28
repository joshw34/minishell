/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:20:30 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/23 17:23:58 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirection_file_checking_and_selection(t_cmd **command_array)
{
	t_redir	*redirection;
	int		fd;

	fd = 0;
	redirection = (*command_array)->redir;
	while (redirection)
	{
		if (redirection->direction == IN)
			close((*command_array)->fd_in);
		else
			close((*command_array)->fd_out);
		fd = open_file(redirection);
		if (fd == -1)
		{
			perror("open file");
			exit(1);
		}
		if (redirection->direction == IN)
			(*command_array)->fd_in = fd;
		else
			(*command_array)->fd_out = fd;
		redirection = redirection->next;
	}
}

void	redirecting_std_input(t_cmd *command_array)
{
	dup2(command_array->fd_in, 0);
	if (command_array->fd_in != 0)
		close(command_array->fd_in);
}

void	redirecting_std_output(t_cmd *command_array)
{
	dup2(command_array->fd_out, 1);
	if (command_array->fd_out != 1)
		close(command_array->fd_out);
}

static	void	redirecting_output_input(t_cmd *command_array)
{
	redirecting_std_input(command_array);
	redirecting_std_output(command_array);
}

void	redirection_and_execution(t_cmd *command_array)
{
	if (command_array->next)
		close(command_array->pipe_fd[0]);
	if (command_array->redir)
		redirection_file_checking_and_selection(&command_array);
	redirecting_output_input(command_array);
	if (execute_command(command_array) == -1)
		exit(127);
	exit(0);
}
