#include <iostream>
#include "CTest.h"
#include <sys/types.h>
#include <unistd.h>
#include <map>
#include <fcntl.h>

/*
 * open函数用来打开一个设备，他返回的是一个整型变量，如果这个值等于-1，说明打开文件出现错误，如果为大于0的值
 参考格式 if(fd=open("/dev/ttys0",O_RDWR | O_NOCTTY | O_NDELAY))<0 {printf("cannot open"};
 int open(const char *pathname, int oflag, …/*, mode_t mode * / ) ;
 打开的操作类型有如下几种
   1) O_RDONLY 只读打开
   2) O_WRONLY 只写打开
   3) O_RDWR 读、写打开
   4) O_APPEND 每次写时都加到文件的尾端
   5) O_CREAT 若此文件不存在则创建它。使用此选择项时，需同时说明第三个参数mode，用其说明该新文件的存取许可权位。
   6) O_EXCL 如果同时指定了O_CREAT，而文件已经存在，则出错。这可测试一个文件是否存在，如果不存在则创建此文件成为一个原子操作。
   7) O_TRUNC 如果此文件存在，而且为只读或只写成功打开，则将其长度截短为0。
   8) O_NOCTTY 如果p a t h n a m e指的是终端设备，则不将此设备分配作为此进程的控制终端。
   9) O_NONBLOCK 如果p a t h n a m e指的是一个F I F O、一个块特殊文件或一个字符特殊文件，则此选择项为此文件的本次打开操作和后续的I / O操作设置非阻塞方式。
   10)O_SYNC 使每次w r i t e都等到物理I / O操作完成。
   这些控制字都是通过“或”符号分开（|）
 */
void testopenfile()
{
    const std::string param_file = "version.txt";
    int fd = open("/dev/ttys0",O_RDWR | O_NOCTTY | O_NDELAY);
    int fd1 = open(param_file.c_str(), O_RDONLY);
    if( fd < 0 )
    {
        printf("cannot open");
    } else{
        printf("fd : %d \n", fd);
    }
    return;
}

void testmap()
{
    map<person,int> m;
    person p1("Tom1",20);
    person p2("Tom2",22);
    person p3("Tom3",22);
    person p4("Tom4",23);
    person p5("Tom5",24);
    m.insert(make_pair(p3, 100));
    m.insert(make_pair(p4, 100));
    m.insert(make_pair(p5, 100));
    m.insert(make_pair(p1, 100));
    m.insert(make_pair(p2, 100));

    for(map<person, int>::iterator iter = m.begin(); iter != m.end(); iter++)
    {
        cout<<iter->first.name<<"\t"<<iter->first.age<<endl;
    }
    return;
}

void testStr()
{
    char line[] = "selinuxfs /sys/fs/selinux selinuxfs rw,relatime 0 0";
    if (strstr(line, "selinuxfs")) {
        strtok(line, " ");
        char* selinux_dir = strtok(NULL, " ");
        char* selinux_path = strcat(selinux_dir, "/enforce");
        FILE* fp_selinux = fopen(selinux_path, "w");
        char* buf = "0"; // set selinux to permissive
        printf("fp_selinux:%0x", fp_selinux);
        fwrite(buf, strlen(buf), 1, fp_selinux);
        fclose(fp_selinux);
    }
    return;
}

struct Rect
{
    int left;
    int top;
    int right;
    int bottom;
};

int rect_intersects_rect(Rect rect1, Rect rect2) {
    return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top);

}

size_t SysStrlcpy(char *dst, const char *src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0) {
        while (--n != 0) {
            if ((*d++ = *s++) == '\0')
                break;
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0) {
        if (siz != 0)
            *d = '\0';		/* NUL-terminate dst */
        while (*s++)
            ;
    }

    return(s - src - 1);	/* count does not include NUL */
}

int main() {
    testopenfile();
    char *pdata = "abcdefg";
    char temp[30];
    SysStrlcpy(temp, pdata, 30);
    Rect rect1 = {361, 468, 393, 500};
    Rect rect2 = {362, 469, 392, 499};
    Rect rect3 = { 10, 10, 40, 40};
    Rect rect4 = {350, 469, 392, 499};

    int re = rect_intersects_rect(rect1, rect4);

    testmap();
    testStr();
    CTest a;
    std::cout << "Hello, World!" << std::endl;
    pid_t pid = getpid();
    depth_1();
    return 0;
}