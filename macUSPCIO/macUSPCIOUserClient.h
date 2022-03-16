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
    virtual bool start( IOService * provider );
    virtual void stop( IOService * provider );

    /* IOUserClient overrides */
    virtual bool initWithTask( task_t owningTask, void * securityID, UInt32 type,  OSDictionary * properties );
    virtual IOReturn clientClose( void );

    virtual IOReturn externalMethod( uint32_t selector, IOExternalMethodArguments * arguments, IOExternalMethodDispatch * dispatch = 0, OSObject * target = 0, void * reference = 0 );

    /* External methods */
    static IOReturn externalPciReadIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
    static IOReturn externalPciWriteIOByte(macUSPCIO *target, void *reference, IOExternalMethodArguments *arguments);
};

#endif /* macUSPCIOUserClient_h */
