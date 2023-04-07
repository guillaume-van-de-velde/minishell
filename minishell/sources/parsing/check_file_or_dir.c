/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_or_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:29:02 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:33:10 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	check_file_access(t_command *command, char *file, int access_type)
{
	if (access_type == EXEC && access(file, X_OK))
	{
		command->status = 126;
		print_error_arg(": permission denied", file);
		return (1);
	}
	else if (access_type == WRITE && access(file, W_OK))
	{
		command->status = 1;
		print_error_arg(": permission denied", file);
		return (1);
	}
	else if (access_type == READ && access(file, R_OK))
	{		
		command->status = 1;
		print_error_arg(": permission denied", file);
		return (1);
	}
	return (0);
}

int	check_is_directory_str(char *str)
{
	skip_spaces(&str);
	while (*str == '.')
		str++;
	while (*str == '/')
		str++;
	while (*str)
	{
		if (*str == '/' && *(str + 1) == '\0')
			return (1);
		str++;
	}
	return (0);
}

int	check_write_access_type(t_command *command, char *str, int access_type)
{
	if (check_is_directory_str(str))
	{
		command->status = 1;
		return (print_error_arg(": is a directory", str), 1);
	}
	if (!access(str, F_OK))
	{
		if (is_directory(str))
		{
			command->status = 1;
			return (print_error_arg(": is a directory", str), 1);
		}
		return (check_file_access(command, str, access_type));
	}
	return (0);
}

int	check_exec_access_type(t_command *command, char *str, int access_type)
{
	if (!ft_strncmp(str, ".", 2))
	{
		command->status = 2;
		return (print_error_arg(": filename argument required", "."), 1);
	}
	if (!has_dot_slash_prefix(str)
		&& !has_slash_prefix(str) && !check_is_directory_str(str))
		return (0);
	if (!access(str, F_OK))
	{
		if (is_directory(str))
		{
			command->status = 126;
			return (print_error_arg(": is a directory", str), 1);
		}
		return (check_file_access(command, str, access_type));
	}
	if (check_is_directory_str(str))
	{
		command->status = 126;
		return (print_error_arg(": not a directory", str), 1);
	}
	command->status = 127;
	return (print_error_arg(": no such file or directory", str), 1);
}

int	file_or_dir_check(t_command *command, char *str, int access_type)
{
	if (!str)
		return (0);
	if (access_type == EXEC)
	{
		return (check_exec_access_type(command, str, access_type));
	}
	else if (access_type == WRITE)
	{
		return (check_write_access_type(command, str, access_type));
	}
	else if (access_type == READ)
	{
		if (!access(str, F_OK))
			return (check_file_access(command, str, access_type));
		command->status = 1;
		if (check_is_directory_str(str))
			return (print_error_arg(": not a directory", str), 1);
		return (print_error_arg(": no such file or directory", str), 1);
	}
	return (0);
}
