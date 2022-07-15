/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:01:57 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:59:25 by frosa-ma         ###   ########.fr       */
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

static void	init_data(t_env *env, char **av, char **ep)
{
	if (access(av[1], F_OK) == -1)
		error("[-] infile", 3, env);
	env->infile = av[1];
	env->outfile = av[4];
	env->envp = get_environ(ep);
	env->av = av;
}

int	main(int ac, char **av, char **ep)
{
	t_env	env;

	if (ac != 5)
		error("[-] argv", 1, NULL);
	if (pipe(env.pfd) == -1)
		error("[-] pipe", 2, NULL);
	init_data(&env, av, ep);
	if (pipeline(&env, 0, init_rd) != 0)
		error("[-] 1: exec", 9, &env);
	if (pipeline(&env, 1, init_wr) != 0)
		error("[-] 2: exec", 10, &env);
	close(env.pfd[0]);
	close(env.pfd[1]);
	waitpid(env.pid[0], NULL, 0);
	waitpid(env.pid[1], NULL, 0);
	ft_free_matrix(env.envp);
	return (0);
}
