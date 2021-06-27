#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct fd
{
	char	flag;
	// 출력하는 길이를 뜻한다. 음수면 왼쪽정렬, 양수면 오른쪽정렬이다
	int		width;
	int		prec;
	char	format;
	int		ret;

} fd;

int		is_format(char c)
{
	char *formats = "cspdiuxX%";

	// 성능 개선을 위한 알파벳체크
	if (!(c >= 'a' && c <= 'z') && (c >= 'A' && c <= 'Z'))
		return (0);
	while (*formats)
	{
		if (c == *formats)
			return (1);
		formats++;
	}
	return (0);
}

int		is_flag(char c)
{
	// .은 다른부분에서 파싱 가능하니 한번 빼봅시다.
	char *flags = "-0*";

	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putnbr(int n)
{
	int		i;
	char	buf[11];

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		n = n * -1;
	}
	i = -1;
	if (n == 0)
		write(1, "0", 1);
	while (n > 0)
	{
		buf[++i] = (n % 10 + 48);
		n = n / 10;
	}
	while (i >= 0)
	{
		write(1, &buf[i--], 1);
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

#include <limits.h>
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

char	*ft_fielddup(const char *src, int len)
{
	char	*str;

	while (src[len] != '\0' && !is_format(src[len]))
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = src[len];
		len--;
	}
	return (str);
}

static long long	recursive(long long n)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / 10));
}

