/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:49 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:48:56 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_char(char **line, char **str, int is_str_arr)
{
	int		last_index;
	char	*join;

	join = ft_calloc(2, sizeof(char));
	if (!join)
		return (1);
	if (!is_str_arr || (is_str_arr && **line != '*'))
		join[0] = **line;
	else
		join[0] = WILDSTAR;
	if (is_str_arr)
		last_index = str_arr_size(str);
	else
		last_index = 0;
	if (last_index)
		last_index--;
	str[last_index] = strjoin_handler(str[last_index], join);
	*line += 1;
	free(join);
	return (str[last_index] == NULL);
}

char	*init_str_quotes(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*handle_quotes(char **line, char quote_type)
{
	char	*str;
	char	**env_var_value;

	str = init_str_quotes();
	if (!str)
		return (NULL);
	*line += 1;
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			env_var_value = handle_env_var(line, 1);
			if (!env_var_value)
				return (free(str), NULL);
			str = strjoin_handler(str, env_var_value[0]);
			free_str_arr(env_var_value);
			if (!str)
				return (NULL);
		}
		else if (add_char(line, &str, 0))
			return (free(str), NULL);
	}
	*line += 1;
	return (str);
}

int	line_arg_condition(char *line)
{
	return (!is_white_space(*line) && !is_pipe(line) && !is_operator(line)
		&& !is_redirection(line) && !is_parenthesis(line));
}

char	**get_line_args(char **line, int expand_env_var)
{
	char	**str_arr;
	char	**env_var_values;

	str_arr = ft_calloc(2, sizeof(char **));
	if (!str_arr)
		return (NULL);
	while (**line && line_arg_condition(*line))
	{
		if (is_env_var(*line, 0))
		{
			env_var_values = handle_env_var(line, expand_env_var);
			str_arr = join_arr_strjoin(str_arr, env_var_values);
			if (!str_arr)
				return (NULL);
		}
		else if (is_quote(**line))
		{
			if (strjoin_str_arr(str_arr, handle_quotes(line, **line)))
				return (free_str_arr(str_arr), NULL);
		}
		else if (add_char(line, str_arr, 1))
			return (NULL);
	}
	return (str_arr);
}
