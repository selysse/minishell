/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:06:32 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/27 17:14:03 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		flag_placer(char *content, char *flag)
{
	if (!(*flag))
	{
		if ((*flag = find_quotes((*content), *flag)))
		{
			ft_strmoveleft(content);
			return (1);
		}
	}
	else if (*flag)
		if (!(*flag = find_quotes((*content), *flag)))
		{
			ft_strmoveleft(content);
			return (1);
		}
	return (0);
}

static size_t	sizeof_content(char *content)
{
	char	flag;
	size_t	size;

	flag = 0;
	size = 0;
	ft_strpass_rev(content, " ");
	while (*content)
	{
		if (!flag)
			if ((*content) == ' ')
				size++;
		flag = find_quotes(*content, flag);
		content++;
	}
	return (size);
}

char			**prepere_cmd(char *content)
{
	char	**cmd;
	char	flag;
	ssize_t	count;
	size_t	size;

	flag = 0;
	size = 0;
	count = -1;
	if (!(cmd = ft_calloc(sizeof(char *), sizeof_content(content) + 2)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	while (content[++count])
	{
		if (!flag && (' ' == content[count]))
		{
			if (!(cmd[size++] = ft_strncut(content, count)))
				error_exit(EXIT_FAILURE, ERROR_MALLOC);
			content = ft_strpass((content += count), " ");
			count = -1;
		}
		if (flag_placer(&(content[count > 0 ? count : 0]), &flag))
			count = count <= 0 ? -1 : count - 1;
	}
	if (*content && !(cmd[size] = ft_strdup(content)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	return (cmd);
}

static int		check_shell_cmd(char **cmd, char *cmd_check,
								void (func)(char **))
{
	if (cmd && (ft_strlen(cmd_check) ==
					(size_t)ft_strcmp_reg(cmd[0], cmd_check)))
	{
		func(&(cmd[1]));
		ft_freestrs(cmd);
		return (TRUE);
	}
	return (FALSE);
}

int				run_cmd(char *content)
{
	char **cmd;

	if (!content || !*content)
		return (ft_puterr(NULL, NULL, ERROR_SYNTAX, EXIT_FAILURE));
	cmd = prepere_cmd(content);
	if (!cmd || !*cmd || !**cmd)
		return (ft_puterr(NULL, NULL, ERROR_SYNTAX, EXIT_FAILURE));
	if (check_shell_cmd(cmd, MS_CD, ms_cd))
		return (0);
	else if (check_shell_cmd(cmd, MS_ECHO, ms_echo))
		return (0);
	else if (check_shell_cmd(cmd, MS_PWD, ms_pwd))
		return (0);
	else if (check_shell_cmd(cmd, MS_UNSET, ms_unset))
		return (0);
	else if (check_shell_cmd(cmd, MS_ENV, ms_env))
		return (0);
	else if (check_shell_cmd(cmd, MS_EXPORT, ms_export))
		return (0);
	else if (check_shell_cmd(cmd, MS_EXIT, ms_exit))
		return (0);
	else
		ms_exec(cmd);
	ft_freestrs(cmd);
	return (0);
}
