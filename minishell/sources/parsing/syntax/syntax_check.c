/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:21 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:42:33 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	check_line(char *line, int is_inside_parenthesis, char *line_ptr_cpy)
{
	skip_spaces(&line);
	if ((is_operator(line) || is_pipe(line)))
		return (print_error("syntax error: unexpected token: ", line), 1);
	while (*line && (*line != ')' || !is_inside_parenthesis))
	{
		if (check_quotes(&line))
			return (print_error("syntax error: missing quote", NULL), 1);
		if (check_redirection_error(&line))
			return (print_error("syntax error: unexpected token: ", line), 1);
		if (check_operator_error(&line))
			return (print_error("syntax error: unexpected token: ", line), 1);
		if (check_parenthesis_error(&line, line_ptr_cpy, is_inside_parenthesis))
			return (1);
		line += (*line && !is_meta_char(line));
	}
	return (0);
}

int	check_syntax(char *line)
{
	char	*line_ptr_cpy;

	line_ptr_cpy = line;
	if (check_line(line, 0, line_ptr_cpy))
	{
		g_status = 2;
		return (1);
	}
	return (0);
}
