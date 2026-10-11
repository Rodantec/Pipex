/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:08:47 by rodantec          #+#    #+#             */
/*   Updated: 2025/04/22 10:09:06 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return ;
}

char	**get_path_cut(char **env)
{
	int		i;
	char	**pathcut;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	if (!env[i])
		return (NULL);
	pathcut = ft_split(env[i] + 5, ':');
	return (pathcut);
}

char	*try_paths(char **pathcut, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (pathcut[i])
	{
		temp = ft_strjoin(pathcut[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**pathcut;
	char	*path;

	pathcut = get_path_cut(env);
	if (!pathcut)
		return (NULL);
	path = try_paths(pathcut, cmd);
	freesplit(pathcut);
	return (path);
}

void	execute_cmd(char *cmd, char **env)
{
	char	**complete_cmd;
	char	*path;

	complete_cmd = ft_split(cmd, ' ');
	if (!complete_cmd)
		exit(1);
	path = find_path(complete_cmd[0], env);
	if (!path)
	{
		freesplit(complete_cmd);
		perror("command not found");
		exit(1);
	}
	execve(path, complete_cmd, env);
	freesplit(complete_cmd);
	free(path);
	exit(1);
}