static int			getbuf(long long n, char **ret)
{
	int		len;

	if (n < 0)
		//len = recursive(-1 * n) + 1;  부호때문에 고침
		len = recursive(-1 * n);
	else if (n == 0)
		len = 1;
	else
		len = recursive(n);
	if (!(*ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	(*ret)[len] = '\0';
	return (len);
}

char				*ft_itoa(int n)
{
	int			len;
	long long	number;
	char		*ret;

	number = (long long)n;
	len = getbuf(number, &ret);
	if (len == -1)
		return (0);
	if (n < 0)
		number *= -1;
	while (--len >= 0)
	{
		ret[len] = (int)(number % 10) + '0';
		number /= 10;
	}
	// if (n < 0)
	// 	ret[0] = '-';
	return (ret);
}

char	*ft_strcat(char *dest, char *src)
{
	size_t destlen;
	size_t i;

	destlen = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int destlen;
	unsigned int i;

	destlen = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		if (i == nb)
		{
			break ;
		}
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t srclen;

	if (!dest && !src)
		return (0);
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	i = 0;
	while (i + 1 < size && i < srclen)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (srclen);
}

int		max(int x, int y)
{
	return ((x > y) ? x : y);
}

int		min(int x, int y)
{
	return ((x < y) ? x : y);
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

void	mypf_printd(int value, fd *info)
{
	char	*temp;
	char	*ret;
	int		bufsize;
	int		i;
	int		j;
	int		len;

	len = (int)recursive(value);
	// 최종버퍼 할당
	bufsize = max(max(len, info->prec), info->width);
	ret = (char*)malloc(sizeof(char) * info->width);
	ret[info->width] = '\0';

	// disp길이 설정
	bufsize = (len < info->prec && info->prec != 0) ? info->prec : len;
	temp = (char*)malloc(sizeof(char)*bufsize);
	
	i = 0;
	j = 0;
	// 정밀도
	// value가 음수일때 prec의 개수에 -를 세지 않는다....
	// -는 맨 마지막에 수동으로 붙여야 겠따!
	if (value < 0)
		temp[i++] = '-';
	if (len < info->prec)
		while (j++ < info->prec - len)
			temp[i++] = '0';
	// value 넣기
	// itoa 함수에 주석을 넣었으니 나중에 잘 수정해둘것.
	ft_strcat(temp, ft_itoa(value));
	//printf("temp: %s\n",temp);
	// 폭 규칙 (value < 0) 센스 미쳤다,,,
	if (bufsize < info->width)
	{
		if (info->flag != '-')
            ft_memset(ret, ' ', info->width - bufsize - (value < 0));
		ft_strncat(ret, temp, bufsize + (value < 0));
		if (info->flag == '-')
            ft_memset(ret + len, ' ', info->width - bufsize - (value < 0));
		write(1, ret, info->width);
		info->ret = info->width;
		free(ret);
		free(temp);
		return ;
	}
	info->ret = bufsize;
	ft_putstr(temp);
	free(temp);
}

void mypf_prints(char *str, fd *info)
{
    char	*ret;
	int		bufsize;
	int		len;
    int		i;

    i = 0;
    len = ft_strlen(str);
	// 문제의 구간 len 값이 없을때(0) 예외처리를 해줘야 함. 0이상으로 바꿀까?
    bufsize = (len > info->prec && info->prec != 0) ? info->prec : len;

    if (bufsize < info->width)
    {
		ret = (char*)malloc(sizeof(char) * info->width);
		ret[info->width] = '\0';
        if (info->flag != '-')
            ft_memset(ret, ' ', info->width - bufsize);
        ft_strncat(ret, str, bufsize);
        if (info->flag == '-')
            ft_memset(ret + len, ' ', info->width - bufsize);
		write(1, ret, info->width);
		info->ret = info->width;
		free(ret);
		return ;
    }
    write(1, str, bufsize);
	info->ret = bufsize;
}

// cspdiuxX%
void mypf_handle(va_list *ap, fd *info)
{
	if (info->format == 'd')
	{
		mypf_printd(va_arg(*ap, int), info);
	}
	else if (info->format == 'c')
	{
		ft_putchar(va_arg(*ap, int));
	}
	else if (info->format == 's')
	{
		mypf_prints(va_arg(*ap, char *), info);
	}

}
//%[플래그][폭][.정밀도][길이] 서식지정자
fd* mypf_init(va_list *ap, char *field)
{
	fd		*info;
	int		i;

	info = (fd*)malloc(sizeof(fd));
	info->flag = '@';
	info->width = 0;
	info->prec = 0;
	info->ret = 0;
	i = 0;
	// flag parsing
	if (is_flag(field[i]))
		info->flag = field[i++];
	// width parsing
	if (info->flag == '*')
		info->width = va_arg(*ap, int);
	if (field[i] >= '0' && field[i] <= '9')
		info->width = ft_atoi(field, &i);

	// prec parsing
	if (field[i] == '.')
	{
		i++;
		if (field[i] == '*')
		{
			info->prec = va_arg(*ap, int);
			i++;
		}
		info->prec = ft_atoi(field, &i);
		if (info->prec < 0)
		{
			// 이것이 *로 넘겼을때는 적용이 안되는데,,,, 어휴
			info->width = 0;
			info->prec = 0;
		}
	}
	// format parsing
	if (is_format(field[i]))
		info->format = field[i];
	return (info);
}

int ft_printf(char *one,...)
{
	va_list	ap;
	fd		*info;
	int		i;
	int		fieldlen;
	int		ret;

	ret = 0;
	i = 0;
	fieldlen = 0;
	va_start(ap, one);
	while (one[i] != '\0')
	{
		if (one[i] == '%')
		{
			while (one[fieldlen + i + 1] != '\0' && !is_format(one[fieldlen + i + 1]))
				fieldlen++;
			info = mypf_init(&ap, ft_fielddup(one + i + 1, fieldlen));
			i += fieldlen + 2;
			mypf_handle(&ap, info);
			ret += info->ret;
			free(info);
			continue;
		}
		write(1, &one[i++], 1);
		ret += 1;
	}
	va_end(ap);
	return (ret);
}

int main(){
	char *s = "42SEOUL";
	int d = -4242;
	int a,b;

	a = ft_printf("나의결과: |%4.7d|end\n", d);
	b =    printf("실제결과: |%4.7d|end\n", d);
	printf("a: %d, b: %d\n", a, b);

	// a = ft_printf("나의결과: |%.4s|end\n", s);
	// b = printf("실제결과: |%.4s|end\n", s);
	// printf("a: %d, b: %d\n", a, b);

	// a = ft_printf("나의결과: |%*.*s|end\n", 10, 9, s);
	// b = printf("실제결과: |%*.*s|end\n", 10, 9, s);
	// printf("a: %d, b: %d\n", a, b);
}
