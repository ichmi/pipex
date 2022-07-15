/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:39:11 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/14 21:03:46 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct	s_cmd
{
	char	**args;
	char	*path;
}				t_cmd;

typedef struct	s_env
{
	t_cmd	cmd;
	char	**envp;
	char	**av;
	char	*infile;
	char	*outfile;
	int		pfd[2];
	int		pid[2];
}				t_env;

#endif
