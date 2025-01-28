/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:29:04 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/19 22:44:38 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_status(char c)
{
	if (c == 39)
		return (S_QUOTE);
	else if (c == 34)
		return (D_QUOTE);
	else
		return (NONE);
}

static	int	check_sep_spacing_2(char *input, int i)
{
	if (input[i + 1] != input[i])
	{
		if (input[i + 1] != '\0' && input[i + 1] != ' ' && input [i + 1] != 31)
			return (2);
		if (i != 0 && input[i - 1] != ' ' && input[i - 1] != 31
			&& input[i - 1] != input[i])
			return (1);
	}
	else if (input[i + 1] == input[i])
	{
		if (i != 0 && input[i - 1] == input[i])
			return (2);
		if (i != 0 && input[i - 1] != ' ' && input[i - 1] != 31)
			return (1);
	}
	return (0);
}

int	check_sep_spacing(char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] != '\0' && input[i + 1] != ' ' && input[i + 1] != 31)
			return (2);
		if (i != 0 && input[i - 1] != ' ' && input[i - 1] != 31)
			return (1);
	}
	if (input[i] == '>' || input[i] == '<')
		return (check_sep_spacing_2(input, i));
	return (0);
}

void	set_token_type(t_tokens *token)
{
	if (token->sep)
	{
		if (token->sep[0] == '|')
			token->type = PIPE;
		if (token->sep[0] == '>' && token->sep[1] == '>')
			token->type = APPEND;
		if (token->sep[0] == '>' && token->sep[1] == '\0')
			token->type = OUTFILE;
		if (token->sep[0] == '<' && token->sep[1] == '<')
			token->type = HEREDOC;
		if (token->sep[0] == '<' && token->sep[1] == '\0')
			token->type = INFILE;
	}
	else if (token->word)
	{
		if (token->prev && token->prev->sep && token->prev->sep[0] != '|')
			token->type = token->prev->type;
		else
			token->type = WORD;
	}
}

bool	is_a_separator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
