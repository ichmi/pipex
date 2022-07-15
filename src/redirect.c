/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:17:03 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:58:27 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_rd(t_env *env)
{
	int	fd;

	close(env->pfd[0]);
	fd = open(env->infile, O_RDONLY);
	if (fd < 0)
		error("[-] infile", 6, env);
	if (dup2(fd, 0) == -1)
		error("[-] 1: dup", 7, env);
	if (dup2(env->pfd[1], STDOUT_FILENO) == -1)
		error("[-] 2: dup", 7, env);
	close(env->pfd[1]);
	close(fd);
	execve(env->cmd.path, env->cmd.args, NULL);
	error("[-] execve", 8, env);
	return (8);
}

int	init_wr(t_env *env)
{
	int	fd;

	fd = open(env->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		error("[-] outfile", 6, env);
	if (dup2(env->pfd[0], STDIN_FILENO) == -1)
		error("[-] 1: dup", 7, env);
	if (dup2(fd, 1) == -1)
		error("[-] 2: dup", 7, env);
	close(env->pfd[0]);
	close(env->pfd[1]);
	close(fd);
	execve(env->cmd.path, env->cmd.args, NULL);
	error("[-] execve", 8, env);
	return (8);
}
