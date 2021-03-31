#include <stdio.h>
#include <errno.h>
#include <string.h>

int reverse(char **s)
{
    __rev_helper(s);
}

int __rev_helper(char **s)
{
    if (s == NULL || *s == NULL)
        return -EFAULT;

    printf("%s\n", *s);

    int len = strlen(*s);
    char *b = *s;
    char *e = *(*s + len);
    char t;
    while (b < e)
    {
	t  = *s;
	*s = *e;
	*e = t;	
	b++;
	e--;
    }
    
    printf("after rev %s\n", *s);
    
    return 0;
}
