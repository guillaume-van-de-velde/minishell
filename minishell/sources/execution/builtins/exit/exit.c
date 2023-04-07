/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:22 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:25:11 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	exit_max(char *value, char *max)
{
	int	i;

	i = 0;
	if (value[i] == '+')
		value++;
	if (ft_strlen(&value[i]) < ft_strlen(max))
		return (0);
	if (ft_strlen(&value[i]) > ft_strlen(max))
		return (1);
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (1);
		if (value[i] < max[i])
			return (0);
		if (value[i] > max[i])
			return (1);
		i++;
	}
	return (0);
}

int	exit_min(char *value, char *min)
{
	int	i;

	i = 0;
	if (ft_strlen(value) < ft_strlen(min))
		return (0);
	if (ft_strlen(value) > ft_strlen(min))
		return (1);
	i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (1);
		if (value[i] < min[i])
			return (0);
		if (value[i] > min[i])
			return (1);
		i++;
	}
	return (0);
}

int	strcmp_for_exit(char *value, char *min, char *max)
{
	int	i;
	int	check;
	int	return_value;

	i = 0;
	while ((value[i] >= 9 && value[i] <= 13) || value[i] == ' ')
		i++;
	if (!(ft_isdigit(value[i]) || value[i] == '-' || value[i] == '+'))
		return (1);
	if (value[i] == '-')
		if (!ft_isdigit(value[i + 1]))
			return (1);
	check = i + 1;
	while (value[check] && ft_isdigit(value[check]))
		check++;
	if (value[check] != '\0')
		return (1);
	if (value[i] == '-')
		return_value = exit_min(value, min);
	else
		return_value = exit_max(value, max);
	if (return_value == 1)
		return (1);
	return (return_value);
}

long	ft_atoi_exit(char *str)
{
	long	result;
	int		i;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

int	exit_ms(t_command *command)
{
	long	value;
	int		i;

	i = 0;
	value = g_status;
	while (command->arguments[i])
		i++;
	if (i > 1)
	{
		value = strcmp_for_exit(command->arguments[1], LMIN, LMAX);
		if (value == 0)
			(value = ft_atoi_exit(command->arguments[1]));
		else
			return (g_status = 2,
				ft_putstr_fd("exit: numeric argument required\n", 2), 1);
	}
	if (i == 3)
		return (g_status = 1, ft_putstr_fd("exit: too many arguments\n", 2), 0);
	if (i > 4)
		return (g_status = 127,
			ft_putstr_fd("exit: too many arguments\n", 2), 0);
	g_status = value;
	return (1);
}
