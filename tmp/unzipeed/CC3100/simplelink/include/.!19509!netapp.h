/*
 * netapp.h - CC31xx/CC32xx Host Driver Implementation
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "simplelink.h"

#ifndef __NETAPP_H__
#define __NETAPP_H__

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************************/
/*ERROR code*/
#define NETAPP_RX_BUFFER_LENGTH_ERROR -230
/*************************************************************************************************************/

typedef struct {
  unsigned long PacketsSent;
  unsigned long PacketsReceived;
  unsigned short MinRoundTime;
  unsigned short MaxRoundTime;
  unsigned short AvgRoundTime;
  unsigned long TestTime;
} SlPingReport_t;

typedef struct {
  unsigned long PingIntervalTime; /* delay between pings, in miliseconds */
  unsigned short PingSize;        /* ping packet size in bytes           */
  unsigned short
      PingRequestTimeout; /* timeout time for every ping in miliseconds  */
  unsigned long
      TotalNumberOfAttempts; /* max number of ping requests. 0 - forever    */
  unsigned long
      Flags; /* flag - 0 report only when finished, 1 - return response for
                every ping, 2 - stop after 1 successful ping.  */
  unsigned long Ip; /* IPv4 address or IPv6 first 4 bytes  */
  unsigned long Ip1OrPaadding;
  unsigned long Ip2OrPaadding;
  unsigned long Ip3OrPaadding;
} SlPingStartCommand_t;

/*  Http Server interface */

#define MAX_INPUT_STRING 64 /*  because of WPA */

#define MAX_AUTH_NAME_LEN 20
#define MAX_AUTH_PASSWORD_LEN 20
#define MAX_AUTH_REALM_LEN 20

#define MAX_DEVICE_URN_LEN (15 + 1)
#define MAX_DOMAIN_NAME_LEN (24 + 1)

#define MAX_ACTION_LEN 30
#define MAX_TOKEN_NAME_LEN                                              \
  20 /* Important: in case the max len is changed, make sure the struct \
        sl_NetAppHttpServerSendToken_t in protocol.h is padded correctly!! */
#define MAX_TOKEN_VALUE_LEN MAX_INPUT_STRING

/* Server Events */
#define SL_NETAPP_HTTPGETTOKENVALUE 1
#define SL_NETAPP_HTTPPOSTTOKENVALUE 2

#define NETAPP_MAX_SERVICE_TEXT_SIZE 256
#define NETAPP_MAX_SERVICE_NAME_SIZE 60
#define NETAPP_MAX_SERVICE_HOST_NAME_SIZE 64

/* Server Responses */
#define SL_NETAPP_RESPONSE_NONE 0
#define SL_NETAPP_HTTPSETTOKENVALUE 1

#define SL_NETAPP_FAMILY_MASK 0x80

typedef struct _slHttpServerString_t {
  unsigned char len;
  unsigned char *data;
} slHttpServerString_t;

typedef struct _slHttpServerData_t {
  unsigned char value_len;
  unsigned char name_len;
  unsigned char *token_value;
  unsigned char *token_name;
} slHttpServerData_t;

typedef struct _slHttpServerPostData_t {
  slHttpServerString_t action;
  slHttpServerString_t token_name;
  slHttpServerString_t token_value;
} slHttpServerPostData_t;

typedef union {
  slHttpServerString_t httpTokenName;  /* SL_NETAPP_HTTPGETTOKENVALUE */
  slHttpServerPostData_t httpPostData; /* SL_NETAPP_HTTPPOSTTOKENVALUE */
} SlHttpServerEventData_u;

typedef union {
  slHttpServerString_t token_value;
} SlHttpServerResponsedata_u;

typedef struct {
  unsigned long Event;
  SlHttpServerEventData_u EventData;
} SlHttpServerEvent_t;

typedef struct {
  unsigned long Response;
  SlHttpServerResponsedata_u ResponseData;
} SlHttpServerResponse_t;

typedef struct {
  unsigned long lease_time;
  unsigned long ipv4_addr_start;
  unsigned long ipv4_addr_last;
} SlNetAppDhcpServerBasicOpt_t;

/********************************************************************************************************/
/*mDNS parameters*/

typedef enum {
  SL_NET_APP_FULL_SERVICE_WITH_TEXT_IPV4_TYPE = 1,
  SL_NET_APP_FULL_SERVICE_IPV4_TYPE,
  SL_NET_APP_SHORT_SERVICE_IPV4_TYPE

} SlNetAppGetServiceListType_e;

typedef struct {
  unsigned long service_ipv4;
  unsigned short service_port;
  unsigned short Reserved;
} SlNetAppGetShortServiceIpv4List_t;

