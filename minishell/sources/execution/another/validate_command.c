/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:33:36 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/06 18:51:17 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_argument_for_path(char *argument)
{
	int	i;
	int	j;

	i = 0;
	while (is_white_space(argument[i]))
		i++;
	j = i;
	while (argument[j] == '.' && argument[i])
	{
		if (argument[i] != '/' && argument[i] != '.')
			return (0);
		if (argument[i] == '/')
			return (1);
		i++;
	}
	if (i != 0 && argument[i - 1] == '.')
		return (0);
	return (1);
}

int	valide_command(char *argument)
{
	if (argument[0] == '/'
		|| (argument[0] == '.' && argument[1] == '/')
		|| (argument[0] == '.' && argument[1] == '.'
			&& argument[2] == '/'))
		return (1);
	return (0);
}
