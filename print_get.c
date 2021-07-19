/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:40:23 by gshim             #+#    #+#             */
/*   Updated: 2021/07/07 18:55:42 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_ps_blank(t_fd *info)
{
	char	blank;

	blank = ' ';
	if (info->format == 'c' || info->format == 's' || info->format == 'p')
		blank = ' ';
	else if (info->flag == '0')
		blank = '0';
	return (blank);
}

int	get_ps_bufsize(t_fd *info, int len)
{
	if (info->format == 's' || info->format == 'p')
	{
		if (len > info->prec && info->prec > 0)
			return (info->prec);
		else
			return (len);
	}
	else
	{
		if (len < info->prec && info->prec > 0)
			return (info->prec + !info->sign);
		else
			return (len + !info->sign);
	}
}

char	get_ps_signchar(t_fd *info)
{
	if (info->sign == 0)
		return ('-');
	else
	{
		if (info->flag == '+')
			return ('+');
		else if (info->flag == ' ')
			return (' ');
		else
			return ('?');
	}
}

t_ps	*ps_init(t_fd *info, t_ULL n)
{
	t_ps	*ps;

	ps = (t_ps *)ft_calloc(1, sizeof(t_ps));
	if (ps == 0)
		return (ps);
	ps->blank = get_ps_blank(info);
	if (n == 0)
		ps->len = 1;
	else
		ps->len = recursive(n, info->baselen);
	ps->bufsize = get_ps_bufsize(info, ps->len);
	return (ps);
}