typedef struct {
  unsigned long service_ipv4;
  unsigned short service_port;
  unsigned short Reserved;
  unsigned char service_name[NETAPP_MAX_SERVICE_NAME_SIZE];
  unsigned char service_host[NETAPP_MAX_SERVICE_HOST_NAME_SIZE];
} SlNetAppGetFullServiceIpv4List_t;

typedef struct {
  unsigned long service_ipv4;
  unsigned short service_port;
  unsigned short Reserved;
  unsigned char service_name[NETAPP_MAX_SERVICE_NAME_SIZE];
  unsigned char service_host[NETAPP_MAX_SERVICE_HOST_NAME_SIZE];
  unsigned char service_text[NETAPP_MAX_SERVICE_TEXT_SIZE];
} SlNetAppGetFullServiceWithTextIpv4List_t;

typedef struct {
  /*The below parameters are used to configure the advertise times and interval
  For example:
      If:
      Period is set to T
      Repetitions are set to P
      Telescopic factor is K=2
      The transmission shall be:
      advertise P times
      wait T
      advertise P times
      wait 4 * T
      advertise P time
      wait 16 * T  ... (till max time reached / configuration changed / query
  issued)
  */
  unsigned long t; /* Number of ticks for the initial period. Default is 100
                      ticks for 1 second. */
  unsigned long p; /* Number of repetitions. Default value is 1 */
  unsigned long k; /* Telescopic factor. Default value is 2. */
  unsigned long RetransInterval; /* Announcing retransmission interval */
  unsigned long Maxinterval;     /* Announcing max period interval     */
  unsigned long max_time;        /* Announcing max time        */
} SlNetAppServiceAdvertiseTimingParameters_t;

#define SL_NET_APP_MASK_IPP_TYPE_OF_SERVICE 0x00000001
#define SL_NET_APP_MASK_DEVICE_INFO_TYPE_OF_SERVICE 0x00000002
#define SL_NET_APP_MASK_HTTP_TYPE_OF_SERVICE 0x00000004
#define SL_NET_APP_MASK_HTTPS_TYPE_OF_SERVICE 0x00000008
#define SL_NET_APP_MASK_WORKSATION_TYPE_OF_SERVICE 0x00000010
#define SL_NET_APP_MASK_GUID_TYPE_OF_SERVICE 0x00000020
#define SL_NET_APP_MASK_H323_TYPE_OF_SERVICE 0x00000040
#define SL_NET_APP_MASK_NTP_TYPE_OF_SERVICE 0x00000080
#define SL_NET_APP_MASK_OBJECITVE_TYPE_OF_SERVICE 0x00000100
#define SL_NET_APP_MASK_RDP_TYPE_OF_SERVICE 0x00000200
#define SL_NET_APP_MASK_REMOTE_TYPE_OF_SERVICE 0x00000400
#define SL_NET_APP_MASK_RTSP_TYPE_OF_SERVICE 0x00000800
#define SL_NET_APP_MASK_SIP_TYPE_OF_SERVICE 0x00001000
#define SL_NET_APP_MASK_SMB_TYPE_OF_SERVICE 0x00002000
#define SL_NET_APP_MASK_SOAP_TYPE_OF_SERVICE 0x00004000
#define SL_NET_APP_MASK_SSH_TYPE_OF_SERVICE 0x00008000
#define SL_NET_APP_MASK_TELNET_TYPE_OF_SERVICE 0x00010000
#define SL_NET_APP_MASK_TFTP_TYPE_OF_SERVICE 0x00020000
#define SL_NET_APP_MASK_XMPP_CLIENT_TYPE_OF_SERVICE 0x00040000
#define SL_NET_APP_MASK_RAOP_TYPE_OF_SERVICE 0x00080000
#define SL_NET_APP_MASK_ALL_TYPE_OF_SERVICE 0xFFFFFFFF

/********************************************************************************************************/
/* sl_NetAppDnsGetHostByName error codes     */

#define SL_NET_APP_DNS_QUERY_NO_RESPONSE \
  (-159) /* DNS query failed, no response                        */
#define SL_NET_APP_DNS_NO_SERVER \
  (-161) /* No DNS server was specified                          */
#define SL_NET_APP_DNS_QUERY_FAILED \
  (-163) /* DNS query failed; no DNS server sent an 'answer'     */
#define SL_NET_APP_DNS_MALFORMED_PACKET \
  (-166) /* Improperly formed or corrupted DNS packet received   */
