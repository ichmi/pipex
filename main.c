/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:01:57 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/14 22:27:24 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include "pipex.h"

void	error(char *err, int ecode, t_env *env) // 11
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

char	*get_executable(t_env *env, char *cmd_name) // 23
{
	char	**environ;
	char	*filepath;
	char	*p;
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

char	*arg_parsing(t_env *env) // 18
{
	char	**token;
	char	*buff;
	char	*str;
	char	*p;
	int		i;

	i = 0;
	token = env->cmd.args;
	buff = NULL;
	while (token[++i])
	{
		p = ft_strjoin(token[i], " ");
		buff = ft_strjoins(buff, p);
		free(p);
	}
	str = ft_strtrim(buff, "' \"");
	free(buff);
	return (str);
}

int	init_rd_end(t_env *env) // 15
{
	int	fd;

	close(env->pfd[0]);
	fd = open(env->infile, O_RDONLY);
	if (fd < 0)
		error("[-] infile", 6, env);
	if (dup2(fd, 0) == -1)
		error("[-] 1: dup", 7, env);
	if (dup2(env->pfd[1], STDOUT_FILENO) == -1)
		error("[-] 2: dup", 7, env);
	close(env->pfd[1]);
	close(fd);
	execve(env->cmd.path, env->cmd.args, NULL);
	error("[-] execve", 8, env);
	return (8);
}
int	init_wr_end(t_env *env) // 15
{
	int fd;

	fd = open(env->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		error("[-] outfile", 6, env);
	if (dup2(env->pfd[0], STDIN_FILENO) == -1)
		error("[-] 1: dup", 7, env);
	if (dup2(fd, 1) == -1)
		error("[-] 2: dup", 7, env);
	close(env->pfd[0]);
	close(env->pfd[1]);
	close(fd);
	execve(env->cmd.path, env->cmd.args, NULL);
	error("[-] execve", 8, env);
	return (8);
}

int	pipeline(t_env *env, int n, int (*fn)(t_env *)) // 36
{
	char	**parsed_arg;
	char	**cmd;
	char	*args;
	char	*exe;

	args = env->av[n + 2];
	if (!*args)
		error("[-] 1: args", 11, env);
	env->cmd.args = ft_split(args, ' ');
	if (!*env->cmd.args || env->cmd.args == NULL)
		error("[-] 2: args", 12, env);
	cmd = env->cmd.args;
	exe = ft_strdup(env->cmd.args[0]);
	if (*cmd[1] == '\'' || *cmd[1] == '"')
	{
		parsed_arg = (char **)ft_calloc(3, sizeof(*parsed_arg));
		parsed_arg[0] = ft_strdup(exe);
		parsed_arg[1] = arg_parsing(env); // ?? may overwrite cmd.args heap (fixed)
		ft_free_matrix(cmd);
		env->cmd.args = parsed_arg;
	}
	if (!access(exe, F_OK))
		env->cmd.path = exe;
	else
		env->cmd.path = get_executable(env, exe);
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

static char	**get_environ(char **ep) // 7
{
	int	i;

	i = -1;
	while(ep[++i])
		if (ft_strnstr(ep[i], "PATH=", 5))
			return (ft_split(ep[i] + 5, ':'));
	return (NULL);
}

static void	init_data(t_env *env, char **av, char **ep) // 6
{
	if (access(av[1], F_OK) == -1)
		error("[-] infile", 3, env);
	env->infile = av[1];
	env->outfile = av[4];
	env->envp = get_environ(ep);
	env->av = av;
}

int main(int ac, char **av, char **ep) // 17
{
	t_env	env;

	if (ac != 5)
		error("[-] argv", 1, NULL);
	if (pipe(env.pfd) == -1)
		error("[-] pipe", 2, NULL);
	init_data(&env, av, ep);
	if (pipeline(&env, 0, init_rd_end) != 0)
		error("[-] 1: exec", 9, &env);
	if (pipeline(&env, 1, init_wr_end) != 0)
		error("[-] 2: exec", 10, &env);
	close(env.pfd[0]);
	close(env.pfd[1]);
	waitpid(env.pid[0], NULL, 0);
	waitpid(env.pid[1], NULL, 0);
	ft_free_matrix(env.envp);
	return (0);
}
