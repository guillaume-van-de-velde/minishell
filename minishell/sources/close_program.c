/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:24 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 22:22:28 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
		i++;
	}
	if (str_arr)
		free(str_arr);
}

void	free_pipeline(t_pipeline pipeline)
{
	int	j;

	j = 0;
	while (pipeline.commands && pipeline.commands[j].is_end)
	{
		free_str_arr(pipeline.commands[j].arguments);
		pipeline.commands[j].arguments = NULL;
		if (pipeline.commands[j].input_file > 2)
			close(pipeline.commands[j].input_file);
		if (pipeline.commands[j].output_file > 2)
			close(pipeline.commands[j].output_file);
		pipeline.commands[j].input_file = 0;
		pipeline.commands[j].output_file = 1;
		j++;
	}
	if (pipeline.commands)
		free(pipeline.commands);
	pipeline.commands = NULL;
}
