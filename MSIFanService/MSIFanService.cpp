//
//  MSIFanService.cpp
//  MSIFanControl
//
//  Created by lgs3137 on 2020/1/3.
//  Copyright © 2020 none. All rights reserved.
//

#include <libkern/version.h>
#include <IOKit/IOCommandGate.h>
#include <sys/kern_control.h>
#include "MSIFanService.hpp"
#include "MSIECControl.h"

OSDefineMetaClassAndStructors(cn_lgs3137_MSIFanService, IOService)

bool MSIFanService::init(OSDictionary *dict)
{
    bool result = IOService::init(dict);
    device = nullptr;
    return result;
}

IOService *MSIFanService::probe(IOService *provider, SInt32 *score)
{
    return IOService::probe(provider, score);
}

errno_t EPHandleSet(kern_ctl_ref ctlref, unsigned int unit, void *userdata, int opt, void *data, size_t len)
{
    return 0;
}

errno_t EPHandleGet(kern_ctl_ref ctlref, unsigned int unit, void *userdata, int opt, void *data, size_t *len)
{
    return 0;
}

errno_t EPHandleConnect(kern_ctl_ref ctlref, struct sockaddr_ctl *sac, void **unitinfo)
{
    return 0;
}

errno_t EPHandleDisconnect(kern_ctl_ref ctlref, unsigned int unit, void *unitinfo)
{
    return 0;
}

// 监听服务并调用Hotpatch方法
errno_t MSIFanService::EPHandleWrite(kern_ctl_ref ctlref, unsigned int unit, void *userdata, mbuf_t m, int flags)
{
    struct MSIECControl *ctrl;
    ctrl = (MSIECControl *)mbuf_data(m);
    fan0 = ctrl->arg0;
    fan1 = ctrl->arg1;
    fan2 = ctrl->arg2;
    fan3 = ctrl->arg3;
    fan4 = ctrl->arg4;
    fan5 = ctrl->arg5;

    OSObject *params[6];
    params[0] = OSNumber::withNumber(fan0, 8 * sizeof(uint32_t));
    params[1] = OSNumber::withNumber(fan1, 8 * sizeof(uint32_t));
    params[2] = OSNumber::withNumber(fan2, 8 * sizeof(uint32_t));
    params[3] = OSNumber::withNumber(fan3, 8 * sizeof(uint32_t));
    params[4] = OSNumber::withNumber(fan4, 8 * sizeof(uint32_t));
    params[5] = OSNumber::withNumber(fan5, 8 * sizeof(uint32_t));
    device->evaluateObject("XFAN", nullptr, params, 6);
    
    IOLog("XFAN: Control EC %d,%d,%d,%d,%d,%d", fan0, fan1, fan2, fan3, fan4, fan5);
    return 0;
}

// 启动服务
bool MSIFanService::start(IOService *provider)
{
    device = OSDynamicCast(IOACPIPlatformDevice, provider);
    if (device == nullptr || !IOService::start(provider)) {
        return false;
    }
    IOSleep(2000);
    errno_t error;
    struct kern_ctl_reg ep_ctl;
    kern_ctl_ref kctlref;
    bzero(&ep_ctl, sizeof(ep_ctl));
    ep_ctl.ctl_id = 0;
    ep_ctl.ctl_unit = 0;
    strlcpy(ep_ctl.ctl_name, "cn.lgs3137.msifanservice.ctl", sizeof(ep_ctl.ctl_name));
    ep_ctl.ctl_flags = CTL_FLAG_PRIVILEGED & CTL_FLAG_REG_ID_UNIT;
    ep_ctl.ctl_send = EPHandleWrite;
    ep_ctl.ctl_setopt = EPHandleSet;
    ep_ctl.ctl_getopt = EPHandleGet;
    ep_ctl.ctl_connect = EPHandleConnect;
    ep_ctl.ctl_disconnect = EPHandleDisconnect;
    error = ctl_register(&ep_ctl, &kctlref);

    IOLog("XFAN: Starting %s",ep_ctl.ctl_name);
    return true;
}

// 关闭服务
void MSIFanService::stop(IOService *provider)
{
    IOLog("XFAN: Stop cn.lgs3137.msifanservice.ctl");
    return;
}
