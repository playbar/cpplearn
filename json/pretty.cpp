// JSON pretty formatting example
// This example can only handle UTF-8. For handling other encodings, see prettyauto example.

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"
#include <rapidjson/document.h>

using namespace rapidjson;



void testParserJson()
{
    //json格式字符串
    // {
    // "name":"qfl",
    // "age":20,
    // "letter":["a","b","c"],
    // "location": {"province":"fujian","city":"xiamen","number":16}
    // "book":[{"name":"book1", "isbn":"123"},{"name":"book2","isbn":"456"}],
    // "healthy":true,
    // }
    const char *json = "{\"name\":\"qfl\", \"age\":20,\"letter\":[\"a\",\"b\",\"c\"],\"location\": {\"province\":\"fujian\",\"city\":\"xiamen\",\"number\":16},\"book\":[{\"name\":\"book1\", \"isbn\":\"123\"},{\"name\":\"book2\",\"isbn\":\"456\"}], \"healthy\":true}";

//    const char *json = "{\"hello\": \"world\",\"t\": true ,\"f\": false,\"n\": null,\"i\": 123,\"pi\": 3.1416,\"a\": [1, 2, 3, 4]}";



    rapidjson::Document newDoc;
//    rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> newDoc;
    newDoc.Parse(json);
    if( newDoc.HasParseError())
    {
        printf("Json Parse error:%d", newDoc.GetParseError());
    }
    else{
        if (newDoc.HasMember("name")) {
            printf("name:%s\n", newDoc["name"].GetString()); //必须要获取对应的数据类型，rapidjson不会帮你转换类型
        }
        else {}

        if (newDoc.HasMember("age")) {
            const rapidjson::Value& value = newDoc["age"];
            printf("age:%d\n", value.GetInt());  //获取正确的类型
        }

        if (newDoc.HasMember("letter")) {
            rapidjson::Value letter;    //使用一个新的rapidjson::Value来存放array的内容
            letter = newDoc["letter"];

            //确保它是一个Array，而且有内容
            if (letter.IsArray() && !letter.Empty()) {
                //遍历Array中的内容
                for (rapidjson::SizeType i = 0; i < letter.Size(); i++) {
                    printf("letter:%s\n", letter[i].GetString());
                }
            }
            else {}
        }

        if (newDoc.HasMember("location")) {
            rapidjson::Value location;      //使用一个新的rapidjson::Value来存放object
            location = newDoc["location"];

            //确保它是一个Object
            if (location.IsObject()) {

                if (location.HasMember("province")) {
                    printf("location:province:%s\n", location["province"].GetString());
                }
                else {}
                if (location.HasMember("city")) {
                    printf("location:city:%s\n", location["city"].GetString());
                }
                else {}
                if (location.HasMember("number")) {
                    printf("location:number:%d\n", location["number"].GetInt());
                }
                else {}
            }
            else {}
        }
        else {}

        //book是一个包含了2个object的array。按照上面的步骤来取值就行
        if (newDoc.HasMember("book")) {
            rapidjson::Value book;
            book = newDoc["book"];

            //先取Array
            if (book.IsArray() && !book.Empty()) {

                rapidjson::Value tempBook;
                for (rapidjson::SizeType i = 0; i < book.Size(); i++) {
                    tempBook = book[i]; //Array中每个元素又是一个Object

                    if (tempBook.IsObject()) {

                        if (tempBook.HasMember("name") && tempBook.HasMember("isbn")) {
                            printf("book:%d:name:%s, isbn:%s\n", i, tempBook["name"].GetString(), tempBook["isbn"].GetString());
                        }
                        else {}
                    }
                    else {}
                }
            }
            else {}
        }
        else {}

        if (newDoc.HasMember("healthy")) {
            if (newDoc["healthy"].GetBool()) {
                printf("healthy:true\n");
            }
            else {
                printf("healthy:false\n");
            }
        }
        else {}
    }

}

int main(int, char*[]) {
    // Prepare reader and input stream.
    testParserJson();
    Reader reader;
    char readBuffer[65536];
    FileReadStream is(stdin, readBuffer, sizeof(readBuffer));

    // Prepare writer and output stream.
    char writeBuffer[65536];
    FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
    PrettyWriter<FileWriteStream> writer(os);

    // JSON reader parse from the input stream and let writer generate the output.
    if (!reader.Parse<kParseValidateEncodingFlag>(is, writer)) {
        fprintf(stderr, "\nError(%u): %s\n", static_cast<unsigned>(reader.GetErrorOffset()), GetParseError_En(reader.GetParseErrorCode()));
        return 1;
    }

    return 0;
}
