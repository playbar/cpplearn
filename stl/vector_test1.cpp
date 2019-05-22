
#include "vector.h"

int main()
{
    vector<int> v1{1, 5, 16, 8};
    for( int i = 0; i < v1.size(); ++i )
    {
        printf("%d \n", v1[i]);
    }

    return 0;
}


