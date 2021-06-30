/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:35:29 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/26 22:08:44 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env(char **env)
{
	t_env	*data;

	g_envlst = NULL;
	g_exit = 0;
	if (!env)
		return ;
	while (*env)
	{
		data = NULL;
		data = create_env(*env);
		ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(data));
		env++;
	}
	if ((data = (t_env *)find_env("PATH")) &&
		(data = (t_env *)((t_dl_list *)data)->content))
		g_path = data->val;
}

void		deal_with_input(char **line)
{
	char	*readout;
	char	*tmp;

	readout = NULL;
	tmp = NULL;
	if (0 > (ft_read_fd(0, &readout)))
		ft_putendl_fd(ERROR_READ, 2);
	if (!(*line) && !(readout))
		ms_exit(NULL);
	if (!(*line) || !(readout))
	{
		if (!(*line))
			*line = readout;
		return ;
	}
	if (!(tmp = ft_strjoin(*line, readout)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	ft_strdel(&readout);
	ft_strdel(line);
	*line = tmp;
}

int			main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	g_name = argv[0];
	init_env(env);
	set_signal();
	line = NULL;
	while (TRUE)
	{
		if (!(line))
			prompt();
		deal_with_input(&line);
		if (line[ft_strlen(line) - 1] == '\n')
		{
			line[ft_strlen(line) - 1] = 0;
			if (!(*line))
			{
				ft_strdel(&line);
				continue ;
			}
			ms_dollar(&line);
			minishell(&line);
		}
	}
	exit(0);
}
