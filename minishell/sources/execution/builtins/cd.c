/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:26 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 22:02:28 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*getenv_ms(char *variable)
{
	char	**env;
	char	*str;
	int		i;
	int		len_variable;

	i = 0;
	env = (*environnement(NULL));
	if (!variable || !env)
		return (NULL);
	len_variable = ft_strlen(variable);
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, len_variable + 1) == '=')
		{
			str = ft_strdup(&env[i][len_variable + 1]);
			if (!str)
				return (ft_putstr_fd(MEM, 2), NULL);
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	complete_env_pwd(t_command *command, char *old_pwd, char *pwd)
{
	command->position = 2;
	command->arguments = malloc(sizeof(char *) * 4);
	if (!command->arguments)
		return (ft_putstr_fd(MEM, 2), free(pwd), pwd = NULL, (void)0);
	command->arguments[0] = malloc(1);
	command->arguments[0][0] = '\0';
	command->arguments[1] = ft_strjoin("PWD=", pwd);
	if (!command->arguments[1])
		return (ft_putstr_fd(MEM, 2), free(command->arguments),
			command->arguments = NULL, free(pwd), pwd = NULL, (void)0);
	if (old_pwd)
	{
		command->arguments[2] = ft_strjoin("OLDPWD=", old_pwd);
		if (!command->arguments[2])
			return (ft_putstr_fd(MEM, 2), free(command->arguments[1]),
				command->arguments[1] = NULL, free(command->arguments),
				command->arguments = NULL, free(pwd), pwd = NULL, (void)0);
	}
	else
		command->arguments[2] = NULL;
	command->arguments[3] = NULL;
	export_ms(command);
	free_dup(command->arguments);
}

void	env_pwd(char *old_pwd)
{
	t_command	export_pwd;
	char		*pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd || !old_pwd)
	{
		if (errno == ERANGE)
			ft_putstr_fd("cd: Path exceeds max buffer lenght\n", 2);
		else if (errno == ENOMEM)
			ft_putstr_fd(MEM, 2);
	}
	else
		complete_env_pwd(&export_pwd, old_pwd, pwd);
	free(pwd);
	pwd = NULL;
}

void	cd_ms(t_command *command)
{
	char	*str;
	char	*old_pwd;

	g_status = 0;
	str = NULL;
	if (command->arguments[1] && command->arguments[2])
		return (g_status = 1, ft_putstr_fd("cd: too many arguments\n", 2));
	old_pwd = getcwd(NULL, 1024);
	if (command->arguments[1])
	{
		if (chdir(command->arguments[1]) == -1)
			return (ft_putstr_fd("cd: No such directory\n", 2),
				g_status = 1, free(old_pwd), old_pwd = NULL, (void)0);
	}
	else
	{
		str = getenv_ms("HOME");
		if (!str)
			return (ft_putstr_fd("cd: HOME not set\n", 2),
				g_status = 1, free(old_pwd), old_pwd = NULL, (void)0);
		if (chdir(str) == -1)
			return (ft_putstr_fd("cd: No such directory\n", 2), g_status = 1,
				free(old_pwd), old_pwd = NULL, free(str), str = NULL, (void)0);
	}
	(env_pwd(old_pwd), free(old_pwd), old_pwd = NULL, free(str), str = NULL);
}
