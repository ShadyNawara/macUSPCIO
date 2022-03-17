//
//  macUSPCIO.cpp
//  macUSPCIO
//
//  Created by Shady Nawara on 3/15/22.
//

#include "macUSPCIO.h"
#include <IOKit/IOLib.h>
#include <IOKit/assert.h>

#define super IOService
OSDefineMetaClassAndStructors( macUSPCIO, IOService );

bool macUSPCIO::start( IOService * provider )
{
    IOLog("macUSPCIO::start\n");

    if( !super::start( provider ))
        return( false );

    /*
     * Our provider class is specified in the driver property table
     * as IOPCIDevice, so the provider must be of that class.
     * The assert is just to make absolutely sure for debugging.
     */

    assert( OSDynamicCast( IOPCIDevice, provider ));
    
    // ignoring deprecated warning as the new driverkit doesnot support IO access
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    
    pci_device = (IOPCIDevice *) provider;
    
#pragma GCC diagnostic pop
    
    /*
     * Enable IO Access
     */
    pci_device->setIOEnable(true);
    
    pci_device->retain();
    if (!pci_device->open(this)) {
        IOLog("%s::%s Could not open provider", getName(), pci_device->getName());
        return false;
    }

    /* publish ourselves so clients can find us */
    registerService();

    return( true );
}

void macUSPCIO::stop(IOService * provider)
{
    IOLog("%s::stop\n", getName());
    
    pci_device->close(this);
    super::stop(provider);
}

UInt8 macUSPCIO::pciReadIOByte(UInt16 address)
{
    UInt8 res = pci_device->ioRead8(address);
    return res;
}

void macUSPCIO::pciWriteIOByte(UInt16 address, UInt8 value)
{
    pci_device->ioWrite8(address, value);
}

UInt8 macUSPCIO::pciReadConfigByte(UInt16 address)
{
    UInt8 res = pci_device->configRead8(address);
    return res;
}

UInt16 macUSPCIO::pciReadConfigWord(UInt16 address)
{
    UInt16 res = pci_device->configRead16(address);
    return res;
}
