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

int main() {
    testmap();
    testStr();
    CTest a;
    std::cout << "Hello, World!" << std::endl;
    pid_t pid = getpid();
    depth_1();
    return 0;
}