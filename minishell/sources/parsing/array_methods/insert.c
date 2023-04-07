/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:29:18 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:43:44 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mem_cpy_str_arr_upto(char **dest, char **src, int up_to)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return ;
	while (i < up_to && src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

void	mem_cpy_str_arr(char **dest, char **src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return ;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

char	**insert_str_arr_at_index(char **arr1, char **arr2, int index)
{
	char	**res;
	int		arr2_size;

	arr2_size = str_arr_size(arr2);
	res = ft_calloc(str_arr_size(arr1) + arr2_size + 1, sizeof(char **));
	if (!res)
		return (NULL);
	mem_cpy_str_arr_upto(res, arr1, index);
	free(arr1[index]);
	arr1[index] = NULL;
	mem_cpy_str_arr(res + index, arr2);
	mem_cpy_str_arr(res + index + arr2_size, arr1 + index + 1);
	free(arr1);
	arr1 = NULL;
	return (res);
}
