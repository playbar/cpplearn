#include <cstdio>
#include "unistd.h"

//通过获取/proc/stat (CPU)和/proc/meminfo(内存和硬盘)文件信息
//proc/meminfo文件结构
//MemTotal:       515164 kB
//MemFree:         15024 kB
//Buffers:         13740 kB
//Cached:         248824 kB
//SwapCached:    960 kB
//Active:         309980 kB
//Inactive:       63420 kB
typedef struct MEMPACKED         //定义一个mem occupy的结构体
{
    char name1[20];      //定义一个char类型的数组名name有20个元素
    unsigned long MemTotal;
    char name2[20];
    unsigned long MemFree;
    char name3[20];
    unsigned long Buffers;
    char name4[20];
    unsigned long Cached;
    char name5[20];
    unsigned long SwapCached;
}MEM_OCCUPY;

//proc/stat文件结构
//cpu  633666 46912 249878 176813696 782884 2859 19625 0
//cpu0 633666 46912 249878 176813696 782884 2859 19625 0
//intr 5812844
//ctxt 265816063
//btime 1455203832
//processes 596625
//procs_running 1
//procs_blocked 0

typedef struct CPUPACKED         //定义一个cpu occupy的结构体
{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned int user; //定义一个无符号的int类型的user
    unsigned int nice; //定义一个无符号的int类型的nice
    unsigned int system;//定义一个无符号的int类型的system
    unsigned int idle; //定义一个无符号的int类型的idle
    unsigned int lowait;
    unsigned int irq;
    unsigned int softirq;
}CPU_OCCUPY;


void get_memoccupy(MEM_OCCUPY *mem) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    char buff[256];
    MEM_OCCUPY *m;
    m = mem;

    fd = fopen("/proc/meminfo", "r");
    //MemTotal: 515164 kB
    //MemFree: 7348 kB
    //Buffers: 7892 kB
    //Cached: 241852  kB
    //SwapCached: 0 kB
    //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %lu ", m->name1, &m->MemTotal);
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %lu ", m->name2, &m->MemFree);
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %lu ", m->name3, &m->Buffers);
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %lu ", m->name4, &m->Cached);
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %lu", m->name5, &m->SwapCached);

    fclose(fd);     //关闭文件fd
}


int get_cpuoccupy(CPU_OCCUPY *cpust) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy = cpust;

    fd = fopen("/proc/stat", "r");
    fgets(buff, sizeof(buff), fd);

    sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle, &cpu_occupy->lowait, &cpu_occupy->irq, &cpu_occupy->softirq);


    fclose(fd);

    return 0;
}


int cal_cpuoccupy(CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    unsigned long od, nd;
    double cpu_use = 0;

    od = (unsigned long)(o->user + o->nice + o->system + o->idle + o->lowait + o->irq + o->softirq);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (unsigned long)(n->user + n->nice + n->system + n->idle + n->lowait + n->irq + n->softirq);//第二次(用户+优先级+系统+空闲)的时间再赋给od
    double sum = nd - od;
    double idle = n->idle - o->idle;
    cpu_use = idle / sum;
    printf("cpu_use1(idle) = %f\r\n", cpu_use);
    idle = n->user + n->system + n->nice - o->user - o->system - o->nice;
    cpu_use = idle / sum;
    printf("cpu_use2(user+system+nice) = %f\r\n", cpu_use);
    return 0;
}

int main( int argc, char **argv )
{
    MEM_OCCUPY mem_stat;
    CPU_OCCUPY cpu_stat1;
    CPU_OCCUPY cpu_stat2;

//获取内存
    get_memoccupy((MEM_OCCUPY *)&mem_stat);
    printf(" [MemTotal] = %lu \n [MemFree] = %lu \n [Buffers] = %lu \n [Cached] = %lu \n [SwapCached] = %lu \n", mem_stat.MemTotal, mem_stat.MemFree, mem_stat.Buffers, mem_stat.Cached, mem_stat.SwapCached);

//第一次获取cpu使用情况
    get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);
    sleep(1000);
//第二次获取cpu使用情况
    get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);
//计算cpu使用率
    cal_cpuoccupy((CPU_OCCUPY *)&cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);

}


