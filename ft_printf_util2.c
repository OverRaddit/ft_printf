/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:32:55 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 14:59:18 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *str, int *i)
{
	char		*s;
	long long	ret;
	int			sign;

	s = (char *)str;
	ret = 0;
	while ((9 <= s[*i] && s[*i] <= 13) || s[*i] == 32)
		(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
		sign = (s[(*i)++] == '-') ? -1 : 1;
	else
		sign = 1;
	while (s[*i] != '\0' && (s[*i] >= '0' && s[*i] <= '9'))
	{
		ret = (ret * 10) + (s[*i] - '0');
		if (!(INT_MIN <= ret * sign && ret * sign <= INT_MAX))
			return ((sign < 0) ? 0 : -1);
		(*i)++;
	}
	ret *= sign;
	return ((int)ret);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned int	i;
	unsigned char	*arr;

	arr = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		arr[i] = value;
		i++;
	}
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*address;

	if (!(address = malloc(size * count)))
		return (0);
	return (ft_memset(address, 0, size * count));
}
