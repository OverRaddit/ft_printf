#include <stdio.h>
#include "ft_printf.h"
#include "ft_printf.c"
#include "ft_printf_util1.c"
#include "ft_printf_util2.c"
#include "ft_printf_util3.c"
#include "condition.c"
#include "mypf.c"
#include "print_number.c"
#include "parse.c"

int main(){

	int		a = -4;
	int		i = 8;
	int		j = -12;
	int		l = 0;

 	   printf("%.*o\n", -3, 12345);
 	ft_printf("%.*o\n", -3, 12345);
}