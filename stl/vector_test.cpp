//
// Created by hou guoli on 2019/1/8.
//

#include <mach/task_info.h>
#include <mach/mach_init.h>
#include <mach/task.h>
#import  <mach/mach.h>
#include "vector"
#include "myalloc.h"
#include "vector_test.h"

#import <sys/types.h>
#import <sys/sysctl.h>
#import <mach/host_info.h>
#import <mach/mach_host.h>
#import <mach/task_info.h>
#import <mach/task.h>


using namespace std;

void testBlockItem(){
    int len = sizeof(DataItem);
    DataItem a[2];
    a[0].tileX = 1;
    a[0].tileY = 1;
    memcpy(a[0].etag, "DataItem", sizeof(a[0].etag));

    DataItem b = a[0];
    std::cout<<a[0].etag<<&a[0].etag<<std::endl;
    std::cout<<b.etag<<&b.etag<<std::endl;

}

void testVector()
{
    std::vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = idata.size()-1; j>= 0; --j)
    {
        std::cout<<idata[j]<<std::endl;
        idata.erase(idata.begin() + j);
    }
    std::cout<<__FUNCTION__ <<std::endl;
}

void testVector1()
{
    std::vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = 0; j < idata.size(); ++j)
    {
        std::cout<<idata[j]<<std::endl;
        idata.erase(idata.begin() + j);

    }
}

struct squareXY{
    int x;
    int y;
};

void testVector2()
{
    squareXY rexy = {6, 7};
    squareXY xy = {2, 3};

    std::vector<squareXY> s(10, xy);
    std::vector<squareXY> res(10, rexy);

    s.resize(5, rexy);
    s = res;

    return;
}

void testVector3()
{
    std::vector<int> v2;
    int nums = 20;
    for (int i = 0; i < nums; ++i){
        v2.push_back(i+1);
        std::cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << std::endl;
    }


}

void testVector4()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    v1.resize(200);
    v2.reserve(200);
    v3.reserve(200);
    v4.resize(200);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v2.clear();
    v2.push_back(99);
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;

}

void testVector5()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity()<<endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v2.push_back(99);
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;

    int nums = 20;
    for (int i = 0; i < nums; ++i){
        v2.push_back(i+1);
        cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    }

    cout << endl;

    v1.resize(100);
    v2.resize(100);
    v2.push_back(99);   // 添加一个元素

    v3.reserve(100);
    v4.reserve(100);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v1.resize(200);
    v2.reserve(200);
    v3.reserve(200);
    v4.resize(200);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v4.push_back(8);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    return;
}

void testVector6(int size)
{
//    float *pfdata = new float[size];

    vector<string, cpl::allocator<string>> vecf;
    vecf.reserve(size);
    for( int i = 0; i  < size; ++i )
    {
        char sz[200] = {0};
        sprintf(sz, "File:%s, %d", __FILE__,  i);
//        vecf[i] = i;
//        vecf.emplace_back(i);
        printf("Fun:%s, index = %d \n", __FUNCTION__, i);
        vecf.push_back(sz);
//        pfdata[i] = i;
    }


    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;

//    vecf.clear();
    {
//        vector<float> vecfswap;
//        vecfswap.swap(vecf);
    }
//    vecf.resize(1);
    vecf.shrink_to_fit();
//
//    delete pfdata;
    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;

}

void myalloctest()
{
    int arr[5] = { 0, 1, 2, 3, 4 };
    //unsigned int i;
    cpl::allocator<int> test;
    cpl::allocator<int> test1;

    vector<int, cpl::allocator<int>>iv(arr, arr + 5);
    for (int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;
}

float getValue()
{
    int64_t memoryUsageInByte = 0;
    task_vm_info_data_t vmInfo;
    mach_msg_type_number_t count = TASK_VM_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_VM_INFO, (task_info_t) &vmInfo, &count);
    if (kernReturn != KERN_SUCCESS)
    {
        return 0.0f;
    }
    memoryUsageInByte = (int64_t) vmInfo.phys_footprint;
    return memoryUsageInByte/1024.0/1024.0;
}


int64_t getMemInfo()
{
    int64_t memoryUsageInByte = 0;
    task_vm_info_data_t vmInfo;
    mach_msg_type_number_t count = TASK_VM_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_VM_INFO, (task_info_t) &vmInfo, &count);
    if (kernReturn != KERN_SUCCESS)
    {
        return 0;
    }
    memoryUsageInByte = (int64_t) vmInfo.phys_footprint;
    return memoryUsageInByte;
}


