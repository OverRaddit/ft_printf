#include <stdio.h>

int main(){
	double d;
	int i=0;
	char *s = "asdff%";
	while(s[i] != '\0')
	{
		printf("%d %c\n", i ,s[i]);
		i++;
	}
}