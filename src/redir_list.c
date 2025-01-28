/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:11:52 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/21 17:54:28 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	set_redir_type(t_redir *new, char *sep)
{
	if (sep[0] == '>')
	{
		new->direction = OUT;
		if (sep[1] == '\0')
			new->mode = OUTFILE;
		else
			new->mode = APPEND;
	}
	else if (sep[0] == '<')
	{
		new->direction = IN;
		if (sep[1] == '\0')
			new->mode = INFILE;
		else
			new->mode = HEREDOC;
	}
}

void	redir_list_clear(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current != NULL)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
}

static	void	redir_add(t_redir *input, t_tokens *tokens)
{
	t_redir	*new;
	t_redir	*temp_input;

	new = ft_calloc(1, sizeof(t_redir));
	temp_input = input;
	while (temp_input->next != NULL)
		temp_input = temp_input->next;
	temp_input->next = new;
	set_redir_type(new, tokens->sep);
	new->filename = ft_strdup(tokens->next->word);
	new->next = NULL;
	new->fd = -1;
	tokens->processed = true;
	tokens->next->processed = true;
}

static	t_redir	*redir_new(t_tokens *tokens)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	set_redir_type(new, tokens->sep);
	new->filename = ft_strdup(tokens->next->word);
	new->next = NULL;
	new->fd = -1;
	tokens->processed = true;
	tokens->next->processed = true;
	return (new);
}

t_redir	*get_redir_list(t_tokens *tokens, int start, int end)
{
	t_redir		*input;
	t_tokens	*temp_tok;

	input = NULL;
	temp_tok = tokens;
	while (temp_tok != NULL && temp_tok->i != start)
		temp_tok = temp_tok->next;
	while (temp_tok != NULL && temp_tok->i != end)
	{
		if (temp_tok->sep != NULL)
		{
			if (temp_tok->sep[0] != '|')
			{
				if (input == NULL)
					input = redir_new(temp_tok);
				else
					redir_add(input, temp_tok);
			}
		}
		temp_tok = temp_tok->next;
	}
	return (input);
}
