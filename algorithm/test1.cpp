
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

    printf("scale = %lf\n", scale);
    return 0;

}