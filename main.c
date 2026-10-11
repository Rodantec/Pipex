/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:17:39 by rodantec          #+#    #+#             */
/*   Updated: 2025/04/22 10:14:14 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *pipefd, int infile, char *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(infile);
		close(pipefd[1]);
		execute_cmd(cmd, env);
		perror("Error");
		exit(1);
	}
}

void	second_child(int *pipefd, int outfile, char *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipefd[1]);
		close(outfile);
		close(pipefd[0]);
		execute_cmd(cmd, env);
		perror("Error");
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	pipefd[2];
	int	infile;
	int	outfile;

	if (argc != 5)
		return (ft_printf("Usage: infile \"cmd1\" \"cmd2\" outfile"), 1);
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (perror("Error"), 1);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		return (close(infile), perror("Error"), 1);
	if (pipe(pipefd) == -1)
		return (perror("Pipe error"), close(infile), close(outfile), 1);
	first_child(pipefd, infile, argv[2], env);
	second_child(pipefd, outfile, argv[3], env);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	wait(NULL);
	wait(NULL);
}
