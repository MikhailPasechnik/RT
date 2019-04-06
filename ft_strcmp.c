/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:34:15 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 17:16:27 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned const char	*v1;
	unsigned const char	*v2;

	v1 = (unsigned const char *)s1;
	v2 = (unsigned const char *)s2;
	while (*v1 && *v2 && *v1 == *v2)
	{
		v1++;
		v2++;
	}
	return (*v1 - *v2);
}
