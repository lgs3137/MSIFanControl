//
//  main.cpp
//  MSIFanControl
//
//  Created by lgs3137 on 2020/1/3.
//  Copyright © 2020 none. All rights reserved.
//

#include <iostream>
#include <sys/kern_control.h>
#include <sys/kern_event.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "MSIECControl.h"

void sendctl(struct MSIECControl ctrl) {
    struct ctl_info info;
    struct sockaddr_ctl addr;
    int fd = socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL);
    if (fd != -1) {
        bzero(&addr, sizeof(addr));
        addr.sc_len = sizeof(addr);
        addr.sc_family = AF_SYSTEM;
        addr.ss_sysaddr = AF_SYS_CONTROL;
        memset(&info, 0, sizeof(info));
        strcpy(info.ctl_name, "cn.lgs3137.msifanservice.ctl");
        if (ioctl(fd, CTLIOCGINFO, &info)) {
            exit(-1);
        }
        addr.sc_id = info.ctl_id;
        addr.sc_unit = 0;
        if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_ctl))){
            exit(-1);
        }
        send(fd, &ctrl, sizeof(MSIECControl), 0);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printf("正确使用:\n%s 20 30 40 60 80 100\n", argv[0]);
    }
    else {
        struct MSIECControl ctrl;
        
        ctrl.arg0 = (uint32_t)atoi(argv[1]);
        ctrl.arg1 = (uint32_t)atoi(argv[2]);
        ctrl.arg2 = (uint32_t)atoi(argv[3]);
        ctrl.arg3 = (uint32_t)atoi(argv[4]);
        ctrl.arg4 = (uint32_t)atoi(argv[5]);
        ctrl.arg5 = (uint32_t)atoi(argv[6]);
        sendctl(ctrl);
        printf("\n😈 %s %s %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
    }
}
