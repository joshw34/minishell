/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc_insert_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:57:33 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/20 17:40:00 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	hd_var_insert_end(t_tokens *temp, char *new, int *i, int *j)
{
	if (temp->word[temp->end] != '\0' && temp->word[temp->end + 1] != '\0')
	{
		*i = temp->end + 1;
		while (temp->word[*i])
		{
			new[*j] = temp->word[*i];
			(*i)++;
			(*j)++;
		}
	}
}

static	void	hd_var_insert_mid(t_tokens *temp, char *new_var,
				char *new, int *j)
{
	int	i;

	i = 0;
	if (new_var != NULL)
	{
		while (new_var[i])
		{
			new[*j] = new_var[i];
			(*j)++;
			i++;
		}
	}
	temp->start = *j;
}

int	hd_var_insert(t_tokens *temp, char *new_var, char *var_name)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new = ft_calloc(ft_strlen(temp->word) + ft_strlen(new_var) + 1,
			sizeof(char));
	while (i < temp->start)
	{
		new[j] = temp->word[i];
		i++;
		j++;
	}
	hd_var_insert_mid(temp, new_var, new, &j);
	if (new_var == NULL)
		temp->start = j;
	hd_var_insert_end(temp, new, &i, &j);
	free(temp->word);
	temp->word = ft_strdup(new);
	multi_free(2, new, var_name);
	return (temp->start);
}