int logMemoryInfo()
{
    int mib[6];
    mib[0] = CTL_HW;
    mib[1] = HW_PAGESIZE;

    int pagesize;
    size_t length;
    length = sizeof (pagesize);
    if (sysctl (mib, 2, &pagesize, &length, NULL, 0) < 0)
    {
        fprintf (stderr, "getting page size");
    }

    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;

    vm_statistics_data_t vmstat;
    if (host_statistics (mach_host_self (), HOST_VM_INFO, (host_info_t) &vmstat, &count) != KERN_SUCCESS)
    {
        fprintf (stderr, "Failed to get VM statistics.");
    }
    task_basic_info_64_data_t info;
    unsigned size = sizeof (info);
    task_info (mach_task_self (), TASK_BASIC_INFO_64, (task_info_t) &info, &size);

    double unit = 1024 * 1024;
    double total = (vmstat.wire_count + vmstat.active_count + vmstat.inactive_count + vmstat.free_count) * pagesize / unit;
    double wired = vmstat.wire_count * pagesize / unit;
    double active = vmstat.active_count * pagesize / unit;
    double inactive = vmstat.inactive_count * pagesize / unit;
    double free = vmstat.free_count * pagesize / unit;
    double resident = info.resident_size / unit;
    printf("===================================================");
    printf("Total:%.2lfMb \n", total);
    printf("Wired:%.2lfMb \n", wired);
    printf("Active:%.2lfMb \n", active);
    printf("Inactive:%.2lfMb \n", inactive);
    printf("Free:%.2lfMb \n", free);
    printf("Resident:%.2lfMb \n", resident);
}



int64_t getFreeMemInfo()
{
    int64_t memoryUsageInByte = 0;
    task_kernelmemory_info_data_t vmInfo;
    mach_msg_type_number_t count = TASK_KERNELMEMORY_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_KERNELMEMORY_INFO, (task_info_t) &vmInfo, &count);
    if (kernReturn != KERN_SUCCESS)
    {
        return 0.0f;
    }
    memoryUsageInByte = (int64_t) vmInfo.total_sfree;
    return memoryUsageInByte;
}

// 获取当前任务所占用的内存（单位：MB）

double getUsedMemory()
{
    task_basic_info_data_t info;
    mach_msg_type_number_t size = sizeof(info);
    kern_return_t kerr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size);

    if (kerr == KERN_SUCCESS) {
        return info.resident_size / 1000.0 / 1000.0;
    } else {
        return 0;
    }
}

double getFreeMemory()
{
    mach_port_t host = mach_host_self();
    mach_msg_type_number_t size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t pagesize;
    vm_statistics_data_t vmstat;

    host_page_size(host, &pagesize);
    host_statistics(host, HOST_VM_INFO, (host_info_t) &vmstat, &size);

    return (vmstat.free_count * pagesize) / 1000.0 / 1000.0;
}


void testVector7(int size)
{
    vector<string*> vecf;
    vecf.reserve(size);
    for( int i = 0; i  < size; ++i )
    {
        char sz[200] = {0};
//        sprintf(sz, "File:%s, Fun:%s, index = %d \n", __FILE__,  __FUNCTION__, i);
        printf(sz);
        string *str = new string(sz);
        vecf.push_back(str);

    }


    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;

    for( int i = 0; i < vecf.size(); ++i )
    {
        delete vecf[i];
    }
    vecf.clear();
    {
        vector<string*> vecfswap;
        vecfswap.swap(vecf);
    }
//    vecf.resize(1);
//    vecf.shrink_to_fit();
    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;
    printf("meminfo:%f M\n", getValue());

}


std::vector<DataItem> testvector()
{
    int i = 45;
    int&& iii = std::move(i);
    std::vector<DataItem> ivecs;
    for( int i = 0; i < 1000; ++i )
    {
        DataItem item;
        item.tileX = i + 1;
//        ivecs.push_back(item);
        int64_t memInfo0 = getMemInfo();
        ivecs.emplace_back(item);
        int64_t memInfo1 = getMemInfo();
        printf("memInfo = %d\n", (int)(memInfo1 - memInfo0));
//        ivecs.emplace_back({1, 1,""});
    }
    std::vector<DataItem> ivecs2;
    ivecs2 = std::move(ivecs);
    return ivecs2;
}

void testMemInfo()
{
    std::vector<int *> ivecs;
    for( int i = 0; i < 1000; ++i )
    {
        int64_t mem1 =  getMemInfo();
        int *idata = new int(i+1);
        ivecs.push_back(idata);
        int64_t mem2 = getMemInfo();
        printf("mem : %d, toatl mem = %f M \n", (int)(mem2 - mem1), getValue());
    }



}

int main()
{
    testMemInfo();
    std::vector<DataItem> re = testvector();
    printf("meminfo:%f M\n", getValue());
    testVector7(1024 * 100);
    printf("meminfo:%f M\n", getValue());

    logMemoryInfo();

    double mem = getMemInfo();
    double usedMem = getUsedMemory();
    double avaMem = getFreeMemInfo();
    printf("meminfo = %lf M, useMem = %lf M, avaMem = %lf M\n", mem, usedMem, avaMem );

    myalloctest();
//    testVector6(20 * 1024 * 1024);
    testVector4();
    testVector5();
    printf("meminfo:%f M \n", getValue());
//    unsigned int ia = 0xFFFFFFFF;
//    float fa = ia;
//    int flen = sizeof( float);
//    testBlockItem();
//    testVector();
//    testVector1();


    return 0;
}