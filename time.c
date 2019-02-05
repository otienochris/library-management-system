#include <stdio.h>
// #include <string.h>
#include <time.h>
#include <math.h>
// #include <curses.h>

int main()
{
    int x;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("borrowed date now: %d-%d-%d %d:%d:%d\n", 
        tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, 
        tm.tm_hour, tm.tm_min, tm.tm_sec);
     printf("return date: %d-%d-%d %d:%d:%d\n", 
        tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, 
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    char x;
    printf("%d", x);

    return 0;
}
