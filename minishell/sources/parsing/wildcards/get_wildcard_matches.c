/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard_matches.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:06 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:50:14 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort(char **arr, int size)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < size)
	{
		j = 1;
		while (j < size - i)
		{
			k = 0;
			while (ft_tolower(arr[j - 1][k]) && ft_tolower(arr[j][k])
				&& ft_tolower(arr[j - 1][k]) == ft_tolower(arr[j][k]))
				k++;
			if (ft_tolower(arr[j - 1][k]) > ft_tolower(arr[j][k]))
			{
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	is_match(char *curr_dir_wildcard,
	t_wildcard_info *wildcard_info, char *file)
{
	if (wildcard_info->directory_match && !is_directory(file))
		return (0);
	if (curr_dir_wildcard[0] != '.' && file[0] == '.')
		return (0);
	if (curr_dir_wildcard[0] != WILDSTAR)
		return (compare(curr_dir_wildcard, file));
	while (*file)
	{
		if (compare(curr_dir_wildcard, file))
			return (1);
		file++;
	}
	return (0);
}

int	add_match(char **match, t_wildcard_info *wildcard_info, char *entry_name)
{
	char	*temp;

	*match = ft_strdup(entry_name);
	if (!*match)
		return (1);
	if (wildcard_info->has_prefix)
	{
		temp = *match;
		*match = ft_strjoin("./", *match);
		(free(temp), temp = NULL);
		if (!*match)
			return (1);
	}
	if (wildcard_info->directory_match)
		*match = strjoin_handler(*match, "/");
	return (*match == NULL);
}

char	**read_dir(char *wildcard, char **matches,
	t_wildcard_info *wildcard_info)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	directory = opendir(".");
	if (!directory)
		return (print_error("error while opening directory\n", NULL), NULL);
	entry = readdir(directory);
	i = 0;
	while (entry)
	{
		if (is_match(wildcard, wildcard_info, entry->d_name))
		{
			if (add_match(matches + i, wildcard_info, entry->d_name))
				return (NULL);
			i++;
		}
		entry = readdir(directory);
	}
	closedir(directory);
	return (matches);
}

char	**get_wildcard_matches(char *wildcard)
{
	t_wildcard_info	wildcard_info;
	char			*curr_dir_wildcard;
	char			**matches;
	int				size;

	curr_dir_wildcard = parse_wildcard(wildcard, &wildcard_info);
	if (!curr_dir_wildcard)
		return (NULL);
	size = wildcard_matches_amount(curr_dir_wildcard, &wildcard_info);
	matches = ft_calloc(size + 1, sizeof(char **));
	if (!matches)
		return (free(curr_dir_wildcard), curr_dir_wildcard = NULL, NULL);
	matches = read_dir(curr_dir_wildcard, matches, &wildcard_info);
	(free(curr_dir_wildcard), curr_dir_wildcard = NULL);
	if (!matches)
		return (NULL);
	sort(matches, str_arr_size(matches));
	return (matches);
}
