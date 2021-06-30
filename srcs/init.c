/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:59:55 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/27 16:21:57 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_init(void)
{
	t_redir	*redir;

	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	redir->count = 0;
	redir->fd_in = dup(STDIN_FILENO);
	redir->fd_out = dup(STDOUT_FILENO);
	redir->type = 0;
	redir->fd = -1;
	return (redir);
}

t_pipe	*pipe_init(void)
{
	t_pipe	*pipe;

	if (!(pipe = ft_calloc(sizeof(t_pipe), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	pipe->count = 0;
	pipe->pos = 0;
	pipe->pid = -1;
	pipe->fd[0][0] = -1;
	pipe->fd[0][1] = -1;
	pipe->fd[1][0] = -1;
	pipe->fd[1][1] = -1;
	return (pipe);
}
