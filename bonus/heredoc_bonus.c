/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:45:03 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/20 20:47:13 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wr_hdoc_in(t_env *env)
{
	char	*delimeter;
	char	*s;
	int		fd;

	delimeter = env->delimeter;
	fd = open(env->infile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		s = _gnl(STDOUT_FILENO);
		if (ft_strncmp(s, delimeter, ft_strlen(delimeter)) == 0)
			break ;
		ft_putstr_fd(s, fd);
		free(s);
	}
	_gnl(SENTINEL);
	close(fd);
	free(s);
}
