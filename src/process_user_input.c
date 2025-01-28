/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:26:40 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/28 13:31:06 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	bool	get_tokens(t_data *data)
{
	char	**split;

	split = split_tokens(&data->user_input);
	if (!split)
		return (ft_putstr_fd("Error: failed to split input", 2), false);
	if (token_list(data, split) == false)
		return (ft_putstr_fd("Error: failed to create token list", 2), false);
	if (check_and_expand_tokens(data->tokens) == false)
		return (false);
	return (true);
}

bool	process_user_input_non_int(t_data *data, char *av2)
{
	if (!data)
		return (NULL);
	data->user_input = ft_strdup(av2);
	if (valid_input(data->user_input) == false)
		return (false);
	if (get_tokens(data) == false)
		return (false);
	data->cmds = get_cmds(data);
	if (!data->cmds)
		return (false);
	return (true);
}

bool	process_user_input(t_data *data)
{
	if (!data)
		return (NULL);
	data->user_input = get_input(data);
	if (valid_input(data->user_input) == false)
		return (false);
	if (get_tokens(data) == false)
		return (false);
	data->cmds = get_cmds(data);
	if (!data->cmds)
		return (false);
	return (true);
}
