//
// Created by Kyrie on 2019/5/3.
//

#ifndef TINYTCPIPSTACK_NETCONFIG_H
#define TINYTCPIPSTACK_NETCONFIG_H

/* 32位无符号数为网络所使用的IP地址，为网络字节序 */
#define FAKE_TAP_ADDR 0x0200000a /*10.0.0.2*/
#define FAKE_IPADDR 0x0100000a /*10.0.0.1*/
#define FAKE_HWADDR "\x00\x34\x45\x67\x89\xab"
#define FAKE_TAP_NETMASK 0x00ffffff /* 255.255.255.0 */
#define FAKE_NETMASK 0x00ffffff /*255.255.255.0*/

#endif //TINYTCPIPSTACK_NETCONFIG_H
