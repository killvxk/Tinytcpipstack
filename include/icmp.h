//
// Created by 张家望 on 2020/5/3.
//

#ifndef TINYTCPIPSTACK_ICMP_H
#define TINYTCPIPSTACK_ICMP_H

/* icmp type
 * 与内核源码icmp type进行对比，内核源码中没有的类型数字，本项目代码用ICMP_T_DUMMY_*替代
 * 对应的处理函数为drop函数，统一做丢弃处理
 * */
#define ICMP_T_ECHORLY        0
#define ICMP_T_DUMMY_1        1
#define ICMP_T_DUMMY_2        2
#define ICMP_T_DESTUNREACH    3
#define ICMP_T_SOURCEQUENCH    4
#define ICMP_T_REDIRECT        5
#define ICMP_T_DUMMY_6        6
#define ICMP_T_DUMMY_7        7
#define ICMP_T_ECHOREQ        8
#define ICMP_T_DUMMY_9        9
#define ICMP_T_DUMMY_10        10
#define ICMP_T_TIMEEXCEED    11
#define ICMP_T_PARAMPROBLEM    12    /* parameter problem */
#define ICMP_T_TIMESTAMPREQ    13
#define ICMP_T_TIMESTAMPRLY    14
#define ICMP_T_INFOREQ        15
#define ICMP_T_INFORLY        16
#define ICMP_T_ADDRMASKREQ    17
#define ICMP_T_ADDRMASKRLY    18
#define ICMP_T_MAXNUM        18

/* Codes for UNREACH. */
#define ICMP_NET_UNREACH    0    /* Network Unreachable		*/
#define ICMP_HOST_UNREACH    1    /* Host Unreachable		*/
#define ICMP_PROT_UNREACH    2    /* Protocol Unreachable		*/
#define ICMP_PORT_UNREACH    3    /* Port Unreachable		*/
#define ICMP_FRAG_NEEDED    4    /* Fragmentation Needed/DF set	*/
#define ICMP_SR_FAILED        5    /* Source Route failed		*/
#define ICMP_NET_UNKNOWN    6
#define ICMP_HOST_UNKNOWN    7
#define ICMP_HOST_ISOLATED    8
#define ICMP_NET_ANO        9
#define ICMP_HOST_ANO        10
#define ICMP_NET_UNR_TOS    11
#define ICMP_HOST_UNR_TOS    12
#define ICMP_PKT_FILTERED    13    /* Packet filtered */
#define ICMP_PREC_VIOLATION    14    /* Precedence violation */
#define ICMP_PREC_CUTOFF    15    /* Precedence cut off */
#define NR_ICMP_UNREACH        15    /* instead of hardcoding immediate value */

/* Codes for REDIRECT. */
#define ICMP_REDIR_NET        0    /* Redirect Net			*/
#define ICMP_REDIR_HOST        1    /* Redirect Host		*/
#define ICMP_REDIR_NETTOS    2    /* Redirect Net for TOS		*/
#define ICMP_REDIR_HOSTTOS    3    /* Redirect Host for TOS	*/

/* Codes for TIME_EXCEEDED. */
#define ICMP_EXC_TTL        0    /* TTL count exceeded		*/
#define ICMP_EXC_FRAGTIME    1    /* Fragment Reass time exceeded	*/


/*ICMP报头*/
struct icmphdr {
    /*ICMP消息类型*/
    unsigned char icmp_type;
    /*ICMP消息代码*/
    unsigned char icmp_code;
    /*校验和*/
    unsigned short icmp_checksum;
    union {
        struct {
            unsigned short id;/*识别号（一般用进程号作为识别号）, 用于匹配ECHO和ECHO REPLY包*/
            unsigned short seq;/*报文序列号, 用于标记ECHO报文顺序*/
        } echo;
        unsigned int gw;
        unsigned int pad;
    } icmp_un;
    unsigned char icmp_data[0];
} __attribute__((packed));

#define icmp_id icmp_un.echo.id
#define icmp_seq icmp_un.echo.seq
#define icmp_undata icmp_un.pad
#define icmp_gw icmp_un.gw

#define ICMP_HRD_SZ sizeof(struct icmphdr)

/*ICMP报文包含在IP数据报中，ICMP报文作为IP层数据报的数据，加上数据报的首部，组成数据报发送出去。
 * 因此为了获取struct icmphdr，利用ipdata定位ip数据报数据部分的位置，然后通过指针强转获取icmphdr
 * */
#define ip2icmp(ip) ((struct icmphdr*)ipdata(ip))

/*
 * ICMP消息类型描述符。其字段之一是用于处理入消息的函数
 * */
struct icmp_control {
    int error;/*error=1表示为差错报文，为0则是一个查询ICMP报文*/
    char *info;

    /*
     * 由接收函数icmp_rcv启用的函数，处理送进来的ICMP消息
     * */
    void (*handler)(struct icmp_control *, struct pk_buff *);/*对该输入类型ICMP报文的处理函数*/
};

#define ICMP_DESC_DUMMY_ENTRY \
{\
    .error=1,\
    .info=NULL,\
    .handler=icmp_drop_reply,\
}

extern void icmp_send(unsigned char,unsigned char,unsigned int,struct pk_buff *);


#endif //TINYTCPIPSTACK_ICMP_H
