/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:08:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:17:57 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *err, int ecode, t_env *env)
{
	if (ecode > 3)
	{
		ft_free_matrix(env->envp);
		free(env->envp);
		ft_free_matrix(env->cmd.args);
		free(env->cmd.args);
		free(env->cmd.path);
	}
	perror(err);
	strerror(ecode);
	exit(ecode);
}
