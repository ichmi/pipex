/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:11:46 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/07/19 01:07:03 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_parser(t_env *env)
{
	char	**parsed_arg;
	char	**tokens;
	int		size;
	int		i;

	tokens = env->cmd.args;
	size = 0;
	i = -1;
	while (tokens[++i])
		size++;
	parsed_arg = (char **)ft_calloc(size + 1, sizeof(*parsed_arg));
	i = 0;
	parsed_arg[0] = ft_strdup(env->cmd.args[0]);
	while (tokens[++i])
		parsed_arg[i] = ft_strtrim(tokens[i], "'\"");
	ft_free_matrix(env->cmd.args);
	env->cmd.args = parsed_arg;
}

static char	*trim_awk_args(t_env *env)
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

int	_awk_parser(char *exe, t_env *env)
{
	char	**parsed_arg;

	parsed_arg = (char **)ft_calloc(3, sizeof(*parsed_arg));
	parsed_arg[0] = ft_strdup(exe);
	parsed_arg[1] = trim_awk_args(env);
	env->cmd.args = parsed_arg;
	return (1);
}
