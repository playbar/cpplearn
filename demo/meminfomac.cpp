#include <iostream>

#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>

using namespace std;

enum BYTE_UNITS
{
    BYTES = 0,
    KILOBYTES = 1,
    MEGABYTES = 2,
    GIGABYTES = 3
};

template <class T>
T convert_unit( T num, int to, int from = BYTES)
{
    for( ; from < to; from++)
    {
        num /= 1024;
    }
    return num;
}

void getMemUsePercentage()
{
    u_int64_t total_mem = 0;
    float used_mem = 0;

    vm_size_t page_size;
    vm_statistics_data_t vm_stats;

    // Get total physical memory
    int mib[] = { CTL_HW, HW_MEMSIZE };
    size_t length = sizeof( total_mem );
    sysctl( mib, 2, &total_mem, &length, NULL, 0 );

    mach_port_t mach_port = mach_host_self();
    mach_msg_type_number_t count = sizeof( vm_stats ) / sizeof( natural_t );
    if( KERN_SUCCESS == host_page_size( mach_port, &page_size ) &&
        KERN_SUCCESS == host_statistics( mach_port, HOST_VM_INFO,
                                         ( host_info_t )&vm_stats, &count )
            )
    {
        used_mem = static_cast<float>(
                ( vm_stats.active_count + vm_stats.wire_count ) * page_size);
    }

    uint usedMem = convert_unit(static_cast< float >( used_mem ), MEGABYTES );
    uint totalMem = convert_unit(static_cast< float >( total_mem ), MEGABYTES );
    float value = float((usedMem * 100)/totalMem);
    cout << value << endl;
}

int main()
{
    getMemUsePercentage();
    return 0;
}


