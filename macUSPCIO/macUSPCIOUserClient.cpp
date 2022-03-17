//
//  macUSPCIOUserClient.cpp
//  macUSPCIO
//
//  Created by Shady Nawara on 3/15/22.
//

#include "macUSPCIO.h"
#include "macUSPCIOUserClient.h"
#include <IOKit/IOLib.h>
#include <IOKit/assert.h>

#define super IOUserClient
OSDefineMetaClassAndStructors( macUSPCIOUserClient, IOUserClient );

bool macUSPCIOUserClient::init(void)
{
    bool result = false;

    IOLog("macUSPCIOUserClient::init()");

    result = super::init();
    if (result != true)
    {
        IOLog("macUSPCIOUserClient::init() - super::init failed.");
        goto Exit;
    }

    driver = NULL;

    IOLog("macUSPCIOUserClient::init() - Finished.");
    return true;

Exit:
    return false;
}

bool macUSPCIOUserClient::start( IOService * provider )
{
    bool success;
    IOLog("macUSPCIOUserClient::start\n");


    driver = OSDynamicCast(macUSPCIO, provider);
    success = (driver != NULL);

    if (success) {
        // It's important not to call super::start if some previous condition
        // (like an invalid provider) would cause this function to return false.
        // I/O Kit won't call stop on an object if its start function returned false.
        success = super::start(provider);
    }

    return success;
}

void macUSPCIOUserClient::stop( IOService * provider )
{
    super::stop(provider);
}

void macUSPCIOUserClient::free(void)
{
    IOLog("macUSPCIOUserClient::free()");

    super::free();
}

bool macUSPCIOUserClient::initWithTask(task_t owningTask, void *securityToken, UInt32 type, OSDictionary *properties)
{
    bool success;

    success = super::initWithTask(owningTask, securityToken, type, properties);

    // This IOLog must follow super::initWithTask because getName relies on the superclass initialization.
    IOLog("macUSPCIOUserClient::%s[%p]::%s(%p, %p, %u, %p)\n", getName(), this, __FUNCTION__, owningTask, securityToken, (unsigned)type, properties);

    if (success) {
    }

    fTask = owningTask;
    driver = NULL;

    return success;
}

const IOExternalMethodDispatch macUSPCIOUserClient::sMethods[kNumberOfMethods] = {
    {
        (IOExternalMethodAction) &macUSPCIOUserClient::externalPciReadIOByte,    // Method pointer.
        1,                                                // One scalar input values.
        0,                                                // No struct input value.
        1,                                                // One scalar output value.
        0                                                // No struct output value.
    },
    {
        (IOExternalMethodAction) &macUSPCIOUserClient::externalPciWriteIOByte,    // Method pointer.
        2,                                                // One scalar input values.
        0,                                                // No struct input value.
        1,                                                // One scalar output value.
        0                                                // No struct output value.
    },
    {
        (IOExternalMethodAction) &macUSPCIOUserClient::externalPciReadConfigByte,    // Method pointer.
        1,                                                // One scalar input values.
        0,                                                // No struct input value.
        1,                                                // One scalar output value.
        0                                                // No struct output value.
    },
    {
        (IOExternalMethodAction) &macUSPCIOUserClient::externalPciReadConfigWord,    // Method pointer.
        1,                                                // One scalar input values.
        0,                                                // No struct input value.
        1,                                                // One scalar output value.
        0                                                // No struct output value.
    }
};

IOReturn macUSPCIOUserClient::externalMethod(uint32_t selector, IOExternalMethodArguments * arguments, IOExternalMethodDispatch * dispatch, OSObject * target, void * reference )
{
    IOLog("%s[%p]::%s(%d, %p, %p, %p, %p)\n", getName(), this, __FUNCTION__, selector, arguments, dispatch, target, reference);

    if (selector < (uint32_t) kNumberOfMethods) {
        dispatch = (IOExternalMethodDispatch *) &sMethods[selector];
        if (!target) {
            target = driver;
        }
    }
    return super::externalMethod(selector, arguments, dispatch, target, reference);
}

IOReturn macUSPCIOUserClient::externalPciReadIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments)
{
    arguments->scalarOutput[0] = target->pciReadIOByte((UInt16)arguments->scalarInput[0]);
    return kIOReturnSuccess;
}

IOReturn macUSPCIOUserClient::externalPciWriteIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments)
{
    target->pciWriteIOByte((UInt16)arguments->scalarInput[0], (UInt8)arguments->scalarInput[1]);
    return kIOReturnSuccess;
}

IOReturn macUSPCIOUserClient::externalPciReadConfigByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments)
{
    arguments->scalarOutput[0] = target->pciReadConfigByte((UInt16)arguments->scalarInput[0]);
    return kIOReturnSuccess;
}

IOReturn macUSPCIOUserClient::externalPciReadConfigWord(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments)
{
    arguments->scalarOutput[0] = target->pciReadConfigWord((UInt16)arguments->scalarInput[0]);
    return kIOReturnSuccess;
}
