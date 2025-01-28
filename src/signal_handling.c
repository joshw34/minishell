/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:03:38 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/23 17:25:39 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	standard_behavior(int sigint)
{
	if (sigint == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_signal = 130;
	}
}

void	here_doc_open_behavior(int sig)
{
	if (sig == SIGINT)
	{
		unlink(HERE_DOC_PATH);
		(void)sig;
		exit (1);
	}
}
