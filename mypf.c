/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:14:54 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 15:28:55 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	mypf_printd(unsigned long long value, t_fd *info)
{
	char	*temp;
	char	*ret;
	int		bufsize;
	int		len;
	char	blank;

	// prec이 존재하면 '0'플래그는 무시된다.
	info->flag = (info->flag == '0' && info->precbit == 1) ? ' ' : info->flag;
	blank = (info->prec == 0) && (info->flag == '0') ? '0' : ' ';
	len = (value == 0) ? 1 : recursive(value, info->baselen);


	// disp길이 설정(prec적용 후의 길이)
	bufsize = (len < info->prec && info->prec != 0) ? info->prec : len;
	bufsize = (!info->sign) ? bufsize + 1 : bufsize;
	temp = (char*)ft_calloc(bufsize + 1, sizeof(char));

	// 정밀도 처리
	if (blank == ' ' && !info->sign)
		temp[0] = '-';
	if (len < info->prec)
		ft_memset(temp + (temp[0] == '-'), '0', info->prec - len);

	// value 넣기
	if (value == 0 && info->precbit == 1 && info->prec == 0)
		bufsize--;
	else
		ft_strcat(temp, ft_uitoa(value, info->digit, info->baselen));
	if (bufsize < info->width)
	{
		// 최종버퍼 할당
		ret = (char*)ft_calloc(info->width, sizeof(char));
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
		return ;
	}
	info->ret = bufsize;
	if (blank != ' ' && !info->sign)
		write(1, "-", 1);
	write(1, temp, ft_strlen(temp));
	free(temp);
}

void	mypf_printc(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	char	blank;

	blank = (info->flag == '0' && info->format == '%') ? '0' : ' ';
	bufsize = 1;
	if (bufsize < info->width)
	{
		ret = (char*)ft_calloc(info->width, sizeof(char));
		if (info->flag != '-')
			ft_memset(ret, blank, info->width - bufsize);
		ft_strncat(ret, &c, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return ;
	}
	write(1, &c, bufsize);
	info->ret = bufsize;
}

void	mypf_prints(char *str, t_fd *info)
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
		ret = (char*)ft_calloc(info->width, sizeof(char));
		if (info->flag != '-')
			ft_memset(ret, ' ', info->width - bufsize);
		ft_strncat(ret, str, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return ;
	}
	info->ret = write(1, str, bufsize);;
}

void	mypf_printp(unsigned long long n, t_fd *info)
{
	char	*temp;
	int		len;

	// 0x에 해당하는 길이를 추가로 더해줘야 한다.
	len = (n == 0) ? 1 + 2 : recursive(n, 16) + 2;
	temp = ft_calloc(len + 1, sizeof(char));

	ft_strncat(temp, ft_xtoa(n), len);
	if (n == 0 && info->precbit == 1 && info->prec == 0 && info->format == 'p')
	{
		mypf_prints("0x", info);
		free(temp);
		return ;
	}
	mypf_prints(temp, info);
	free(temp);
}
