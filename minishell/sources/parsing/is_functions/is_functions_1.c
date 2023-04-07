/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:38 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 13:09:39 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_pipe(char *line)
{
	return (*line == '|' && *(line + 1) != '|');
}

int	is_redirection(char *line)
{
	if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		return (2);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

int	is_parenthesis(char *line)
{
	return (*line == '(' || *line == ')');
}

int	is_env_var(char *line, char quote_type)
{
	if (*line != '$')
		return (0);
	if (!is_quote(quote_type) && is_quote(*(line + 1)))
		return (1);
	if (!ft_isalnum(*(line + 1)) && *(line + 1) != '?' && *(line + 1) != '_')
		return (0);
	return (*(line + 1)
		&& (!quote_type || (quote_type == '"' && *(line + 1) != '"')));
}
