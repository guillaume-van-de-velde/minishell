/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:52 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:30:04 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	handle_simple_left_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(command, file, READ))
		return (RED_ERROR);
	if (command->input_file > 2)
		close(command->input_file);
	command->input_file = open(file, O_RDONLY);
	if (command->input_file == -1)
	{
		command->status = errno;
		print_error("could not open file: ", file);
	}
	return (command->input_file == -1);
}

int	handle_simple_right_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(command, file, WRITE))
		return (RED_ERROR);
	if (command->output_file != 1)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_file == -1)
	{
		command->status = errno;
		print_error("could not open file: ", file);
	}
	return (command->output_file == -1);
}

int	handle_double_right_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(command, file, WRITE))
		return (RED_ERROR);
	if (command->output_file != 1)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (command->output_file == -1)
	{
		command->status = errno;
		print_error("could not open file: ", file);
	}
	return (command->output_file == -1);
}
