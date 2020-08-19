
#include <printf.h>
#include <string>
#include <vector>

double calScale(int minl, int maxl, double maxScale)
{
    return maxScale / (1 << (maxl - minl));
}

void test1(){
    int data[] = {
            131093,
            131082,
            131083,
            131084,
            131088,
            131089,
            131094,
            131329,
            131330,
            131331,
            131332,
            131333,
            131334,
            131335,
            131336,
            131337,
            131338,
            131339,
            131340,
            131341,
            131098,
            131342,
            131344,
            131099,
            131102,
            131103,
            131106,
            131107,
            131110,
            131111,
            131115
    };

    int len = sizeof(data)/sizeof(data[0]);
    for( int i = 0; i < len; ++i ){
        int a = data[i] & 0xFFFF;
        printf("%d,   %d \n", a, data[i]);
    }
    return;
}

void split_str(const std::string & src, std::vector<std::string> & vec_str, const std::string & sep)
{
    std::string::size_type start = 0;
    for (std::string::size_type end = src.find(sep, start); end != std::string::npos; end = src.find(sep, start))
    {
        //if (end > start)
        {
            std::string sub = src.substr(start, end - start);
            vec_str.push_back(sub);
        }
        start = end + sep.length();
    }
    //if (start < src.length())
    {
        vec_str.push_back(src.substr(start, src.length() - start));
    }
}

void testsscanf(){
    char https[6] = {0};
    char urls[256] = {0};
    int df = 0;
    int idx = 0;
    int lv = 0;
    int bn = 0;
    int pvr = 0;
    int lyr = 0;
    int ver = 0;
    int nd = 0;
    int lug = 0;
    int nation = 0;
    const char *urlString = "https://map.baidu.com/mapserver?df=1&idx=397131&lv=6&bn=124&pvr=4&lyr=7&ver=0&nd=2&lug=0&nation=0";
    std::vector<std::string> vec_temp;
    split_str(urlString, vec_temp, "&");

    sscanf(vec_temp[6].c_str(), "ver=%d", &ver);
    sscanf(vec_temp[8].c_str(), "lug=%d", &lug);
    sscanf(vec_temp[9].c_str(), "nation=%d", &nation);

    char http[30] = {0};
    char buf[512] = {0};
    int num = 0;
    sscanf("https://www.test.com?num=500", "%*\?num=%d", &num);
    printf("%s\n", buf);

    sscanf(urlString, "%s://%s?df=1&idx=%d&lv=%d&bn=%d&pvr=%d&lyr=%d&ver=%d&nd=%d&lug=%d&nation=%d", https, urls,
           &df, &idx, &lv, &bn, &pvr, &lyr, &ver, &nd, &lug, &nation);


}

int main()
{
    testsscanf();
    test1();
    int  sl = 23;
    double maxs = 1 << 5;
    double mins = calScale(4, 25, maxs);
    double scale = mins * (1 << (sl - 4));

    char *pdata = "\0x89\0x54";


    printf("scale = %lf, pdata = %s\n", scale, pdata);
    return 0;

}