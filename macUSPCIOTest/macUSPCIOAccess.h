//
//  macUSPCIOAccess.h
//  Access methods for macUSPCIO
//
//  Created by Shady Nawara
//  MacUSPCIO: https://github.com/ShadyNawara/macUSPCIO
//

#ifndef macUSPCIOAccess_h
#define macUSPCIOAccess_h

#include <IOKit/IOKitLib.h>

extern io_connect_t macUSPCIO_driver_connection;

bool InitMacUSPCIODriver() {
    if(macUSPCIO_driver_connection) {
        return true;
    }
    
    io_service_t dev = IOServiceGetMatchingService(NULL, IOServiceMatching("macUSPCIO"));
    if (dev) {
        kern_return_t ret = IOServiceOpen(dev, mach_task_self(), 0, &macUSPCIO_driver_connection);
        IOObjectRelease(dev);
        return ret == kIOReturnSuccess;
    }
    return false;
}

void CloseMacUSPCIODriver() {
    if(macUSPCIO_driver_connection) {
        IOServiceClose(macUSPCIO_driver_connection);
    }
}

uint8_t macUSPCIOReadIOByte(uint16_t address) {
    uint32_t outputCount = 1;
    uint64_t output = 0;
    uint64_t input[1] = {address};
    
    IOConnectCallScalarMethod(macUSPCIO_driver_connection, 0, input, 1, &output, &outputCount);
        
    return (uint8_t)output;
}

void macUSPCIOWriteIOByte(uint16_t address, uint8_t value) {
    uint32_t outputCount = 1;
    uint64_t output = 0;
    uint64_t input[2] = {address, value};
    
    IOConnectCallScalarMethod(macUSPCIO_driver_connection, 1, input, 2, &output, &outputCount);
}

uint8_t macUSPCIOReadConfigByte(uint16_t address) {
    uint32_t outputCount = 1;
    uint64_t output = 0;
    uint64_t input[1] = {address};
    
    IOConnectCallScalarMethod(macUSPCIO_driver_connection, 2, input, 1, &output, &outputCount);
        
    return (uint8_t)output;
}

uint16_t macUSPCIOReadConfigWord(uint16_t address) {
    uint32_t outputCount = 1;
    uint64_t output = 0;
    uint64_t input[1] = {address};
    
    IOConnectCallScalarMethod(macUSPCIO_driver_connection, 3, input, 1, &output, &outputCount);
        
    return (uint16_t)output;
}


#endif /* macUSPCIOAccess_h */
