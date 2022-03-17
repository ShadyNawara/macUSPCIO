#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <IOKit/IOKitLib.h>

#include "macUSPCIOAccess.h"


io_connect_t macUSPCIO_driver_connection;

int main(void)
{
    InitMacUSPCIODriver();
    printf("Vendor Id: %x\n", ReadConfigPortWord(0x00));
    printf("Device Id: %x\n", ReadConfigPortWord(0x02));
    printf("Subsystem Vendor Id: %x\n", ReadConfigPortWord(0x2c));
    printf("Subsystem Id: %x\n", ReadConfigPortWord(0x2e));
    CloseMacUSPCIODriver();
    return 0;
}
