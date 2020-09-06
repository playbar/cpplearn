#include <stdio.h>
long a=10000,b=0,c=10000,d,e,f[10001],g;
int main()
{
    for(;b != c; f[b++] = a/5)
        ;
    for(; d=0,g=c*2,c>5000; c--,printf("%.4d",e+d/a),e=d%a)
        for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b)
            ;

    return 0;
}