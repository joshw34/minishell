/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:06:26 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/21 17:57:19 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_list_clear(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_array(current->args);
		if (current->redir)
			redir_list_clear(current->redir);
		free(current);
		current = next;
	}
}

static	void	cmd_trim_spaces(t_cmd *cmds)
{
	char	*temp;

	if (!cmds->cmd)
		return ;
	temp = ft_strtrim(cmds->cmd, " ");
	if (temp)
	{
		free(cmds->cmd);
		cmds->cmd = temp;
	}
}

static	void	cmdlist_add(t_cmd *cmds, t_data *data, int start, int end)
{
	t_cmd	*new;
	t_cmd	*temp_cmds;

	new = ft_calloc(1, sizeof(t_cmd));
	temp_cmds = cmds;
	while (temp_cmds->next != NULL)
		temp_cmds = temp_cmds->next;
	temp_cmds->next = new;
	new->redir = get_redir_list(data->tokens, start, end);
	new->cmd_n = temp_cmds->cmd_n;
	new->cmd = parse_cmd(data->tokens, start, end);
	new->args = parse_cmd_args(data->tokens, start, end);
	cmd_trim_spaces(new);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->data = data;
	new->env = data->env;
	new->prev = temp_cmds;
	new->next = NULL;
}

static	t_cmd	*cmdlist_new(t_data *data, int start, int end, int n_cmds)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	new->redir = get_redir_list(data->tokens, start, end);
	new->cmd_n = n_cmds;
	new->cmd = parse_cmd(data->tokens, start, end);
	if (new->cmd)
		new->args = parse_cmd_args(data->tokens, start, end);
	cmd_trim_spaces(new);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->data = data;
	new->env = data->env;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*get_cmds(t_data *data)
{
	t_cmd	*cmds;
	int		n_cmds;
	int		start;
	int		end;
	int		i;

	cmds = NULL;
	if (data->tokens == NULL || data->user_input == NULL)
		return (cmds);
	i = 0;
	n_cmds = cmd_count(data->tokens);
	start = 0;
	while (i < n_cmds)
	{
		end = cmd_find_end(start, data->tokens);
		if (cmds == NULL)
			cmds = cmdlist_new(data, start, end, n_cmds);
		else
			cmdlist_add(cmds, data, start, end);
		start = end;
		i++;
	}
	return (cmds);
}
