/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:19 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 16:25:34 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	valid_input(char *input)
{
	if (!input || input[0] == '\0' || is_whitespace(input) == true)
		return (false);
	return (true);
}

static	char	*get_prompt(void)
{
	char	*user;
	char	*dir;
	char	*prompt;
	char	*pwd;

	if (getenv("USER") == NULL)
		user = ft_strdup("");
	else
		user = ft_strjoin(getenv("USER"), "@");
	pwd = get_realpwd();
	if (pwd[0] == '\0')
		return (user);
	dir = ft_strjoin(pwd, " $ ");
	free(pwd);
	prompt = ft_strjoin(user, dir);
	multi_free(2, user, dir);
	return (prompt);
}

char	*get_input(t_data *data)
{
	char	*ret;
	char	*prompt;

	prompt = get_prompt();
	ret = readline(prompt);
	if (!ret)
	{
		printf("exit\n");
		free(prompt);
		free_data_struct(data, false);
		g_last_signal = 127;
		exit(0);
	}
	free(prompt);
	add_history(ret);
	return (ret);
}
