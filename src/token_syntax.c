/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:01:16 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/28 13:32:00 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	find_closing_quote(char *str, int *i, char c, int *q_total)
{
	if (str[*i + 1])
		(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == '\0')
	{
		(*i)--;
		return ;
	}
	else
		(*q_total)++;
}

static	bool	check_quotes(char *str)
{
	int		i;
	int		q_total;
	char	c;

	i = 0;
	q_total = 0;
	if (ft_strchr(str, 34) == 0 && ft_strchr(str, 39) == 0)
		return (true);
	while (str[i])
	{
		while (str[i] && str[i] != 34 && str[i] != 39)
			i++;
		if (str[i] == 34 || str[i] == 39)
			q_total++;
		else
			break ;
		c = str[i];
		find_closing_quote(str, &i, c, &q_total);
		i++;
	}
	if (q_total % 2 == 0)
		return (true);
	else
		return (printf("%s %c\n", ERROR_1, c), false);
}

bool	sep_syntax(t_tokens *token)
{
	if (token->sep[0] == '|' && token->i == 0)
		return (printf("%s '%s'\n", ERROR_3, token->next->sep), false);
	if (!token->next)
		return (printf("%s\n", ERROR_2), false);
	if (token->next->sep && token->sep[0] != '|')
		return (printf("%s '%s'\n", ERROR_3, token->next->sep), false);
	return (true);
}

bool	word_syntax(char *str)
{
	if (check_quotes(str) == false)
		return (false);
	return (true);
}
