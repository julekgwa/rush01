#include <sys/statvfs.h>
#include <iostream>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>
#include <mach/vm_map.h>
#include <sys/types.h>

static unsigned long long _previousTotalTicks = 0;
static unsigned long long _previousIdleTicks = 0;

float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks) {
    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;
    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float) idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);
    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.
float GetCPULoad() {
    host_cpu_load_info_data_t cpuinfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t) &cpuinfo, &count) == KERN_SUCCESS) {
        unsigned long long totalTicks = 0;
        for (int i = 0; i < CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
        return CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
    } else return -1.0f;
}


// ** STEP 1 **
//  "hostname" - (Hostname)
//  "id -un" - (Current user)
//  "system_profiler SPSoftwareDataType" - (System Software Overviwe)
//  "date \"+%H:%M:%S   %d/%m/%y\"" - (Date and Time)
// ** STEP 2 **
//  "sysctl -n machdep.cpu.brand_string" - (CPU make/model)
//  "sysctl -n machdep.cpu.core_count" - (Core count)
//  "ps -A -o %cpu | awk '{s+=$1} END {print s \"%\"}'" - (CPU usage in %)
//  "ps -A -o %mem | awk '{s+=$1} END {print s \"%\"}'" - (MEM usage in %)
//  "id -un | df -h ~" (User Diskuseage)

using namespace std;

int main(int argc, char *argv[]) {


    int mib[2];
    int64_t physical_memory;
    size_t length;

    // Get the Physical memory size
    mib[0] = CTL_HW;
    mib[1] = HW_MACHINE_ARCH;
    length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    sysct
    printf("%lld", physical_memory);
    return 0;
}
