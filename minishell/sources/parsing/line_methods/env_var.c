/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:47 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:48:24 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	env_var_name_len(char *line)
{
	int	len;

	len = 0;
	while (line[len]
		&& (ft_isalnum(line[len])
			|| (line[len] == '?' && !len) || line[len] == '_'))
	{
		len++;
		if (line[len] == '?')
			break ;
	}
	return (len);
}

char	*get_env_var_name(char **line)
{
	int		i;
	char	*env_var_name;

	env_var_name = ft_calloc(env_var_name_len(*line) + 1, sizeof(char));
	if (!env_var_name)
		return (NULL);
	i = 0;
	while (**line
		&& (ft_isalnum(**line) || (**line == '?' && !i) || **line == '_'))
	{
		env_var_name[i] = **line;
		*line += 1;
		if (env_var_name[i] == '?')
			break ;
		i++;
	}
	return (env_var_name);
}

char	**split_handler(char *s, char c)
{
	char	**split;

	if (!s)
		return (ft_calloc(2, sizeof(char **)));
	split = ft_split(s, c);
	free(s);
	s = NULL;
	return (split);
}

void	replace_chars(char *str, char c, char replace_with)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == c)
			*str = replace_with;
		str++;
	}
}

char	**handle_env_var(char **line, int is_inside_quotes)
{
	char	*env_var_value;
	char	*env_var_name;

	*line += 1;
	env_var_name = get_env_var_name(line);
	if (!env_var_name)
		return (NULL);
	if (env_var_name[0] == '?')
		env_var_value = ft_itoa(g_status);
	else
		env_var_value = getenv_ms(env_var_name);
	free(env_var_name);
	if (!env_var_value && errno == ENOMEM)
		return (NULL);
	if (is_inside_quotes)
		return (split_handler(env_var_value, '\0'));
	replace_chars(env_var_value, '*', WILDSTAR);
	return (split_handler(env_var_value, ' '));
}
