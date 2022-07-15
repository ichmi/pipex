/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:11:46 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/15 05:12:29 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*trim_args(t_env *env)
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

void	arg_parsing(char *exe, t_env *env)
{
	char	**parsed_arg;

	parsed_arg = (char **)ft_calloc(3, sizeof(*parsed_arg));
	parsed_arg[0] = ft_strdup(exe);
	parsed_arg[1] = trim_args(env);
	env->cmd.args = parsed_arg;
}
