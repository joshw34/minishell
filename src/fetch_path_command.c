/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_path_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:08:41 by cngogang          #+#    #+#             */
/*   Updated: 2025/01/08 15:10:39 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	from_env_to_path_array(char ***path_array, char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			*path_array = ft_split(*env + 5, ':');
			break ;
		}
		env++;
	}
	if (!env)
		return (0);
	return (1);
}

char	**get_path_array(char **env, char *arg)
{
	char	**path_array;
	char	**anchor;
	char	*temp;
	char	*ptr;

	path_array = NULL;
	if (!from_env_to_path_array(&path_array, env))
		return (NULL);
	anchor = path_array;
	while (path_array && *path_array)
	{
		temp = *path_array;
		ptr = ft_strjoin("/", arg);
		*path_array = ft_strjoin(*path_array, ptr);
		free(ptr);
		free(temp);
		++path_array;
	}
	return (anchor);
}
