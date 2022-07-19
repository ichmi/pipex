/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:08:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/18 22:51:57 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	clear_pipes(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->size)
		free(env->pfd[i]);
	free(env->pfd);
}

void	cmd_not_found(t_env *env)
{
	char	*buff;

	buff = NULL;
	buff = ft_strjoin("Command '", env->exe);
	buff = ft_strjoins(buff, "' not found\n");
	write(2, buff, ft_strlen(buff) + 1);
	free(buff);
	free(env->exe);
	exit(127);
}

void	error(char *err, int ecode, t_env *env)
{
	char	*buff;
	int		i;

	i = -1;
	if (ecode == 1)
	{
		buff = NULL;
		ft_putstr_fd("[-] bash: ", 2);
		buff = ft_strjoin(env->infile, ": No such file or directory");
		ft_putendl_fd(buff, 2);
		free(buff);
		exit(ecode);
	}
	clear_pipes(env);
	perror(err);
	strerror(ecode);
	exit(ecode);
}
