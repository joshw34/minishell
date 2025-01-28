/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:03:53 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 13:45:45 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	rebuild_str(t_tokens *tok, char *temp1, char *temp2)
{
	if (!temp1 && !temp2)
		tok->word = ft_strdup("");
	else if (temp1 && temp2)
	{
		tok->word = ft_strjoin(temp1, temp2);
		multi_free(2, temp1, temp2);
	}
	else if (temp1)
	{
		tok->word = ft_strdup(temp1);
		free(temp1);
	}
	else if (temp2)
	{
		tok->word = ft_strdup(temp2);
		free(temp2);
	}
}

static	int	remove_section(t_tokens *tok, int var_name_len)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	if (tok->start != 0)
	{
		temp1 = ft_strdup(tok->word);
		temp1[tok->start] = '\0';
	}
	if (tok->word[tok->start + var_name_len + 1] != '\0')
		temp2 = ft_strdup(tok->word + tok->start + var_name_len + 1);
	free(tok->word);
	rebuild_str(tok, temp1, temp2);
	tok->end = tok->end - (var_name_len + 1);
	return (tok->start);
}

static	char	*get_end_section(t_tokens *tok, char *first_part,
	int var_name_len)
{
	char	*ret;
	char	*temp;

	if (tok->word[tok->start + var_name_len + 1])
	{
		temp = ft_strdup(tok->word + tok->start + var_name_len + 1);
		ret = ft_strjoin(first_part, temp);
		multi_free(2, temp, first_part);
	}
	else
	{
		ret = ft_strdup(first_part);
		free(first_part);
	}
	return (ret);
}

static	int	insert_var(t_tokens *tok, char *new_var, int var_name_len)
{
	char	*temp1;
	char	*temp2;
	int		new_start;
	int		len_after_end;

	len_after_end = ft_strlen(tok->word + tok->end);
	if (tok->start == 0)
		temp1 = ft_strdup(new_var);
	else
	{
		temp2 = ft_strdup(tok->word);
		temp2[tok->start] = '\0';
		temp1 = ft_strjoin(temp2, new_var);
		free(temp2);
	}
	new_start = ft_strlen(temp1);
	temp2 = get_end_section(tok, temp1, var_name_len);
	free(tok->word);
	tok->word = ft_strdup(temp2);
	free(temp2);
	tok->start = new_start;
	tok->end = ft_strlen(tok->word) - len_after_end;
	return (tok->start);
}

int	token_str_join(t_tokens *tok, char *new_var, int var_name_len,
	char *var_name)
{
	char	*exit_code;

	if (var_name_len == 1 && var_name[0] == '?')
	{
		exit_code = ft_itoa(g_last_signal);
		insert_var(tok, exit_code, ft_strlen(exit_code));
		free(exit_code);
		return (tok->start);
	}
	if (!new_var)
		return (remove_section(tok, var_name_len));
	else
		return (insert_var(tok, new_var, var_name_len));
}
