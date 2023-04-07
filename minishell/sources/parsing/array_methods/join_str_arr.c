/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:45:01 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**str_arr_dup(char **src)
{
	char	**res;
	int		i;

	res = malloc((str_arr_size(src) + 1) * sizeof(char **));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = ft_strdup(src[i]);
		if (!res[i])
			return (free_str_arr(res), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	strjoin_str_arr(char **str_arr, char *join)
{
	int		last_index;

	if (!join)
		return (1);
	last_index = str_arr_size(str_arr);
	if (last_index)
		last_index--;
	str_arr[last_index] = strjoin_handler(str_arr[last_index], join);
	free(join);
	join = NULL;
	if (!str_arr[last_index] && errno == ENOMEM)
		return (1);
	return (0);
}

char	**join_arr_strjoin(char **dest, char **arr2)
{
	int		j;
	int		last_index;
	int		dest_size;

	if (!arr2)
		return (NULL);
	dest_size = str_arr_size(dest);
	last_index = dest_size;
	if (last_index)
		last_index--;
	dest = ft_realloc(dest, dest_size, dest_size + str_arr_size(arr2) + 2);
	if (!dest)
		return (free_str_arr(arr2), NULL);
	if (arr2[0] && strjoin_str_arr(dest, arr2[0]))
		return (free_str_arr(dest), free_str_arr(arr2), NULL);
	j = 1;
	while (arr2[j])
	{
		if (arr2[j][0])
			dest[j + last_index] = arr2[j];
		else
			(free(arr2[j]), arr2[j] = NULL);
		j++;
	}
	return (free(arr2), arr2 = NULL, dest);
}

char	**join_str_arr(char **dest, char **arr2)
{
	int		dest_size;

	if (!arr2)
		return (free_str_arr(dest), NULL);
	dest_size = str_arr_size(dest);
	dest = ft_realloc(dest, dest_size, dest_size + str_arr_size(arr2) + 2);
	if (!dest)
		return (free_str_arr(arr2), NULL);
	mem_cpy_str_arr(dest + dest_size, arr2);
	return (free(arr2), arr2 = NULL, dest);
}
