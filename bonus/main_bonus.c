/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:01:57 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/20 21:01:03 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**get_environ(char **ep)
{
	int	i;

	i = -1;
	while (ep[++i])
		if (ft_strnstr(ep[i], "PATH=", 5))
			return (ft_split(ep[i] + 5, ':'));
	return (NULL);
}

static void	init_heredoc(int ac, char **av, char **ep, t_env *env)
{
	env->is_hd = 1;
	env->delimeter = av[2];
	env->infile = "HDOC_BUFF";
	env->av = av;
	env->size = ac - 4;
	env->outfile = av[ac - 1];
	env->envp = get_environ(ep);
	env->exe = NULL;
	env->exit_status = 0;
}

static void	init_env(int ac, char **av, char **ep, t_env *env)
{
	env->is_hd = 0;
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

int	init_files(int ac, char **av, char **ep, t_env *env)
{
	if (strncmp(av[1], "here_doc", 9) == 0)
	{
		init_heredoc(ac, av, ep, env);
		wr_hdoc_in(env);
		return (1);
	}
	init_env(ac, av, ep, env);
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	t_env	env;
	int		i;

	if ((strncmp(av[1], "here_doc", 9) == 0 && ac < 6) || ac < 5)
		error(ERR RED "bash" ENDERR, 1, NULL);
	i = init_files(ac, av, ep, &env);
	init_pipeline(&env);
	file_to_pipe(i, &env);
	pipe_to_pipe(&i, &env);
	pipe_to_file(i, &env);
	i = -1;
	while (++i < env.size)
		wait(NULL);
	if (env.is_hd)
		unlink(env.infile);
	clear_pipes(&env);
	ft_free_matrix(env.envp);
	return (env.exit_status);
}
