//
// Created by hou guoli on 2019/1/8.
//

#include "vector"

void testVector()
{
    vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = idata.size()-1; j>= 0; --j)
    {
        printf("%d \n", idata[j]);
        idata.erase(idata.begin() + j);

    }
}

int main()
{
    testVector();
    return 0;
}