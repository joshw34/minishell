/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG_FUNCS.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:41:20 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/27 20:36:54 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	db_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%d\t%s\n", i, array[i]);
		i++;
	}
}

void	db_print_tokens(t_data *data)
{
	t_tokens	*temp;

	temp = data->tokens;
	while (temp != NULL)
	{
		printf("TOKEN: %d\n", temp->i);
		printf("Word: %s\n", temp->word);
		printf("Sep: %s\n", temp->sep);
		printf("Processed: %d\n", temp->processed);
		printf("\n");
		temp = temp->next;
	}
}

void	db_print_cmds(t_data *data)
{
	t_cmd	*temp;
	int		i;

	temp = data->cmds;
	i = 0;
	while (temp != NULL)
	{
		printf("\nCOMMAND #%d\n", i);
		printf("cmd_n = %d\n", temp->cmd_n);
		printf("Command: %s\n", temp->cmd);
		printf("fd_in: %d\nfd_out: %d\n", temp->fd_in, temp->fd_out);
		printf("located at: %p\n", temp);
		printf("Prev: %p\n", temp->prev);
		printf("Next: %p\n", temp->next);
		db_print_redir(temp->redir);
		temp = temp->next;
		i++;
	}
}

void	db_print_redir(t_redir *redir)
{
	printf("\nINPUT REDIRECTION:\n");
	if (redir == NULL)
		printf("No Redirection\n");
	else
	{
		while (redir != NULL)
		{
			printf("Filename: %s\n", redir->filename);
			printf("Direction (0 = in, 1 = out): %d\n", redir->direction);
			printf("Mode (0 = infile, 1 = heredoc, 2 = outfile, 3 = append): %d\n", redir->mode);
			redir = redir->next;
		}
	}
}
