//
//  MSIFanService.hpp
//  MSIFanControl
//
//  Created by lgs3137 on 2020/1/3.
//  Copyright © 2020 none. All rights reserved.
//

#ifndef MSIFanService_hpp
#define MSIFanService_hpp

#define MSIFanService cn_lgs3137_MSIFanService

#include <IOKit/IOService.h>
#include <IOKit/acpi/IOACPIPlatformDevice.h>

class MSIFanService : public IOService
{
	OSDeclareDefaultStructors(cn_lgs3137_MSIFanService)
    
public:
	virtual bool init(OSDictionary *dictionary = 0) override;
    virtual IOService *probe(IOService *provider, SInt32 *score) override;
    virtual bool start(IOService *provider) override;
    virtual void stop(IOService *provider) override;

    static errno_t EPHandleWrite(kern_ctl_ref ctlref, unsigned int unit, void *userdata, mbuf_t m, int flags);
};

static IOACPIPlatformDevice *device;

uint32_t fan0 = 0x00000014, fan1 = 0x00000014, fan2 = 0x00000028, fan3 = 0x0000003C, fan4 = 0x00000050, fan5 = 0x00000064;

#endif
