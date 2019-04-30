#ifndef __TEST_UTILS__
#define __TEST_UTILS__

#include <string>
#include <vector>
#include <time.h>
#include "math.h"
#include "md5.h"

using namespace std;

class CUtils
{
public:
    
    template <typename T>
    static T log2(T v);
    // static float log2f(float v);
    
    template <typename T>
    static int sign(T x);

    // Format char messages to a string.
    static std::string  format(const char* formats, ...);
    
    // get the lowercase of a string.
    static std::string  lowercase(const std::string &str);
    // get the uppercase of a string.
    static std::string  uppercase(const std::string &str);
    // change a string to lowercase.
    static void         toLowercase(std::string &str);
    // change a string to uppercase.
    static void         toUppercase(std::string &str);
    
    static void split(const std::string &src, char delim, std::vector<std::string> &des);
    
    // get the lowercase extension of a string filename.
    static std::string    extension(const std::string &filename);
    static std::string  stripExtension(const std::string &filename);
    static std::string  filename(const std::string &filepath);
    
    template <typename T>
    static T* strAllocAndCopy(const T *src);
    template <typename T>
    static void SysFree(T *des);
    
    // get File Path for a specified file.
    // static std::string  getFilePath(const std::string &filename);
    
    static unsigned int getMilliseconds();
    
    static unsigned int getMicroseconds();
    
    static unsigned int nextPowerOfTwo(unsigned int x);
    
    static bool isPowerOfTwo(unsigned int x);
    
    template <typename T, typename F>
    static T mix(T x, T y, F a);
    
    static float levelFilter(float x0, float x1, float levelRatio);
    
    static float iconScale(float zDepth, float eyeCenterDistance, float minScale = 0.5f);
    
    static void sleep(double seconds);


    static unsigned int bkdr_hash(const void *key, size_t len);

    static unsigned int ap_hash(const void *key, size_t len);
    
    // static MapGetFilePath mCallBack_GetFilePath;
    
    // generate md5
    static std::string calc_md5(unsigned char *encrypt, unsigned int length);
    
    // get file time
    static long getCurrentTime();
    static long getCurrentTimeMS();
    static long getLastModifyTime(std::string path);
    static void printfTime(long time,std::string word);
    
    // list dir files
    static void list_dir_files(const std::string &path, std::vector<string> &files);
};


/////////////////////////////////////////////////////////////////////////

template <>
inline float CUtils::log2(float v)
{
    return logf(v) * 1.4426950408889634f;
}

template <typename T>
inline T CUtils::log2(T v)
{
    return log(v) * 1.4426950408889634;
}

template <typename T>
inline int CUtils::sign(T x)
{
    return (x > 0) - (x < 0);
}



inline std::string CUtils::format(const char* formats, ...)
{
    char szBuffer[4096];
    va_list args;
    va_start(args, formats);
    vsprintf(szBuffer, formats, args);
    va_end(args);
    return szBuffer;
}

inline unsigned int CUtils::getMilliseconds()
{
    return (unsigned int)(float)(clock() / ((float)CLOCKS_PER_SEC / 1000.0));
}

inline unsigned int CUtils::getMicroseconds()
{
    return (unsigned int)(float)(clock() / ((float)CLOCKS_PER_SEC / 1000000.0));
}

inline unsigned int CUtils::nextPowerOfTwo(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

template <typename T, typename F>
inline T CUtils::mix(T x, T y, F a)
{
    F one(1);
    return x * (one - a) + y * a;
}

inline bool CUtils::isPowerOfTwo(unsigned int x)
{
    return ((x != 0) && !(x & (x - 1)));
}

inline float CUtils::iconScale(float zDepth, float eyeCenterDistance, float minScale)
{
    zDepth = std::max(zDepth, eyeCenterDistance);   // no expanding
    float scale = eyeCenterDistance / zDepth;
    // scale = 1.0f - (1.0f - scale);// * 0.64f;
    scale = std::max(scale, minScale);
    return scale;
}

inline float CUtils::levelFilter(float x0, float x1, float levelRatio)
{
    if (x1 > 0.0f && x0 > 0.0f)
        return powf(x1 / x0, levelRatio) * x0;
    return x1 * levelRatio + x0 * (1.0f - levelRatio);
}

inline void CUtils::sleep(double seconds)
{
    struct timespec tim;
    tim.tv_sec = int(seconds);
    tim.tv_nsec = (seconds - (int)seconds) * 1000000000;
    if (nanosleep(&tim, NULL) < 0)
    {
        printf("nano sleep call failed!\n");
    }
};

template <typename T>
inline T* CUtils::strAllocAndCopy(const T *src)
{
    const T *p = src;
    while (*p != 0) ++p;
    size_t size = sizeof(T) * (p - src + 1);
    T *des = (T*)malloc(size);
    SysMemcpy(des, src, size);
    return des;
}

template <typename T>
inline void CUtils::SysFree(T *des)
{
    free((void*)des);
}

inline unsigned int CUtils::bkdr_hash(const void *key, size_t len)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    unsigned char *p = (unsigned char *)key;
    
    for (int i = 0; i < len; ++i)
        hash = hash * seed + p[i];
    
    return (hash & 0x7FFFFFFF);
}

inline unsigned int  CUtils::ap_hash(const void *key, size_t len)
{
    unsigned int hash = 0;
    unsigned char *p = (unsigned char *)key;
    
    for (int i = 0; i < len; ++i)
    {
        if ((i & 1) == 0)
            hash ^= ((hash << 7) ^ (p[i]) ^ (hash >> 3));
        else
            hash ^= (~((hash << 11) ^ (p[i]) ^ (hash >> 5)));
    }
    return (hash & 0x7FFFFFFF);
}
#endif

