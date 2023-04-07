/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:45 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 14:28:04 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_condition(char *line)
{
	return (!is_white_space(*line) && (!is_meta_char(line) || is_quote(*line)));
}

int	word_len(char *line)
{
	int		len;
	char	quote_type;

	len = 0;
	while (*line && word_condition(line))
	{
		if (is_quote(*line))
		{
			quote_type = *line;
			line++;
			while (*line && *line != quote_type)
			{
				len++;
				line++;
			}
			line++;
			continue ;
		}
		len++;
		line++;
	}
	return (len);
}

void	strcpy_quotes(char **line, char *str, int *index)
{
	char	quote_type;

	quote_type = **line;
	*line += 1;
	while (**line && **line != quote_type)
	{
		str[*index] = **line;
		*index += 1;
		*line += 1;
	}
	*line += 1;
}

char	*dup_line_word(char **line)
{
	char	*str;
	int		i;

	str = malloc((word_len(*line) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (**line && word_condition(*line))
	{
		if (is_quote(**line))
			strcpy_quotes(line, str, &i);
		else
		{
			str[i] = **line;
			i++;
			*line += 1;
		}
	}
	str[i] = '\0';
	return (str);
}
