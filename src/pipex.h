/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:39:11 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:55:57 by frosa-ma         ###   ########.fr       */
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
# include "pipex.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}		t_cmd;

typedef struct s_env
{
	t_cmd	cmd;
	char	**envp;
	char	**av;
	char	*infile;
	char	*outfile;
	int		pfd[2];
	int		pid[2];
}		t_env;

int		pipeline(t_env *env, int n, int (*fn)(t_env *));
int		init_rd(t_env *env);
int		init_wr(t_env *env);
void	arg_parsing(char *exe, t_env *env);
void	error(char *err, int ecode, t_env *env);

#endif
