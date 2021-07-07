/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:42:04 by gshim             #+#    #+#             */
/*   Updated: 2021/07/07 20:41:05 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*printd_prec(t_fd *info, t_ps *ps, t_ULL n)
{
	char	*temp;

	temp = (char *)ft_calloc((ps->bufsize) + 1, sizeof(char));
	if (!temp)
		return (0);
	if (ps->blank == ' ' && info->signchar != '?')
		temp[0] = info->signchar;
	if (ps->len < info->prec)
		ft_memset(temp + (temp[0] == info->signchar), '0',
			info->prec - ps->len);
	if (n == 0 && info->precbit == 1 && info->prec == 0)
		(ps->bufsize)--;
	else
		ft_strcat(temp, ft_uitoa(n, info->digit, info->baselen));
	return (temp);
}

int	printd_width(t_fd *info, t_ps *ps, char *temp)
{
	char	*ret;

	ret = (char *)ft_calloc(info->width, sizeof(char));
	if (!ret)
		return (-1);
	if (ps->blank == '0' && info->signchar != '?')
		ret[0] = info->signchar;
	if (info->flag != '-')
		ft_memset(ret + (ret[0] == info->signchar), ps->blank,
			info->width - ps->bufsize);
	ft_strncat(ret, temp, ps->bufsize);
	if (info->flag == '-')
		ft_memset(ret + ps->bufsize, ps->blank, info->width - ps->bufsize);
	write(1, ret, info->width);
	info->ret = info->width;
	free(ret);
	free(temp);
	return (0);
}

int	print_number(t_ULL n, t_fd *info)
{
	char	*temp;
	t_ps	*ps;

	if (info->flag == '0' && info->precbit == 1)
		info->flag = 'x';
	info->signchar = get_ps_signchar(info);
	ps = ps_init(info, n);
	temp = printd_prec(info, ps, n);
	if (!temp)
		return (-1);
	if (ps->bufsize < info->width)
		return (printd_width(info, ps, temp));
	info->ret = ps->bufsize;
	if (ps->blank != ' ' && !info->sign)
		write(1, "-", 1);
	write(1, temp, ft_strlen(temp));
	free(ps);
	free(temp);
	return (0);
}
