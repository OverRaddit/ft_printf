/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:14:54 by gshim             #+#    #+#             */
/*   Updated: 2021/07/05 00:03:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*printd_prec(t_fd *info, int bufsize, char b, unsigned long long n)
{
	char	*temp;
	int		len;

	len = (n == 0) ? 1 : recursive(n, info->baselen);
	temp = (char*)ft_calloc(bufsize + 1, sizeof(char));
	if (b == ' ' && !info->sign)
		temp[0] = '-';
	if (len < info->prec)
		ft_memset(temp + (temp[0] == '-'), '0', info->prec - len);
	if (n == 0 && info->precbit == 1 && info->prec == 0)
		bufsize--;
	else
		ft_strcat(temp, ft_uitoa(n, info->digit, info->baselen));
	return (temp);
}

int	printd_width(t_fd *info,int bufsize, char blank, char *temp)
{
	char	*ret;

	if (!(ret = (char*)ft_calloc(info->width, sizeof(char))))
		return (-1);
	if (blank == '0' && !info->sign)
		ret[0] = '-';
	if (info->flag != '-')
		ft_memset(ret + (ret[0] == '-'), blank, info->width - bufsize);
	ft_strncat(ret, temp, bufsize);
	if (info->flag == '-')
		ft_memset(ret + bufsize, blank, info->width - bufsize);
	write(1, ret, info->width);
	info->ret = info->width;
	free(ret);
	free(temp);
	return (0);
}

int	print_number(unsigned long long n, t_fd *info)
{
	char	*temp;
	int		bufsize;
	int		len;
	char	blank;

	// 준비물
	info->flag = (info->flag == '0' && info->precbit == 1) ? ' ' : info->flag;
	blank = get_Field_blank(info);
	len = (n == 0) ? 1 : recursive(n, info->baselen);
	bufsize = get_Field_bufsize(info, len);
	if (!(temp = (char*)ft_calloc(bufsize + 1, sizeof(char))))
		return (-1);

	// prec처리
	if (blank == ' ' && !info->sign)
		temp[0] = '-';
	if (len < info->prec)
		ft_memset(temp + (temp[0] == '-'), '0', info->prec - len);
	if (n == 0 && info->precbit == 1 && info->prec == 0)
		bufsize--;
	else
		ft_strcat(temp, ft_uitoa(n, info->digit, info->baselen));

	// width를 적용한 출력
	if (bufsize < info->width)
		return printd_width(info, bufsize, blank, temp);

	// width 무시한 출력
	info->ret = bufsize;
	if (blank != ' ' && !info->sign)
		write(1, "-", 1);
	write(1, temp, ft_strlen(temp));
	free(temp);
	return (0);
}

int	print_char(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	char	blank;

	blank = get_Field_blank(info);
	bufsize = 1;
	if (bufsize < info->width)
	{
		if (!(ret = (char*)ft_calloc(info->width, sizeof(char))))
			return (-1);
		if (info->flag != '-')
			ft_memset(ret, blank, info->width - bufsize);
		ft_strncat(ret, &c, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return (0);
	}
	write(1, &c, bufsize);
	info->ret = bufsize;
	return (0);
}

int	print_str(char *str, t_fd *info)
{
	char	*ret;
	int		bufsize;
	int		len;

	// .s, .0s 같이 나오면 출력하지 않는다.
	if (str == 0)
		str = "(null)";
	if (info->precbit == 1 && info->prec == 0 && info->format == 's')
		str = "";
	len = ft_strlen(str);
	bufsize = (len > info->prec && info->prec > 0) ? info->prec : len;
	if (bufsize < info->width)
	{
		if (!(ret = (char*)ft_calloc(info->width, sizeof(char))))
			return (-1);
		if (info->flag != '-')
			ft_memset(ret, ' ', info->width - bufsize);
		ft_strncat(ret, str, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return (0);
	}
	info->ret = write(1, str, bufsize);
	return (0);
}

int	print_address(unsigned long long n, t_fd *info)
{
	char	*temp;
	int		len;

	len = (n == 0) ? 1 + 2 : recursive(n, 16) + 2;
	if (!(temp = ft_calloc(len + 1, sizeof(char))))
		return (-1);
	ft_strncat(temp, ft_xtoa(n), len);
	if (n == 0 && info->precbit == 1 && info->prec == 0)
	{
		print_str("0x", info);
		free(temp);
		return (0);
	}
	print_str(temp, info);
	free(temp);
	return (0);
}
