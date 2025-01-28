/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:13:18 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/10 15:17:52 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_remove_quotes(t_cmd *cmd)
{
	int		i;
	int		last;
	char	*temp;

	i = 0;
	if (!cmd->cmd)
		return ;
	while (cmd->args[i])
	{
		last = ft_strlen(cmd->args[i]) - 1;
		if ((cmd->args[i][0] == 34 && cmd->args[i][last] == 34)
			|| (cmd->args[i][0] == 39 && cmd->args[i][last] == 39))
		{
			temp = ft_strdup(cmd->args[i] + 1);
			temp[last - 1] = '\0';
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

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
			expand_path(tokens);
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
