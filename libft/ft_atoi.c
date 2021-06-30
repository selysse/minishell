/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:56:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/25 17:15:29 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *s)
{
	unsigned long	rez;
	int				sign;

	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	rez = 0;
	while (*s >= '0' && *s <= '9')
	{
		rez = rez * 10 + (*s - '0');
		s++;
		if (rez > 9223372036854775807)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (rez * sign);
}