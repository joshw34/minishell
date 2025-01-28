/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var_export_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:53:47 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/21 12:37:35 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_env_all_arg(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
		return ;
	while (cmd->args[i])
	{
		remove_var(cmd->data, cmd->args[i]);
		++i;
	}
}

void	export_env_all_arg(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
		print_ascii_sorted_env(cmd->data);
	while (cmd->args[i])
	{
		if (!export_env(cmd->data, cmd->args[i]))
			printf("minishell: export: %s : not a valid identifier\n",
				cmd->args[i]);
		++i;
	}
}

static bool	value_valid(char *new_var, int i)
{
	while (new_var[i])
	{
		if (ft_isprint(new_var[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	var_name_is_valid(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (true);
	return (false);
}

bool	var_is_valid(char *new_var)
{
	int	i;

	i = 0;
	if (ft_isalpha(new_var[i]) || new_var[i] == '_')
		i++;
	else
		return (false);
	while (var_name_is_valid(new_var[i]) == true)
		i++;
	if (new_var[i] == '\0')
		return (true);
	if (new_var[i] == '=' && new_var[i + 1] == '\0')
		return (true);
	if (new_var[i] == '=')
	{
		if (value_valid(new_var, i) == true)
			return (true);
		else
			return (false);
	}
	return (false);
}
