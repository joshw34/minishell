/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file_opening.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:03:53 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/23 17:24:56 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	open_infile(t_redir *redirection)
{
	int	fd;

	if (redirection->mode == 1)
	{
		fd = open(HERE_DOC_PATH, O_RDONLY, 0777);
	}
	else
		fd = open((redirection)->filename, O_RDONLY, 0777);
	return (fd);
}

static	int	open_outfile(t_redir *redirection)
{
	int	fd;

	if ((redirection)->mode == APPEND)
		fd = open((redirection)->filename, O_WRONLY | O_APPEND);
	else
	{
		fd = open((redirection)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	return (fd);
}

int	open_file(t_redir *redirection)
{
	int	fd;

	if ((redirection)->direction)
		fd = open_outfile(redirection);
	else
		fd = open_infile(redirection);
	return (fd);
}
