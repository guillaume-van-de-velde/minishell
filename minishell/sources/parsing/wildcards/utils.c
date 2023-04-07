/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:07 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:54:58 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_matching_chunk(char *wildcard, char *file)
{
	int	i;

	i = 0;
	while (wildcard[i] && file[i]
		&& wildcard[i] != WILDSTAR && file[i] == wildcard[i])
		i++;
	return (wildcard[i] == WILDSTAR || wildcard[i] == '\0');
}

int	stuff_stuff(char *wildcard, char *file)
{
	while (*file && !is_matching_chunk(wildcard, file))
		file++;
	while (*wildcard && *file && *wildcard == *file)
	{
		file++;
		wildcard++;
	}
	if (*wildcard == WILDSTAR)
		return (compare(wildcard, file));
	return (*file == *wildcard);
}

int	compare(char *wildcard, char *file)
{
	if (*wildcard == WILDSTAR)
	{
		while (*wildcard == WILDSTAR)
			wildcard++;
		if (!*wildcard)
			return (1);
		while (*file && !stuff_stuff(wildcard, file))
			file++;
		return (*file);
	}
	if (!is_matching_chunk(wildcard, file))
		return (0);
	while (*wildcard && *file && *wildcard == *file)
	{
		file++;
		wildcard++;
	}
	if (*wildcard == WILDSTAR)
		return (compare(wildcard, file));
	return (*file == *wildcard);
}

int	wildcard_matches_amount(char *curr_dir_wildcard,
	t_wildcard_info *wildcard_info)
{
	struct dirent	*entry;
	int				count;
	DIR				*directory;

	directory = opendir(".");
	if (!directory)
		return (ft_putstr_fd("error\n", 2), 1);
	count = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (is_match(curr_dir_wildcard, wildcard_info, entry->d_name))
			count++;
		entry = readdir(directory);
	}
	closedir(directory);
	return (count);
}

char	*parse_wildcard(char *wildcard, t_wildcard_info *wildcard_info)
{
	int		i;
	char	*res;

	wildcard_info->has_prefix = 0;
	res = malloc(ft_strlen(wildcard) + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (!ft_strncmp(wildcard, "./", 2))
	{
		wildcard_info->has_prefix = 1;
		wildcard += 2;
	}
	while (wildcard[i] && wildcard[i] != '/')
	{
		res[i] = wildcard[i];
		i++;
	}
	wildcard_info->directory_match = wildcard[i] == '/';
	res[i] = '\0';
	return (res);
}
