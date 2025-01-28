/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:52:39 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 18:04:41 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	go_full_path(t_data *data, char *new_dir)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	if (access(new_dir, F_OK) == 0)
	{
		chdir(new_dir);
		temp_new_dir = get_realpwd();
		if (!temp_new_dir)
			printf("%s%s\n", ERROR_4, ERROR_4_2);
		temp_pwd = ft_strjoin("PWD=", temp_new_dir);
		temp_oldpwd = ft_strjoin("OLDPWD=", get_var(data->env, "PWD"));
		export_env(data, temp_pwd);
		export_env(data, temp_oldpwd);
		multi_free(3, temp_new_dir, temp_pwd, temp_oldpwd);
	}
	else
	{
		perror(new_dir);
		g_last_signal = 1;
	}
}

static	void	go_home_expand(t_data *data, char *new_dir)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	if (find_var(data->env, "HOME") == NULL)
		return (go_home_expand_sysenv(data, new_dir));
	temp_new_dir = ft_strjoin(get_var(data->env, "HOME"), new_dir + 1);
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
	ft_putstr_fd("Error: Invalid directory\n", 2);
	free(temp_new_dir);
	g_last_signal = 1;
	return ;
}

static	void	go_home(t_data *data)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	if (find_var(data->env, "HOME") == NULL)
		return (go_home_sysenv(data));
	if (access(get_var(data->env, "HOME"), F_OK) == 0)
	{
		temp_new_dir = ft_strdup(get_var(data->env, "HOME"));
		temp_pwd = ft_strjoin("PWD=", get_var(data->env, "HOME"));
		temp_oldpwd = ft_strjoin("OLDPWD=", get_var(data->env, "PWD"));
		export_env(data, temp_pwd);
		export_env(data, temp_oldpwd);
		chdir(temp_new_dir);
		multi_free(3, temp_new_dir, temp_pwd, temp_oldpwd);
		return ;
	}
	else
		ft_putstr_fd("Error: $HOME is not a valid directory/n", 2);
	g_last_signal = 1;
}

static	void	go_back(t_data *data)
{
	char	*temp_new_dir;
	char	*temp_pwd;
	char	*temp_oldpwd;

	if (get_var(data->env, "OLDPWD") == NULL)
		return (g_last_signal = 1,
			ft_putstr_fd("Error: OLDPWD is not set\n", 2));
	if (access(get_var(data->env, "OLDPWD"), F_OK) == 0)
	{
		temp_new_dir = ft_strdup(get_var(data->env, "OLDPWD"));
		temp_pwd = ft_strjoin("PWD=", get_var(data->env, "OLDPWD"));
		temp_oldpwd = ft_strjoin("OLDPWD=", get_var(data->env, "PWD"));
		export_env(data, temp_pwd);
		export_env(data, temp_oldpwd);
		chdir(temp_new_dir);
		multi_free(3, temp_new_dir, temp_pwd, temp_oldpwd);
		printf("%s\n", get_var(data->env, "PWD"));
		return ;
	}
	else
		g_last_signal = 1;
}

void	change_dir(t_cmd *cmd)
{
	char	*new_dir;

	new_dir = cmd->args[1];
	g_last_signal = 0;
	if (cmd->args[2])
		return (g_last_signal = 1, ft_putstr_fd(ERROR_7, 2));
	if (!new_dir && get_var(cmd->data->env, "HOME") == NULL)
		return (ft_putstr_fd("Error: HOME is not set\n", 2));
	if (!new_dir)
		return (go_home(cmd->data));
	if (ft_strncmp(new_dir, "~", 2) == 0)
		return (go_home(cmd->data));
	if (ft_strncmp(new_dir, "-", 2) == 0)
		return (go_back(cmd->data));
	if (new_dir[0] == '~' && new_dir[1] != '\0')
		return (go_home_expand(cmd->data, new_dir));
	else
		return (go_full_path(cmd->data, new_dir));
}
