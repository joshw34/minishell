/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:29:27 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 13:45:24 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expand_tilde(t_tokens *tok)
{
	char	*temp1;
	char	*temp2;

	if (tok->word[0] != '~')
		return ;
	if (get_var(tok->data->env, "HOME") != NULL)
		temp1 = get_var(tok->data->env, "HOME");
	else if (getenv("HOME") != NULL)
		temp1 = getenv("HOME");
	else
	{
		tok->start = tok->start + 1;
		return ;
	}
	if (tok->word[0] == '~')
	{
		temp2 = ft_strdup(tok->word + 1);
		free(tok->word);
		tok->word = ft_strjoin(temp1, temp2);
		free(temp2);
		tok->start = ft_strlen(temp1);
		tok->end = tok->end + ft_strlen(temp1) - 1;
	}
	else
		return ;
}

void	remove_tok_quotes(t_tokens *tok)
{
	int		new_size;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new_size = ft_strlen(tok->word) - 2;
	new = ft_calloc(new_size + 1, sizeof(char));
	while (tok->word[i])
	{
		if (i == tok->start || i == tok->end)
			i++;
		else
		{
			new[j] = tok->word[i];
			j++;
			i++;
		}
	}
	free(tok->word);
	tok->word = ft_strdup(new);
	free(new);
	tok->end = tok->end - 2;
}

void	find_section_end(t_tokens *tok)
{
	int		i;
	char	c;

	i = tok->start;
	if (tok->q_status == NONE)
	{
		while (tok->word[i] && tok->word[i] != 34 && tok->word[i] != 39)
			i++;
		i--;
	}
	else if ((tok->q_status == S_QUOTE || tok->q_status == D_QUOTE)
		&& tok->word[i + 1])
	{
		c = tok->word[i];
		i++;
		while (tok->word[i] != c)
			i++;
	}
	if (tok->word[i] == '\0')
		tok->end = i - 1;
	else
		tok->end = i;
}
