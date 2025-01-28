/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_parse_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:09:02 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/19 22:46:40 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	char	**build_arg_array(t_tokens *tokens, int start, int end)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_calloc(end - start + 2, sizeof(char *));
	while (tokens != NULL && tokens->i <= end)
	{
		if (tokens->processed == false && tokens->word != NULL)
		{
			args[i] = ft_strdup(tokens->word);
			i++;
		}
		tokens = tokens->next;
	}
	return (args);
}

char	**parse_cmd_args(t_tokens *tokens, int start, int end)
{
	t_tokens	*temp_1;
	char		**args;

	temp_1 = tokens;
	while (temp_1 != NULL && temp_1->i != start)
		temp_1 = temp_1->next;
	if (temp_1 == NULL)
		return (NULL);
	args = build_arg_array(temp_1, start, end);
	return (args);
}
