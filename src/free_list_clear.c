/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:05:51 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/19 22:36:44 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_lstclear(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	current = tokens;
	while (current->i != 0)
		current = current->prev;
	while (current != NULL)
	{
		next = current->next;
		if (current->word)
			free(current->word);
		if (current->sep)
			free(current->sep);
		free(current);
		current = next;
	}
}
