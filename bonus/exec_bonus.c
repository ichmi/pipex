/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:04:18 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/20 15:13:27 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_filepath(t_env *env, char *cmd_name)
{
	char	**environ;
	char	*filepath;
	int		i;

	i = -1;
	environ = env->envp;
	filepath = NULL;
	while (environ[++i])
	{
		if (filepath)
			free(filepath);
		filepath = ft_strjoin(environ[i], "/");
		filepath = ft_strjoins(filepath, cmd_name);
		if (!access(filepath, F_OK))
			return (filepath);
	}
	free(filepath);
	return (ft_strdup(""));
}

static void	init_program_args(int n, char **exe, t_env *env)
{
	char	*args;

	args = env->av[n + 2];
	if (n == 0 && !*args)
	{
		if (env->envp)
			ft_free_matrix(env->envp);
		clear_pipes(env);
		exit(0);
	}
	env->cmd.args = ft_split(args, ' ');
	if (n && !*env->cmd.args)
	{
		ft_free_matrix(env->cmd.args);
		ft_free_matrix(env->envp);
		clear_pipes(env);
		exit(0);
	}
	else
		*exe = ft_strdup(env->cmd.args[0]);
}

static int	is_awk(char *exe, t_env *env)
{
	char	**cmd;

	cmd = env->cmd.args;
	if (cmd[0] && ft_strncmp(cmd[0], "awk", 4) == 0)
		if (cmd[1] && (*cmd[1] == '\'' || *cmd[1] == '"'))
			return (_awk_parser(exe, env));
	return (0);
}

void	exec(int n, t_env *env)
{
	char	**cmd;

	init_program_args(n, &env->exe, env);
	cmd = env->cmd.args;
	if (is_awk(env->exe, env))
		ft_free_matrix(cmd);
	else if (cmd[1] && (ft_strchr(cmd[1], '\'') || ft_strchr(cmd[1], '"')))
		arg_parser(env);
	if (!access(env->exe, F_OK))
		env->cmd.path = env->exe;
	else
		env->cmd.path = get_filepath(env, env->exe);
	if (execve(env->cmd.path, env->cmd.args, env->envp) == -1)
	{
		ft_free_matrix(env->cmd.args);
		ft_free_matrix(env->envp);
		free(env->cmd.path);
		clear_pipes(env);
		cmd_not_found(env);
	}
}
