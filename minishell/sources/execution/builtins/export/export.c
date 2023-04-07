/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:24:20 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:24:20 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	validate_variable(char *argument)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (ft_putstr_fd("minishell: not a valid identifier\n", 2),
			g_status = 1, 0);
	i++;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]))
			return (ft_putstr_fd("minishell: not a valid identifier\n", 2),
				g_status = 1, 0);
		i++;
	}
	if (argument[i] == '\0')
		return (0);
	return (1);
}

int	variable_count(char **arguments)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (arguments[i])
	{
		if (validate_variable(arguments[i]))
			count++;
		else
			arguments[i][0] = '\0';
		i++;
	}
	return (count);
}

char	**new_env(char **env, char **arguments)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *)
			* (bigarray_len(env) + variable_count(arguments) + 1));
	if (!new)
		return (NULL);
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new)
			return (free_dup(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	export_ms(t_command *command)
{
	int		i;
	char	**new;
	char	**env;

	i = 0;
	g_status = 0;
	env = *(environnement(NULL));
	while (env[i])
		i++;
	new = new_env(env, command->arguments);
	if (!new)
		return (g_status = 12, ft_putstr_fd(MEM, 2));
	complete_env(new, command->arguments, i);
	if (!new)
		return (g_status = 12, ft_putstr_fd(MEM, 2));
	(void)environnement(new);
	free_dup(env);
}
