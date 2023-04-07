/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:59 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 04:18:24 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator_before_parenthesis(char *line, char *ptr)
{
	line -= line != ptr;
	while (line != ptr && *line == ' ')
		line--;
	if (*line == '(')
		return (0);
	line -= line != ptr;
	return (!is_operator(line) && line != ptr);
}

int	check_operator_after_parenthesis(char **line)
{
	*line += 1;
	skip_spaces(line);
	return (!is_operator(*line) && **line != ')' && **line);
}

int	check_missing_parenthesis(char **line)
{
	while (**line && **line != ')')
	{
		if (is_quote(**line))
			check_quotes(line);
		else if (**line == '(')
		{
			*line += 1;
			if (check_missing_parenthesis(line))
				return (1);
			*line += 1;
		}
		else
			*line += 1;
	}
	return (!**line);
}

int	check_empty_parenthesis(char **line)
{
	skip_spaces(line);
	return (**line == ')');
}

int	check_parenthesis_error(char **line, char *ptr, int is_inside_parenthesis)
{
	if (!is_inside_parenthesis && **line == ')')
		return (print_error("unexpected token error: ", *line), 1);
	if (**line == '(')
	{
		if (check_operator_before_parenthesis(*line, ptr))
			return (print_error("unexpected token error: ", *line), 1);
		*line += 1;
		if (check_empty_parenthesis(line))
			return (print_error("unexpected token error: ", *line), 1);
		if (check_line(*line, 1, ptr))
			return (1);
		if (check_missing_parenthesis(line))
			return (print_error("syntax error: missing parenthesis", NULL), 1);
		if (check_operator_after_parenthesis(line))
			return (print_error("unexpected token error: ", *line), 1);
	}
	return (0);
}
