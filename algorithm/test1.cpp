
#include <printf.h>


double calScale(int minl, int maxl, double maxScale)
{
    return maxScale / (1 << (maxl - minl));
}

int main()
{
    int  sl = 23;
    double maxs = 1 << 5;
    double mins = calScale(4, 25, maxs);
    double scale = mins * (1 << (sl - 4));

    char *pdata = "\0x89\0x54";


    printf("scale = %lf, pdata = %s\n", scale, pdata);
    return 0;

}