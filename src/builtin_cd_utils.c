/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:33:13 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 13:24:17 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	go_home_sysenv(t_data *data)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	if (getenv("HOME") != NULL && access(getenv("HOME"), F_OK) == 0)
	{
		temp_new_dir = ft_strdup(getenv("HOME"));
		temp_pwd = ft_strjoin("PWD=", temp_new_dir);
		temp_oldpwd = ft_strjoin("OLDPWD=", get_var(data->env, "PWD"));
		export_env(data, temp_pwd);
		export_env(data, temp_oldpwd);
		chdir(temp_new_dir);
		multi_free(3, temp_new_dir, temp_pwd, temp_oldpwd);
		return ;
	}
	ft_putstr_fd("Error: Cannot access system HOME variable\n", 2);
	g_last_signal = 1;
}

void	go_home_expand_sysenv(t_data *data, char *new_dir)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	temp_new_dir = NULL;
	if (getenv("HOME") != NULL)
	{
		temp_new_dir = ft_strjoin(getenv("HOME"), new_dir + 1);
		if (access(temp_new_dir, F_OK) == 0)
		{
			chdir(temp_new_dir);
			free(temp_new_dir);
			temp_new_dir = get_realpwd();
			temp_pwd = ft_strjoin("PWD=", temp_new_dir);
			temp_oldpwd = ft_strjoin("OLDPWD=", get_var(data->env, "PWD"));
			export_env(data, temp_pwd);
			export_env(data, temp_oldpwd);
			multi_free(3, temp_new_dir, temp_pwd, temp_oldpwd);
			return ;
		}
	}
	ft_putstr_fd("Error: Cannot access system HOME variable\n", 2);
	free(temp_new_dir);
	g_last_signal = 1;
	return ;
}
