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
    static const char* dextIdentifier = "macUSPCIO";
    
    kern_return_t ret = kIOReturnSuccess;
    io_iterator_t iterator = IO_OBJECT_NULL;
    io_service_t service = IO_OBJECT_NULL;
    io_connect_t connection = IO_OBJECT_NULL;
    /// - Tag: ClientApp_Connect
    ret = IOServiceGetMatchingServices(NULL, IOServiceNameMatching(dextIdentifier), &iterator);
    if (ret != kIOReturnSuccess)
    {
        printf("Unable to find service for identifier with error: 0x%08x.\n", ret);
        PrintErrorDetails(ret);
    }

    printf("Searching for dext service...\n");
    while ((service = IOIteratorNext(iterator)) != IO_OBJECT_NULL)
    {
        // Open a connection to this user client as a server to that client, and store the instance in "service"
        ret = IOServiceOpen(service, mach_task_self_, 0, &connection);

        if (ret == kIOReturnSuccess)
        {
            printf("\tOpened service.\n");
            break;
        }
        else
        {
            printf("\tFailed opening service with error: 0x%08x.\n", ret);
        }

        IOObjectRelease(service);
    }
    IOObjectRelease(iterator);

    if (service == IO_OBJECT_NULL)
    {
        printf("Failed to match to device.\n");
        return EXIT_FAILURE;
    }
    
    return 0;
}
