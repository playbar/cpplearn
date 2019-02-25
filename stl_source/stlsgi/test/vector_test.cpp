//
// Created by hou guoli on 2019/1/8.
//

#include <iostream>
#include <vector>

void testVector()
{
    std::vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = idata.size()-1; j>= 0; --j)
    {
        std::cout<<idata[j]<<std::endl;
        idata.erase(idata.begin() + j);

    }
}

int main()
{
    testVector();
    return 0;
}