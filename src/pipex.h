/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:39:11 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/20 21:06:37 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "utils.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}		t_cmd;

typedef struct s_env
{
	t_cmd	cmd;
	int		exit_status;
	char	**envp;
	char	**av;
	int		**pfd;
	char	*infile;
	char	*outfile;
	int		size;
	char	*exe;
}		t_env;

void	file_to_pipe(int i, t_env *env);
void	pipe_to_file(int i, t_env *env);
void	exec(int n, t_env *env);
void	arg_parser(t_env *env);
int		_awk_parser(char *exe, t_env *env);
void	error(char *err, int ecode, t_env *env);
void	cmd_not_found(t_env *env);
void	clear_pipes(t_env *env);

#endif