#define SL_NET_APP_DNS_MISMATCHED_RESPONSE \
  (-174) /* Server response type does not match the query request*/

/********************************************************************************************************/

/* NetApp application IDs */
#define SL_NET_APP_HTTP_SERVER_ID (1)
#define SL_NET_APP_DHCP_SERVER_ID (2)
#define SL_NET_APP_MDNS_ID (4)
#define SL_NET_APP_DNS_SERVER_ID (8)
#define SL_NET_APP_DEVICE_CONFIG_ID (16)

/* NetApp application set/get options */
#define NETAPP_SET_DHCP_SRV_BASIC_OPT (0)

/* HTTP server set/get options */
#define NETAPP_SET_GET_HTTP_OPT_PORT_NUMBER (0)
#define NETAPP_SET_GET_HTTP_OPT_AUTH_CHECK (1)
#define NETAPP_SET_GET_HTTP_OPT_AUTH_NAME (2)
#define NETAPP_SET_GET_HTTP_OPT_AUTH_PASSWORD (3)
#define NETAPP_SET_GET_HTTP_OPT_AUTH_REALM (4)
#define NETAPP_SET_GET_HTTP_OPT_ROM_PAGES_ACCESS (5)

#define NETAPP_SET_GET_MDNS_CONT_QUERY_OPT (1)
#define NETAPP_SET_GET_MDNS_QEVETN_MASK_OPT (2)
#define NETAPP_SET_GET_MDNS_TIMING_PARAMS_OPT (3)

/* DNS server set/get options */
#define NETAPP_SET_GET_DNS_OPT_DOMAIN_NAME (0)

/* Device Config set/get options */
#define NETAPP_SET_GET_DEV_CONF_OPT_DEVICE_URN (0)
#define NETAPP_SET_GET_DEV_CONF_OPT_DOMAIN_NAME (1)

typedef void (*P_SL_DEV_PING_CALLBACK)(SlPingReport_t *);

/*****************************************************************************

    API Prototypes

 *****************************************************************************/

/*!

    \addtogroup netapp
    @{

*/
/*!
    \brief Starts a network application

    Gets and starts network application for the current WLAN mode

    \param[in] AppBitMap      application bitmap, could be one or combination of
   the following: \n
                              - SL_NET_APP_HTTP_SERVER_ID (1)
                              - SL_NET_APP_DHCP_SERVER_ID (2)
                              - SL_NET_APP_MDNS_ID        (4)

    \return                   On error, negative number is returned

    \sa                       Stop one or more the above started applications
   using sl_NetAppStop \note                     This command activates the
   application for the current WLAN mode (AP or STA) \warning \par Example:
    \code
    For example: Starting internal HTTP server + DHCP server:
    sl_NetAppStart(SL_NET_APP_HTTP_SERVER_ID | SL_NET_APP_DHCP_SERVER_ID)

    \endcode
*/
#if _SL_INCLUDE_FUNC(sl_NetAppStart)
int sl_NetAppStart(unsigned long AppBitMap);
#endif
/*!
    \brief Stops a network application

    Gets and stops network application for the current WLAN mode

    \param[in] AppBitMap    application id, could be one of the following: \n
                            - SL_NET_APP_HTTP_SERVER_ID (1)
                            - SL_NET_APP_DHCP_SERVER_ID (2)
                            - SL_NET_APP_MDNS_ID (4)

    \return                 On error, negative number is returned

    \sa
    \note                This command disables the application for the current
   active WLAN mode (AP or STA) \warning \par                 Example: \code

    For example: Stopping internal HTTP server:
                         sl_NetAppStop(SL_NET_APP_HTTP_SERVER_ID);

    \endcode
*/
#if _SL_INCLUDE_FUNC(sl_NetAppStop)
int sl_NetAppStop(unsigned long AppBitMap);
#endif

