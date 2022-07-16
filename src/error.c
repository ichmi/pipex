/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:08:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 19:32:15 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *err, int ecode, t_env *env)
{
	if (ecode == 1)
	{
		write(2, err, ft_strlen(err) + 1);
		exit(ecode);
	}
	if (ecode == 11)
	{
		write(2, err, ft_strlen(err) + 1);
		ft_free_matrix(env->envp);
		exit(ecode);
	}
	perror(err);
	strerror(ecode);
	exit(ecode);
}

int	wrb_outfile(t_env *env)
{
	int		fd;

	fd = open(env->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	ft_free_matrix(env->cmd.args);
	env->pid_flag = 0;
	return (close(fd));
}
