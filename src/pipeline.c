/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:04:18 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:18:18 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (filepath)
	{
		free(filepath);
		error("[-] program", 4, env);
	}
	return (NULL);
}

static void	tokenize_cmd(int n, char **exe, t_env *env)
{
	char	*args;

	args = env->av[n + 2];
	if (!*args)
		error("[-] 1: args", 11, env);
	env->cmd.args = ft_split(args, ' ');
	if (!*env->cmd.args || env->cmd.args == NULL)
		error("[-] 2: args", 12, env);
	*exe = ft_strdup(env->cmd.args[0]);
}

int	pipeline(t_env *env, int n, int (*fn)(t_env *))
{
	char	**cmd;
	char	*exe;

	tokenize_cmd(n, &exe, env);
	cmd = env->cmd.args;
	if (*cmd[1] == '\'' || *cmd[1] == '"')
	{
		arg_parsing(exe, env);
		ft_free_matrix(cmd);
	}
	if (!access(exe, F_OK))
		env->cmd.path = exe;
	else
		env->cmd.path = get_filepath(env, exe);
	if (env->cmd.path == NULL)
		error("[-] program", 4, env);
	env->pid[n] = fork();
	if (env->pid[n] == -1)
		error("[-] fork", 5, env);
	if (!env->pid[n])
		return (fn(env));
	ft_free_matrix(env->cmd.args);
	free(env->cmd.path);
	free(exe);
	return (0);
}
