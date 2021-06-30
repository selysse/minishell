/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:17:55 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/12 16:38:35 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i_find;
	size_t	i_s;

	if (!*find)
		return ((char*)str);
	i_s = 0;
	while (str[i_s] && i_s < n)
	{
		i_find = 0;
		while (find[i_find] && (find[i_find] == str[i_s + i_find]) &&
				((i_s + i_find) < n))
			i_find++;
		if (!find[i_find])
			return ((char*)&str[i_s]);
		i_s++;
	}
	return (0);
}

char	*ft_strncut(const char *str, size_t n)
{
	char	*ret;
	size_t	i;

	if (!str)
		return (NULL);
	if (!(ret = (char *)ft_calloc(n + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (str[i] && (n > i))
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	*ft_strinsert(char *str, char *target, size_t to)
{
	size_t	str_count;
	size_t	count;
	char	*ret;

	if (!(ret = ft_calloc(sizeof(char), ft_strlen(target) + ft_strlen(str))))
		return (NULL);
	count = 0;
	while (str[count] && (count < to))
	{
		ret[count] = str[count];
		count++;
	}
	str_count = count;
	while (*target)
	{
		ret[count++] = *target;
		target++;
	}
	while (str[str_count])
		ret[count++] = str[str_count++];
	free(str);
	return (ret);
}

char	*ft_strreplace(char *str, char *sample, ssize_t where, ssize_t insted)
{
	char	*new;
	ssize_t	count;

	if (!(new = ft_calloc(sizeof(char),
		ft_strlen(str) + ft_strlen(sample) - insted + 1)))
		return (NULL);
	count = -1;
	while ((++count < where) && *str)
		new[count] = *(str++);
	while (*sample)
		new[count++] = *(sample++);
	while (insted-- && *str)
		str++;
	while (*str)
		new[count++] = *(str++);
	return (new);
}
