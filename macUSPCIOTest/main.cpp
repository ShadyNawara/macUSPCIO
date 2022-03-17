#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <IOKit/IOKitLib.h>

#include "macUSPCIOAccess.h"


io_connect_t macUSPCIO_driver_connection;

int main(void)
{
    InitMacUSPCIODriver();
    printf("%i", ReadIoPortByte(0x40));
    CloseMacUSPCIODriver();
    return 0;
}
