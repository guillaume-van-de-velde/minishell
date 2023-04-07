/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:12 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:42:37 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_memcpy(void *dest, void *src, int data_type, int index)
{
	if (data_type == PIPELINES)
		((t_pipeline *)dest)[index] = ((t_pipeline *)src)[index];
	else if (data_type == COMMANDS)
		((t_command *)dest)[index] = ((t_command *)src)[index];
	else if (data_type == STR_ARR)
		((char **)dest)[index] = ((char **)src)[index];
	else
		((int *)dest)[index] = ((int *)src)[index];
}

int	ft_sizeof(int data_type)
{
	if (data_type == PIPELINES)
		return (sizeof(t_pipeline));
	if (data_type == COMMANDS)
		return (sizeof(t_command));
	if (data_type == STR_ARR)
		return (sizeof(char **));
	return (sizeof(int *));
}

void	*ft_realloc(void *src, int prev_size, int new_size)
{
	void	*res;
	int		i;

	res = ft_calloc(new_size, sizeof(char **));
	if (!res || !src)
		return (res);
	i = 0;
	while (i < prev_size)
	{
		((char **)res)[i] = ((char **)src)[i];
		i++;
	}
	free(src);
	src = NULL;
	return (res);
}
