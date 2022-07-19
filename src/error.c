/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:08:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/19 03:30:51 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	buff = ft_strjoin("Command '" BLUE, env->exe);
	buff = ft_strjoins(buff, RES "' not found");
	ft_putstr_fd(BASH, 2);
	ft_putendl_fd(buff, 2);
	free(buff);
	free(env->exe);
	exit(127);
}

static void	invalid_file(int ecode, t_env *env)
{
	char	*buff;

	buff = NULL;
	ft_putstr_fd(BASH BLUE, 2);
	buff = ft_strjoin(env->infile, RES ": No such file or directory");
	ft_putendl_fd(buff, 2);
	free(buff);
	exit(ecode);
}

static void	perm_denied(int ecode, t_env *env)
{
	char	*buff;
	buff = NULL;
	ft_putstr_fd(BASH BLUE, 2);
	buff = ft_strjoin(env->infile, RES ": Permission denied");
	ft_putendl_fd(buff, 2);
	free(buff);
	ft_free_matrix(env->envp);
	clear_pipes(env);
	exit(ecode);
}

void	error(char *err, int ecode, t_env *env)
{
	if (ecode == 1)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd("Use it as follow: ", 2);
		ft_putendl_fd(HOWTO, 2);
		exit(ecode);
	}
	if (ecode == 2)
		invalid_file(ecode, env);
	if (ecode == 5)
		perm_denied(ecode, env);
	clear_pipes(env);
	perror(err);
	strerror(ecode);
	exit(ecode);
}
