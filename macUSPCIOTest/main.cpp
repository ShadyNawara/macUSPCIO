#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <IOKit/IOKitLib.h>

inline void PrintErrorDetails(kern_return_t ret)
{
    printf("\tSystem: 0x%02x\n", err_get_system(ret));
    printf("\tSubsystem: 0x%03x\n", err_get_sub(ret));
    printf("\tCode: 0x%04x\n", err_get_code(ret));
}


int main(void)
{
    kern_return_t ret;
    io_connect_t conn = 0;
    io_service_t dev = IOServiceGetMatchingService(NULL, IOServiceMatching("macUSPCIO"));
    if (dev) {
        ret = IOServiceOpen(dev, mach_task_self(), 0, &conn);
        if (ret == kIOReturnSuccess) {
            printf("opened service\n");
            uint32_t outputCount = 1;
            uint64_t scalarO_64 = 0;
            uint64_t scalarinput_64[1] = {0x040};
            ret = IOConnectCallScalarMethod(conn, 0, scalarinput_64, 1, &scalarO_64, &outputCount);
            if (ret == 0) {
                printf("result = %x\n", (uint8_t)scalarO_64);
            }
            IOServiceClose(conn);
        }
        IOObjectRelease(dev);
    }
    return 0;
}
