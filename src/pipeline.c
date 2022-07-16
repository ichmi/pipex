/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:04:18 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/16 03:43:11 by frosa-ma         ###   ########.fr       */
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
		free(cmd_name);
		ft_free_matrix(env->cmd.args);
		ft_free_matrix(env->envp);
		error("[-] 1: program", 4, env);
	}
	return (NULL);
}

static void	validate_cmd(char *exe, t_env *env)
{
	if (!access(exe, F_OK))
		env->cmd.path = exe;
	else
		env->cmd.path = get_filepath(env, exe);
	if (env->cmd.path == NULL)
		error("[-] program", 4, env);
}

static void	tokenize_cmd(int n, char **exe, t_env *env)
{
	char	*args;

	args = env->av[n + 2];
	if (!n && !*args)
		error("[-] cmd: Command not found\n", 11, env);
	env->cmd.args = ft_split(args, ' ');
	if (n && !*env->cmd.args)
		*exe = NULL;
	else
		*exe = ft_strdup(env->cmd.args[0]);
}

int	is_awk(char *exe, t_env *env)
{
	char	**cmd;

	cmd = env->cmd.args;
	if (cmd[0] && ft_strncmp(cmd[0], "awk", 4) == 0)
	{
		if (cmd[1] && (*cmd[1] == '\'' || *cmd[1] == '"'))
		{
			_awk_parser(exe, env);
			return (1);
		}
	}
	return (0);
}

int	pipeline(t_env *env, int n, int (*fn)(t_env *))
{
	char	**cmd;
	char	*exe;

	tokenize_cmd(n, &exe, env);
	if (!exe)
		return (wrb_outfile(env));
	cmd = env->cmd.args;
	if (is_awk(exe, env))
		ft_free_matrix(cmd);
	else if (cmd[1] && (ft_strchr(cmd[1], '\'') || ft_strchr(cmd[1], '"')))
		arg_parser(env);
	validate_cmd(exe, env);
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
