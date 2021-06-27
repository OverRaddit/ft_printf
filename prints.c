

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

void mypf_prints(char *str, fd *info)
{
    char *temp;
    char *ret;
    int i;

    i = 0;
    vlen = (int)recursive(value);
    bufsize = max(min(vlen, info->prec), info->width);
    ret = (char*)malloc(sizeof(char) * bufsize);
    ret[bufsize] = '\0';
    // temp 에 prec개 만큼 복사
    if (vlen > info->prec)
        ft_strlcpy(temp, str, prec + 1) // null 까지 포함
    else
        temp = str;
    if (min(vlen, info->prec) < info->width)
    {
        if (info->flag == '-')
            while (i < info->width - bufsize)
                ret[i++] = ' ';
        ft_strcat(ret, temp);
        if (into->flag != '-')
            while (i < info->width - bufsize)
                ret[i++] = ' ';
    }
    write(1, ret, bufsize);
    free(ret);
}