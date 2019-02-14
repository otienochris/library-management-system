#include <stdio.h>
#include <time.h>
#include <math.h>

int main()
{

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("borrowed date now: %d-%d-%d %d:%d:%d\n", 
        tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, 
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    
     printf("return date: %d-%d-%d %d:%d:%d\n", 
        tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, 
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    // borrowed day
    typedef struct 
    {
        int d,m,y,h,min,sec;
    }TIME;
    TIME taim;
    taim.d = tm.tm_mday, taim.m = tm.tm_mon, taim.y = tm.tm_year + 1900, taim.h = tm.tm_hour, taim.min = tm.tm_min, taim.sec = tm.tm_sec;

    printf("borrowed date now: %d-%d-%d %d:%d:%d\n",taim.d,taim.m,taim.y, taim.h,taim.min,taim.sec);
    int x = tm.tm_yday;
    printf("%d\n", x);
    printf("%ld\n", t);


    return 0;
}

