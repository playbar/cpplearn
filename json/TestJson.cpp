#include "TestJson.h"
#include <stdio.h>
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
TestJson::TestJson(void)
{
}

TestJson::~TestJson(void)
{
}

void TestJson::readFile( const char * fileName )
{
    if (fileName == nullptr) return;
    FILE * pFile = fopen (fileName , "r");
    if(pFile){
        //读取文件进行解析成json
        rapidjson::FileStream inputStream(pFile);
        _jsonDocument.ParseStream<0>(inputStream);
        fclose(pFile);
    }
    if(!_jsonDocument.IsObject()){
        _jsonDocument.SetObject();
    }
}

void TestJson::addStrMenber(const char *key,const char *value)
{
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(value,_jsonDocument.GetAllocator());
    _jsonDocument.AddMember(key,strValue,_jsonDocument.GetAllocator());
}

bool TestJson::hasMenber(const char *key)
{
    if (_jsonDocument.HasMember(key)) {
        return true;
    }
    return false;
}

void TestJson::removeMenber(const char *key)
{
    if (_jsonDocument.HasMember(key)) {
        _jsonDocument.RemoveMember(key);
    }
}

bool TestJson::writeFile( const char * fileName )
{
    if (fileName == nullptr) return false;
    //转为字符串格式
    rapidjson::StringBuffer buffer;
    rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
    _jsonDocument.Accept(writer);
    const char* str = buffer.GetString();
    FILE * pFile = fopen (fileName , "w");
    if (!pFile) return false;
    fwrite(str,sizeof(char),strlen(str),pFile);
    fclose(pFile);
    return true;
}

