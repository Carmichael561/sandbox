#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <dlfcn.h>
struct tm* (*orig_localtime)(const time_t *timep);
struct tm* localtime(const time_t *timep)
{
    time_t t = (*timep - 60*60*24);
    t = 1142085600;
    printf("%s", ctime(&t));
    return orig_localtime(&t);
}
void _init(void)
{
    printf("Loading hack\n");
    orig_localtime = dlsym(RTLD_NEXT, "localtime");

    if (orig_localtime == NULL)
    {
	printf("Cannot load symbol: %s\n", dlerror());
    }

    printf("localdate = %p\n", orig_localtime);

    time_t base = 1142085600;
    for(int i = 0; i < 4; ++i) {
    time_t time = base + i * 24 * 60 * 60;
    printf("%s", ctime(&time));
    }
}
