//
//  macUSPCIO.h
//  macUSPCIO
//
//  Created by Shady Nawara on 3/15/22.
//

#ifndef macUSPCIO_h
#define macUSPCIO_h

#include <IOKit/pci/IOPCIDevice.h>
#include "macUSPCIOShared.h"

class macUSPCIO : public IOService
{
    OSDeclareDefaultStructors( macUSPCIO );

private:
    // ignoring deprecated warning as the new driverkit doesnot support IO access
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    
    IOPCIDevice* pci_device;
    
#pragma GCC diagnostic pop
    
    
public:
    /* IOService overrides */
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    
    /*
     * Reads a byte from the pci device io space at a given address
     * and returns the value
     */
    UInt8 pciReadIOByte(UInt16 address);
    
    /*
     * Writes a byte to the pci device io space at a given address
     * and value
     */
    void pciWriteIOByte(UInt16 address, UInt8 value);
    
    /*
     * Reads a byte from the pci device config space at a given address
     * and returns the value
     */
    UInt8 pciReadConfigByte(UInt16 address);
    
    /*
     * Reads a byte from the pci device config space at a given address
     * and returns the value
     */
    UInt16 pciReadConfigWord(UInt16 address);
};


#endif /* macUSPCIO_h */
