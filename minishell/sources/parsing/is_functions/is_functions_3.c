/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:35:37 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:36:59 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	has_dot_slash_prefix(char *str)
{
	skip_spaces(&str);
	while (*str == '.')
		str++;
	return (*str == '/');
}

int	has_slash_prefix(char *str)
{
	skip_spaces(&str);
	return (*str == '/');
}

int	is_env_var_heredoc(char *line, char quote_type)
{
	if (*line != '$')
		return (0);
	if (!ft_isalnum(*(line + 1)) && *(line + 1) != '?' && *(line + 1) != '_')
		return (0);
	return (*(line + 1)
		&& (!quote_type || (quote_type == '"' && *(line + 1) != '"')));
}

int	is_export_command(t_command *command)
{
	char	*command_name;

	if (!command->arguments || !command->arguments[0])
		return (0);
	command_name = command->arguments[0];
	if (!command_name)
		return (0);
	return (!ft_strncmp(command_name, "export", 7));
}
