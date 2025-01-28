/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:05:00 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/19 22:41:49 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_spaces(char **input, int *index, int new_spaces)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_calloc(1, ft_strlen(*input) + 2);
	while ((*input)[j])
	{
		if ((new_spaces == 1 && j == (*index))
			|| (new_spaces == 2 && j == (*index + 1)))
		{
			temp[i] = 31;
			i++;
		}
		temp[i] = (*input)[j];
		i++;
		j++;
	}
	free(*input);
	*input = ft_strdup(temp);
	free(temp);
}

static	void	token_quote(char *input, int *i, char c)
{
	int	j;

	j = *i;
	if (input[j + 1])
		j++;
	while (input[j] && input[j] != c)
		j++;
	if (input[j] == '\0')
		j--;
	*i = j;
}

static	void	token_no_quote(char **input, int *i)
{
	int	spaces_to_add;

	if ((*input)[*i] == ' ')
	{
		(*input)[*i] = 31;
		return ;
	}
	spaces_to_add = check_sep_spacing(*input, *i);
	if (spaces_to_add == 2)
		add_spaces(input, i, spaces_to_add);
	spaces_to_add = check_sep_spacing(*input, *i);
	if (spaces_to_add == 1)
		add_spaces(input, i, spaces_to_add);
}

char	**split_tokens(char **input)
{
	int		i;
	int		q_status;

	i = 0;
	while ((*input)[i])
	{
		q_status = set_status((*input)[i]);
		if (q_status == NONE)
			token_no_quote(input, &i);
		else if (q_status == S_QUOTE || q_status == D_QUOTE)
			token_quote(*input, &i, (*input)[i]);
		i++;
	}
	return (ft_split(*input, 31));
}
