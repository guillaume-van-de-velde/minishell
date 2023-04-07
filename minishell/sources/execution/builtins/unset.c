/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:39 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:18:39 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	delete_variable(char **env, int j)
{
	char	**new;
	int		i;
	int		index_new;

	i = 0;
	index_new = 0;
	new = malloc(sizeof(char *) * bigarray_len(env));
	if (!new)
		return (g_status = 12, ft_putstr_fd(MEM, 2));
	while (env[i])
	{
		if (i != j)
		{
			new[index_new] = ft_strdup(env[i]);
			if (!new)
				return (g_status = 12, ft_putstr_fd(MEM, 2));
			index_new++;
		}
		i++;
	}
	new[index_new] = NULL;
	(void)environnement(new);
	free_dup(env);
}

int	valid_delete(char *argument)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (0);
	i++;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]))
			return (0);
		i++;
	}
	if (argument[i] == '=')
		return (0);
	return (1);
}

void	delete_env(t_command *command, int i)
{
	int		j;
	int		size_arg;
	char	**new_env;

	j = 0;
	size_arg = 0;
	new_env = *(environnement(NULL));
	while (command->arguments[i][size_arg])
		size_arg++;
	size_arg++;
	while (new_env[j])
	{
		if (ft_strncmp(new_env[j], command->arguments[i], size_arg) == '=')
		{
			delete_variable(new_env, j);
			new_env = *(environnement(NULL));
		}
		else
			j++;
	}
}

void	unset_ms(t_command *command)
{
	int	i;

	g_status = 0;
	i = 0;
	if (!command->arguments[1])
		return ;
	while (command->arguments[++i])
		if (valid_delete(command->arguments[i]))
			delete_env(command, i);
}
