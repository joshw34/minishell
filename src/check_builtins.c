/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:33:25 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 11:39:37 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		print_pwd(cmd->data);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(cmd->data);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		print_env(cmd->data);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_cmd(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		change_dir(cmd);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_env_all_arg(cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_env_all_arg(cmd);
	else
		return (false);
	return (true);
}
