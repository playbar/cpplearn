#include <iostream>
#include "CTest.h"
#include <sys/types.h>
#include <unistd.h>
#include <map>

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