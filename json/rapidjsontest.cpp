#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <fstream>

#define psln(x) std::cout << #x " = " << (x) << std::endl

using namespace rapidjson;

class Myrapidjson
{
public:
	Myrapidjson(){};
	~Myrapidjson(){};
public:
	int  read(const char* jsonfile);//step:1
	int  parse();//step:2

	int    Find(const char* find);
	int    AddMember(const char* Key,const char* Value);
	int    convert_to_string();
	int    ReLoad(const char* jsonfile);
private:
	rapidjson::Document    doc;
	std::string      		stringFromStream;
	std::ifstream    	   in;
	StringBuffer 			buffer;      // in rapidjson/stringbuffer.h
};

int Myrapidjson::read(const char* jsonfile){
    in.open(jsonfile, std::ifstream::in);
    if (!in.is_open())
        return -1;
    std::string line;
    while (getline(in, line)) {
        stringFromStream.append(line + "\n");
    }
    in.close();

    parse();
    return  0;
}
int Myrapidjson::parse(){
    doc.Parse<0>(stringFromStream.c_str());
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        psln(code);
        return -1;
    }
    return 0;
}

int Myrapidjson::Find(const char* find){
	rapidjson::Value::ConstMemberIterator itr = doc.FindMember(find);
	if (itr != doc.MemberEnd()){
		 printf("%s\n", itr->value.GetString());
	}

	return 0;
}

int Myrapidjson::AddMember(const char* key,const char* values)
{
	using rapidjson::Value;
    Value & v = doc["dictVersion"];
    if (v.IsInt()) {
        psln(v.GetInt());
    }

    Value & contents = doc["content"];
    if (contents.IsArray()) {
        for (size_t i = 0; i < contents.Size(); ++i) {
            Value & v = contents[i];
            assert(v.IsObject());
            if (v.HasMember("key") && v["key"].IsString()) {
                psln(v["key"].GetString());
            }
            if (v.HasMember("value") && v["value"].IsString()) {
                psln(v["value"].GetString());
            }
        }
    }
    psln("add a value into array");

    Value Key(rapidjson::kStringType);
    Key.SetString(key,doc.GetAllocator());


    Value StrValue(rapidjson::kStringType);
    StrValue.SetString(values,doc.GetAllocator());


	Value item(Type::kObjectType);
    item.AddMember(Key, StrValue,doc.GetAllocator());
    contents.PushBack(item, doc.GetAllocator());

    //-------
    convert_to_string();
    return  0;
}

int Myrapidjson::convert_to_string(){
    Writer<StringBuffer> writer(buffer); // in rapidjson/writer.h
    doc.Accept(writer);

    psln(buffer.GetString());
    return  0;
}

int Myrapidjson::ReLoad(const char* jsonfile){
	FILE* file = fopen(jsonfile,"wb");
    if (file)
    {
        fputs(buffer.GetString(),file);
        fclose(file);
    }else{
    	psln("ReLoad failed");
    	return -1;
    }
    return  0;
}

int main(int argc, char const *argv[])
{
	Myrapidjson     m_test;

	m_test.read("test.json");

	m_test.AddMember("key","word7");

	m_test.ReLoad("test.json");

	return 0;
}


