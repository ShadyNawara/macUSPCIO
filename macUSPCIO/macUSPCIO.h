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

#define BIT(nr) (1UL << (nr))
#define SMBHSTCFG               0x040
#define SMBHSTCFG_HST_EN        BIT(0)

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
};


#endif /* macUSPCIO_h */
