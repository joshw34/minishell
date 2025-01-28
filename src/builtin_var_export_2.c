/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var_export_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:33:10 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/23 17:23:02 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	is_ascii_lesser(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		++i;
	if (s1[i] <= s2[i])
		return (1);
	else
		return (0);
}

static char	**dup_2d_array(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_calloc(i + 1, sizeof(char *));
	if (!new_array)
		return (false);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_array);
}

static	char	**sort_2d_array_by_ascii(char **array)
{
	int		i;
	int		j;
	char	*temp;
	char	**env_copy;

	i = 0;
	env_copy = dup_2d_array(array);
	while (env_copy[i])
	{
		j = i;
		while (env_copy[j])
		{
			if (is_ascii_lesser(env_copy[j], env_copy[i]))
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			++j;
		}
		++i;
	}
	return (env_copy);
}

void	print_ascii_sorted_env(t_data *data)
{
	int		i;
	char	**sorted_env;

	i = 0;
	if (!data->env)
		return ;
	sorted_env = sort_2d_array_by_ascii(data->env);
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free_array(sorted_env);
}
