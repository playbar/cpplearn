//
// Created by hou guoli on 2019/6/5.
//

#ifndef STL_VECTOR_TEST_H
#define STL_VECTOR_TEST_H

#include "iostream"

class DataItem
{
public:
    int	tileX;
    int	tileY;
    char etag[33];

    DataItem() {
        std::cout << "DataItem Constructor" << std::endl;
    }

    DataItem(int x, int y, char *pdata)
    {
        tileX = x;
        tileY = y;
        int ilen = strlen(pdata) > 33 ? 32 : strlen(pdata);
        memcpy(etag, pdata, ilen);
        std::cout << "DataItem Constructor -1" << std::endl;
    }

    DataItem(const DataItem& src)
    {
        this->tileX = src.tileX;
        std::cout << "DataItem Copy Constructor" << std::endl;
    }
    DataItem(DataItem&& src)
    {
        this->tileX = src.tileX;
        std::cout << "DataItem Move Constructor" << std::endl;
    }
    DataItem& operator=(const DataItem& src) noexcept
    {
        if (this == &src)
            return *this;
        this->tileX = src.tileX;
        std::cout << "operator=(const DataItem& src)" << std::endl;
        return *this;
    }
    DataItem& operator=(DataItem&& src) noexcept
    {
        if (this == &src)
            return *this;
        this->tileX = src.tileX;
        std::cout << "operator=(const DataItem&& src)" << std::endl;
        return *this;
    }
    ~DataItem()
    {
        std::cout << "DataItem Destructor" << std::endl;
    }
} ;

#endif //CPPLEARN_VECTOR_TEST_H
