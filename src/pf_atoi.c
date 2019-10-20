/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:27:29 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:35:19 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		pf_atoi(const char *nptr)
{
	int			result;
	int			sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\r' || *nptr == '\t' ||
			*nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = *nptr++ == '-' ? -1 : 1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > 469762049 && sign == 1)
			return (-1);
		else if (result > 469762049 && sign == -1)
			return (0);
		result = result * 10 + ((int)*nptr++ - '0');
	}
	return (result * sign);
}
