#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>

#include "utils.h"


std::string CUtils::extension(const std::string &filename)
{
    size_t pos = filename.rfind('.');
    if (pos != std::string::npos)
    {
        std::string substr = filename.substr(pos + 1);
        toLowercase(substr);
        return substr;
    }
    else
        return "";
}

std::string CUtils::stripExtension(const std::string &filename)
{
    size_t pos = filename.rfind('.');
    if (pos != std::string::npos)
        return filename.substr(0, pos);
    else
        return filename;
}

std::string CUtils::filename(const std::string &filepath)
{
    size_t pos = filepath.find_last_of("\\/");
    if (pos != std::string::npos)
        return filepath.substr(pos + 1);
    return filepath;
}

void CUtils::split(const std::string &src, char delim, std::vector<std::string> &des)
{
    std::stringstream srcStream(src);
    std::string item;
    while (std::getline(srcStream, item, delim))
        des.push_back(item);
}

std::string CUtils::lowercase(const std::string &str)
{
    std::string ret = str;
    size_t size = ret.size();
    for(size_t i = 0; i < size; ++i)
    {
        if (ret[i] >= 'A' && ret[i] <= 'Z')
            ret[i] += 32;
    }
    return ret;
}

std::string CUtils::uppercase(const std::string &str)
{
    std::string ret = str;
    size_t size = ret.size();
    for(size_t i = 0; i < size; ++i)
    {
        if(ret[i] >= 'a' && ret[i] <= 'z')
            ret[i] -= 32;
    }
    return ret;
}

void CUtils::toLowercase(std::string &str)
{
    size_t size = str.size();
    for (size_t i = 0; i < size; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

void CUtils::toUppercase(std::string &str)
{
    size_t size = str.size();
    for (size_t i = 0; i < size; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

std::string CUtils::calc_md5(unsigned char *encrypt, unsigned int length)
{
    std::string md5Str;
    unsigned char decrypt[16] = {0};
    char dec[4] = {0};
    md5_data md5;
    md5_init(&md5);
    md5_update(&md5,(unsigned char*)encrypt,length);
    md5_final(&md5,decrypt);
    for(int i=0;i<16;i++)
    {
        snprintf(dec, 4, "%02x", decrypt[i]);
        md5Str += dec;
    }
    
    return md5Str;
}

void CUtils::printfTime(long time,std::string word)
{
    char str_time[100];
    struct tm *local_time = NULL;
    time_t utc_time;
    utc_time = time;
    local_time = localtime(&utc_time);
    strftime(str_time, sizeof(str_time), "%Y-%m-%d,%H:%M:%S", local_time);
    printf("%s: %s\n", str_time, word.c_str());
}

long CUtils::getCurrentTime()
{
    time_t nowtime;
    nowtime = time(NULL);
    
    return (long)nowtime;
}

long CUtils::getCurrentTimeMS()
{
    struct timeval now;
    gettimeofday(&now,NULL);
    return now.tv_sec*1000L+now.tv_usec/1000L;
}

long CUtils::getLastModifyTime(std::string path)
{
    struct stat buf;
    if (lstat(path.c_str(), &buf)) {
        printf("Dec error load file state: %s\n", path.c_str());
        return (long)0;
    }
    
    return (long)buf.st_ctime;
}


void CUtils::list_dir_files(const std::string &path, std::vector<string> &files)
{
    DIR* dir;
    struct dirent* ptr;
    dir = opendir(path.c_str());
    
    if (dir == NULL)
        return;
    
    while ( (ptr = readdir(dir)) != NULL ) {
        files.push_back(ptr->d_name);
    }
    
    closedir(dir);
}





