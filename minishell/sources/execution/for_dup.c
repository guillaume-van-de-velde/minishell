/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:19:01 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:19:01 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	bigarray_len(char **bigarray)
{
	int	i;

	i = 0;
	while (bigarray[i])
		i++;
	return (i);
}

void	free_dup(char **dup_bigarray)
{
	int	i;

	i = 0;
	while (dup_bigarray[i])
		i++;
	i--;
	while (i >= 0)
	{
		free(dup_bigarray[i]);
		dup_bigarray[i] = NULL;
		i--;
	}
	free(dup_bigarray);
	dup_bigarray = NULL;
}

char	**duplicate_bigarray(char **bigarray)
{
	char	**dup_bigarray;
	int		i;

	i = 0;
	dup_bigarray = malloc(sizeof(char *) * (bigarray_len(bigarray) + 1));
	if (!dup_bigarray)
		return (ft_putstr_fd(MEM, 2),
			g_status = 12, NULL);
	while (bigarray[i])
	{
		dup_bigarray[i] = ft_strdup(bigarray[i]);
		if (!dup_bigarray[i])
			return (free_dup(dup_bigarray),
				ft_putstr_fd(MEM, 2),
				g_status = 12, NULL);
		i++;
	}
	dup_bigarray[i] = NULL;
	return (dup_bigarray);
}
