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

bool macUSPCIOUserClient::initWithTask( task_t owningTask, void * securityID, UInt32 type,  OSDictionary * properties )
{
    IOLog("macUSPCIOUserClient::initWithTask(type %u)\n", type);
    
    fTask = owningTask;

    return( super::initWithTask( owningTask, securityID, type, properties ));
}

bool macUSPCIOUserClient::start( IOService * provider )
{
    IOLog("macUSPCIOUserClient::start\n");

    if( !super::start( provider ))
        return( false );

    assert( OSDynamicCast( macUSPCIO, provider ));
    driver = (macUSPCIO *) provider;

    openClientsCount = 1;

    return( true );
}

IOReturn macUSPCIOUserClient::clientClose( void )
{
    if( !isInactive())
        terminate();

    return( kIOReturnSuccess );
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