/*!
    \brief Get host IP by name

    Obtain the IP Address of machine on network, by machine name.

    \param[in]  hostname        host name
    \param[in]  usNameLen       name length
    \param[out] out_ip_addr     This parameter is filled in with
                                host IP address. In case that host name is not
                                resolved, out_ip_addr is zero.
    \param[in]  family          protocol family

    \return                     On success, positive is returned.
                                On error, negative is returned
                                SL_POOL_IS_EMPTY may be return in case there are
   no resources in the system In this case try again later or increase
   MAX_CONCURRENT_ACTIONS Possible DNS error codes:
                                - SL_NET_APP_DNS_QUERY_NO_RESPONSE
                                - SL_NET_APP_DNS_NO_SERVER
                                - SL_NET_APP_DNS_QUERY_FAILED
                                - SL_NET_APP_DNS_MALFORMED_PACKET
                                - SL_NET_APP_DNS_MISMATCHED_RESPONSE

    \sa
    \note   Only one sl_NetAppDnsGetHostByName can be handled at a time.
            Calling this API while the same command is called from another
   thread, may result in one of the two scenarios:
            1. The command will wait (internal) until the previous command
   finish, and then be executed.
            2. There are not enough resources and POOL_IS_EMPTY error will
   return. In this case, MAX_CONCURRENT_ACTIONS can be increased (result in
   memory increase) or try again later to issue the command. \warning \par
   Example: \code unsigned long DestinationIP;
    sl_NetAppDnsGetHostByName("www.google.com", strlen("www.google.com"),
   &DestinationIP,SL_AF_INET);

    Addr.sin_family = SL_AF_INET;
    Addr.sin_port = sl_Htons(80);
    Addr.sin_addr.s_addr = sl_Htonl(DestinationIP);
    AddrSize = sizeof(SlSockAddrIn_t);
    SockID = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, 0);
    \endcode
*/
#if _SL_INCLUDE_FUNC(sl_NetAppDnsGetHostByName)
int sl_NetAppDnsGetHostByName(char *hostname, unsigned short usNameLen,
                              unsigned long *out_ip_addr, unsigned char family);
#endif

/*!
        \brief Return service attributes like IP address, port and text
   according to service name \par The user sets a service name Full/Part (see
   example below), and should get:
        - IP of service
        - The port of service
        - The text of service

        Hence it can make a connection to the specific service and use it.
        It is similar to get host by name method.

        It is done by a single shot query with PTR type on the service name.

                  The command that is sent is from constant parameters and
   variables parameters.


        \param[in]     pService                   Service name can be full or
   partial. \n Example for full service name:
                                                  1. PC1._ipp._tcp.local
                                                  2. PC2_server._ftp._tcp.local
   \n
                                                  .
                                                  Example for partial service
   name:
                                                  1. _ipp._tcp.local
                                                  2. _ftp._tcp.local

        \param[in]    ServiceLen                  The length of the service name
   (in_pService). \param[in]    Family                      IPv4 or IPv6
   (SL_AF_INET , SL_AF_INET6). \param[out]    pAddr Contains the IP address of
   the service. \param[out]    pPort                      Contains the port of
   the service. \param[out]    pTextLen                   Has 2 options. One as
   Input field and the other one as output:
                                                  - Input: \n
                                                  Contains the max length of the
   text that the user wants to get.\n It means that if the text len of service
   is bigger that its value than the text is cut to inout_TextLen value.
                                                  - Output: \n
                                                   Contain the length of the
   text that is returned. Can be full text or part of the text (see above).

        \param[out]   pOut_pText     Contains the text of the service full or
   partial

        \return       On success, zero is returned
                      SL_POOL_IS_EMPTY may be return in case there are no
   resources in the system In this case try again later or increase
   MAX_CONCURRENT_ACTIONS In case No service is found error -177 will be
   returned

        \note         The returns attributes belongs to the first service found.
                      There may be other services with the same service name
   that will response to the query. The results of these responses are saved in
   the peer cache of the Device and should be read by another API.

                      Only one sl_NetAppDnsGetHostByService can be handled at a
   time. Calling this API while the same command is called from another thread,
   may result in one of the two scenarios:
                      1. The command will wait (internal) until the previous
   command finish, and then be executed.
                      2. There are not enough resources and SL_POOL_IS_EMPTY
   error will return. In this case, MAX_CONCURRENT_ACTIONS can be increased
   (result in memory increase) or try again later to issue the command.

        \warning      Text length can be 120 bytes only
*/
#if _SL_INCLUDE_FUNC(sl_NetAppDnsGetHostByService)
long sl_NetAppDnsGetHostByService(
    char *pServiceName, /*  string containing all (or only part): name + subtype
                           + service */
    unsigned char ServiceLen, unsigned char Family, /*  4-IPv4 , 16-IPv6  */
    unsigned long pAddr[], unsigned long *pPort,
    unsigned short *pTextLen, /*  in: max len , out: actual len */
    char *pText);

#endif

/*!



        \brief Get service List
        Insert into out pBuffer a list of peer's services that are the NWP.
        The list is in a form of service struct. The user should chose the type
        of the service struct like:
            - Full service parameters with text.
            - Full service parameters.
            - Short service parameters (port and IP only) especially for tiny
   hosts.

        The different types of struct are made to give the
        Possibility to save memory in the host


        The user also chose how many max services to get and start point index
        NWP peer cache.
        For example:
