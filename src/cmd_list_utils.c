/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:13:18 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/19 22:45:42 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	char	*join_cmd(t_tokens *tokens, int end)
{
	char	*ret;
	char	*temp_word;
	char	*temp_join;

	ret = NULL;
	while (tokens != NULL && tokens->i <= end)
	{
		if (tokens->processed == false && tokens->word != NULL)
		{
			temp_word = ft_strjoin(tokens->word, " ");
			if (ret == NULL)
				ret = ft_strdup(temp_word);
			else
			{
				temp_join = ft_strjoin(ret, temp_word);
				free(ret);
				ret = ft_strdup(temp_join);
				free(temp_join);
			}
			free(temp_word);
		}
		tokens = tokens->next;
	}
	return (ret);
}

char	*parse_cmd(t_tokens *tokens, int start, int end)
{
	t_tokens	*temp_1;
	char		*cmd;

	temp_1 = tokens;
	while (temp_1 != NULL && temp_1->i != start)
		temp_1 = temp_1->next;
	if (temp_1 == NULL)
		return (NULL);
	cmd = join_cmd(temp_1, end);
	return (cmd);
}

int	cmd_find_end(int start, t_tokens *tokens)
{
	int			ret;
	t_tokens	*temp;

	ret = 0;
	temp = tokens;
	while (temp != NULL && temp->i != start)
		temp = temp->next;
	while (temp != NULL)
	{
		ret = temp->i;
		temp = temp->next;
		if (temp != NULL && temp->sep != NULL && temp->sep[0] == '|')
			break ;
	}
	if (temp == NULL)
		return (ret);
	else
		return (ret + 1);
}

int	cmd_count(t_tokens *tokens)
{
	int			n;
	t_tokens	*temp;

	n = 1;
	temp = tokens;
	while (temp != NULL)
	{
		if (temp->sep != NULL && temp->sep[0] == '|'
			&& temp->next != NULL)
			n++;
		temp = temp->next;
	}
	return (n);
}
