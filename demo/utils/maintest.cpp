//
// Created by hou guoli on 2019/3/12.
//
#include "md5.h"
#include "utils.h"

void testutils()
{
    std::vector<std::string> files;
    CUtils::list_dir_files("./", files);
    for( int i = 0; i < files.size(); ++i )
    {
        printf("file:%s \n", files[i].c_str());
    }
    return;
}

int main()
{
    std::string str;
    int len = str.length();
    int size = str.size();

    str.resize(20);
    len = str.length();
    size = str.size();

    str = "abcdefg";
    str.resize(100);

    len = str.length();
    size = str.size();

    str[2] = '\0';
    int lenstr = strlen( str.c_str());
    len = str.length();
    size = str.size();

    printf("len : %d, size : %d", len, size );
    testutils();
    return 0;
}