/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:17:03 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/19 03:24:17 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_to_pipe(int i, t_env *env)
{
	pid_t	**pfd;
	int		wstatus;
	int		pid;
	int		fd;

	pfd = env->pfd;
	if (pipe(pfd[i]) == -1)
		error(PIPE, 3, env);
	pid = fork();
	if (pid == -1)
		error(FORK, 4, env);
	if (pid == 0)
	{
		close(pfd[i][0]);
		fd = open(env->infile, O_RDONLY);
		if (fd == -1)
			error(NULL, 5, env);
		dup2(fd, STDIN_FILENO);
		dup2(pfd[i][1], STDOUT_FILENO);
		exec(i, env);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		env->exit_status = WEXITSTATUS(wstatus);
	close(pfd[i][1]);
}

void	pipe_to_file(int i, t_env *env)
{
	pid_t	**pfd;
	int		wstatus;
	int		pid;
	int		fd;

	pfd = env->pfd;
	pid = fork();
	if (pid == -1)
		error(FORK, 4, env);
	if (!pid)
	{
		fd = open(env->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(pfd[i - 1][0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		exec(i, env);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		env->exit_status = WEXITSTATUS(wstatus);
	close(pfd[i - 1][0]);
}
