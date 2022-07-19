/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:01:57 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/19 02:45:09 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_environ(char **ep)
{
	int	i;

	i = -1;
	while (ep[++i])
		if (ft_strnstr(ep[i], "PATH=", 5))
			return (ft_split(ep[i] + 5, ':'));
	return (NULL);
}

static void	init_env(int ac, char **av, char **ep, t_env *env)
{
	env->infile = av[1];
	if (access(av[1], F_OK) == -1)
		error(NULL, 2, env);
	env->av = av;
	env->size = ac - 3;
	env->outfile = av[ac - 1];
	env->envp = get_environ(ep);
	env->exe = NULL;
	env->exit_status = 0;
}

static void	init_pipeline(t_env *env)
{
	int	**pfd;
	int	i;

	pfd = (int **)ft_calloc(env->size, sizeof(*pfd));
	i = -1;
	while (++i < env->size)
		pfd[i] = (int *)ft_calloc(2, sizeof(int));
	env->pfd = pfd;
}

int	main(int ac, char **av, char **ep)
{
	t_env	env;
	int		i;

	if (ac != 5)
		error(BASH, 1, NULL);
	init_env(ac, av, ep, &env);
	init_pipeline(&env);
	file_to_pipe(0, &env);
	pipe_to_file(1, &env);
	i = -1;
	while (++i < env.size)
		wait(NULL);
	clear_pipes(&env);
	ft_free_matrix(env.envp);
	return (env.exit_status);
}
