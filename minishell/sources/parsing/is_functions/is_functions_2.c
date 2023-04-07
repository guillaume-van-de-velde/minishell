/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:42 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:29:38 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *line)
{
	return (!ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2));
}

int	is_meta_char(char *line)
{
	return (is_pipe(line) || is_operator(line) || is_quote(*line)
		|| is_redirection(line) || is_parenthesis(line) || *line == '&');
}

int	is_wildcard(char *str)
{
	int	has_wildcard;
	int	slash_count;

	has_wildcard = 0;
	slash_count = 0;
	if (!ft_strncmp(str, "./", 2))
		str += 2;
	while (*str)
	{
		has_wildcard += *str == WILDSTAR;
		slash_count += *str == '/';
		if (slash_count && *str && *str != '/')
			return (0);
		str++;
	}
	return (has_wildcard);
}

int	is_heredoc(char *line)
{
	if (ft_strncmp(line, "<<", 2))
		return (0);
	line += 2;
	skip_spaces(&line);
	return (*line && (!is_meta_char(line) || is_quote(*line)));
}

int	is_directory(char *file)
{
	DIR		*directory;

	directory = opendir(file);
	if (directory)
		return (closedir(directory), 1);
	return (0);
}
