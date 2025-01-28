/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:59:42 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 17:30:02 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	process_var(t_tokens *tok)
{
	int		i;
	int		j;
	char	*temp;

	j = 1;
	i = tok->start + 1;
	temp = ft_calloc(ft_strlen(tok->word) + 1, sizeof(char));
	temp[0] = tok->word[i];
	i++;
	while (i <= tok->end && tok->word[i] && (ft_isalnum(tok->word[i]) == 1
			|| tok->word[i] == '_'))
	{
		if (temp[0] == '?' || (temp[0] >= 48 && temp[0] <= 57))
			break ;
		temp[j] = tok->word[i];
		i++;
		j++;
	}
	if (!temp[0])
		return (i);
	i = token_str_join(tok, get_var(tok->data->env, temp),
			ft_strlen(temp), temp);
	free(temp);
	return (i);
}

void	expand_tok_var(t_tokens *tok)
{
	int	i;

	i = tok->start;
	while (i < tok->end)
	{
		if (tok->word[i] == '$')
		{
			if (tok->word[i + 1] && (ft_isalnum(tok->word[i + 1]) == 1
					|| tok->word[i + 1] == '_' || tok->word[i + 1] == '?'))
			{
				tok->start = i;
				i = process_var(tok);
				continue ;
			}
		}
		i++;
	}
}

static	void	expand_token_section(t_tokens *tok)
{
	if (tok->q_status == S_QUOTE)
		remove_tok_quotes(tok);
	if (tok->q_status == D_QUOTE)
	{
		remove_tok_quotes(tok);
		if (tok->type == WORD)
			expand_tok_var(tok);
	}
	if (tok->q_status == NONE)
	{
		if (tok->type == WORD)
		{
			expand_tilde(tok);
			expand_tok_var(tok);
		}
	}
}

static	bool	process_word(t_tokens *tok)
{
	int	i;

	i = 0;
	while (tok->word[i])
	{
		tok->q_status = set_status(tok->word[i]);
		tok->start = i;
		find_section_end(tok);
		expand_token_section(tok);
		i = tok->end;
		if (i < 0 || tok->word[i] == '\0')
			break ;
		i++;
	}
	return (true);
}

bool	check_and_expand_tokens(t_tokens *token)
{
	t_tokens	*temp;

	temp = token;
	while (temp != NULL)
	{
		if (temp->word)
		{
			if (word_syntax(temp->word) == false)
				return (false);
			if (process_word(temp) == false)
				return (false);
			if (temp->type == HEREDOC && process_heredoc(temp->data, temp->word)
				== false)
				return (false);
		}
		else if (temp->sep)
		{
			if (sep_syntax(temp) == false)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}
