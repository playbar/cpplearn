#ifndef _TEST_JSON_H_
#define _TEST_JSON_H_

#include "json/document.h"
using namespace std;
class TestJson
{
public:
    TestJson(void);
    ~TestJson(void);
    //读取文件
    void readFile( const char * fileName );
    //添加字符串成员
    void addStrMenber(const char *key,const char *value);
    //是否存在成员
    bool hasMenber(const char *key);
    //删除成员
    void removeMenber(const char *key);
    //写入文件
    bool writeFile( const char * fileName );

private:
    rapidjson::Document _jsonDocument;
};
#endif

