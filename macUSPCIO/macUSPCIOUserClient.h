//
//  macUSPCIOUserClient.h
//  macUSPCIO
//
//  Created by Shady Nawara on 3/15/22.
//

#ifndef macUSPCIOUserClient_h
#define macUSPCIOUserClient_h

#include <IOKit/IOUserClient.h>

class macUSPCIOUserClient : public IOUserClient
{
    OSDeclareDefaultStructors( macUSPCIOUserClient );

private:
    macUSPCIO *       driver;
    task_t                      fTask;
    SInt32                      openClientsCount;
    static const IOExternalMethodDispatch sMethods[kNumberOfMethods];

public:
    /* IOService overrides */
    virtual bool init(void) override;
    virtual bool start( IOService * provider ) override;
    virtual void stop( IOService * provider ) override;
    virtual void free(void) override;

    /* IOUserClient overrides */
    virtual bool initWithTask(task_t owningTask, void *securityToken, UInt32 type, OSDictionary *properties) override;

    virtual IOReturn externalMethod( uint32_t selector, IOExternalMethodArguments * arguments, IOExternalMethodDispatch * dispatch = 0, OSObject * target = 0, void * reference = 0 ) override;

    /* External methods */
    static IOReturn externalPciReadIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
    static IOReturn externalPciWriteIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
    
    static IOReturn externalPciReadConfigByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
    static IOReturn externalPciReadConfigWord(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
};

#endif /* macUSPCIOUserClient_h */
