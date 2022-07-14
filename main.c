/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:01:57 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/14 01:27:50 by frosa-ma         ###   ########.fr       */
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

typedef struct	s_data
{
	char	**cmd;
	char	*bin;
}				t_data;

static char	**__get_environ(char **ep)
{
	int	i;

	i = -1;
	while(ep[++i])
		if (ft_strnstr(ep[i], "PATH=", 5))
			return (ft_split(ep[i] + 5, ':'));
	return (NULL);
}

char	*get_executable(char **environ, char *cmd)
{
	char	*filepath;
	int		i;

	i = -1;
	while (environ[++i])
	{
		filepath = ft_strjoin(environ[i], "/");
		filepath = ft_strjoins(filepath, cmd);
		if (!access(filepath, F_OK))
			return (filepath);
	}
	return (NULL);
}

char	*arg_parsing(char **cmd_args)
{
	char	*buff;
	char	*str;
	char	*p;
	int		i;

	buff = ft_strdup("");
	i = 0;
	while (cmd_args[++i])
	{
		p = ft_strjoin(cmd_args[i], " ");
		buff = ft_strjoins(buff, p);
		free(p);
	}
	str = ft_strtrim(buff, "' \"");
	free(buff);
	return (str);
}

void	init_rd_end(int *pfd, char *file, char *bin, char **cmd)
{
	int	fd;

	close(pfd[0]);
	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	close(fd);
	execve(bin, cmd, NULL);
}
void	init_wr_end(int *pfd, char *file, char *bin, char **cmd)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, 0777);
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, 1);
	close(fd);
	close(pfd[0]);
	close(pfd[1]);
	execve(bin, cmd, NULL);
}

void	init_pipes(char **av, char *infile, char *outfile, char **envp)
{
	char	**cmd;
	char	*bin;
	int		pfd[2];
	int		pid[2];

	pipe(pfd);
	cmd = ft_split(av[2], ' ');
	if (*cmd[1] == '\'' || *cmd[1] == '"')
	{
		cmd[1] = arg_parsing(cmd);
		cmd[2] = NULL;
	}
	if (*cmd[0] == '/')
		bin = cmd[0];
	else
		bin = get_executable(envp, cmd[0]);

	pid[0] = fork();
	if (!pid[0])
	{
		init_rd_end(pfd, infile, bin, cmd);
		return ;
	}

	cmd = ft_split(av[3], ' ');
	bin = get_executable(envp, cmd[0]);

	pid[1] = fork();
	if (!pid[1])
	{
		init_wr_end(pfd, outfile, bin, cmd);
		return ;
	}

	close(pfd[0]);
	close(pfd[1]);
}

int main(int ac, char **av, char **envp)
{
	// char	**cmd;
	char	*bin;
	pid_t	pid[2];
	// int		pfd[2];
	int		fd;

	// pipe(pfd);
	envp = __get_environ(envp);
	// cmd = ft_split(av[2], ' ');
	// if (*cmd[1] == '\'' || *cmd[1] == '"')
	// {
	// 	cmd[1] = arg_parsing(cmd);
	// 	cmd[2] = NULL;
	// }
	// if (*cmd[0] == '/')
	// 	bin = cmd[0];
	// else
	// 	bin = get_executable(envp, cmd[0]);

	init_pipes(av, av[1], av[4], envp);

	// pid[0] = fork();
	// if (!pid[0])
	// {
	// 	close(pfd[0]);
	// 	fd = open(av[1], O_RDONLY);
	// 	dup2(fd, 0);
	// 	dup2(pfd[1], STDOUT_FILENO);
	// 	close(pfd[1]);
	// 	close(fd);
	// 	execve(bin, cmd, NULL);
	// }

	// cmd = ft_split(av[3], ' ');
	// bin = cmd_absolute_path(envp, cmd[0]);

	// pid[1] = fork();
	// if (!pid[1])
	// {
	// 	fd = open(av[4], O_WRONLY | O_CREAT, 0777);
	// 	dup2(pfd[0], STDIN_FILENO);
	// 	dup2(fd, 1);
	// 	close(fd);
	// 	close(pfd[0]);
	// 	close(pfd[1]);
	// 	execve(bin, cmd, NULL);
	// }

	// close(pfd[0]);
	// close(pfd[1]);

	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);

	return (0);
}
