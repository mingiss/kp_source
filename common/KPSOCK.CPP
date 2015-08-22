//---------------------
// kpsock.cpp
// Win32 sockets
//

//---------------------
#ifdef Debug
#define TRACE_HTTP
#endif

//---------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <time.h>

#if (CompilerGr == Watcom) && (__WATCOMC__ == 1202)

// dël SOCKADDR_STORAGE, faile ws2def.h, includintam ið winsock2.h/windows.h, includintam ið kpsock.cpp
#  if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0600)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600   // Windows Vista
#  endif

// dël GROUP_REQ faile ws2ipdef.h, includintam ið ..., includintam ið kpsock.cpp
#  if !defined(NTDDI_VERSION) || (NTDDI_VERSION < 0x05010000)
#undef NTDDI_VERSION
#define NTDDI_VERSION 0x05010000
#  endif

// kad windows.h neincludintø winsock.h
// #define _WINSOCKAPI_
// typedef unsigned short      u_short;

#include <winsock2.h>
#include <iptypes.h>
#include <Ws2ipdef.h>
#include <Iphlpapi.h>
#endif

#if (CompilerGr==Msvc)
#include <winsock2.h>
#endif

// mingw 3.15 ir vëlesniems, Open Watcom v1.8 ( > 1.1)
#if FALSE // ((CompilerGr == Mingw) && (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION >= 315))
#include <ws2def.h>
#include <Ws2ipdef.h>
#include <Iphlpapi.h>
#endif

#if (CompilerGr == Watcom) && (__WATCOMC__ < 1202)
#include <winsock.h>
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"


//---------------------
const unsigned char *ProtocolNames[NUM_OF_PROTS_1] =
{
   (const unsigned char *)"<undefined>",  //   NO_PROT

   (const unsigned char *)"HTTP",         //   HTTP_PROT,
   (const unsigned char *)"FTP",          //   FTP_PROT,
};


const unsigned char *TransferModeNames[NUM_OF_HTTP_TR_MODES_1] =
{
   (const unsigned char *)"<undefined>",  //   NO_MODE

   (const unsigned char *)"chunked",      //   HTTP_TR_CHUNK_MODE,
};


const unsigned char *KpsockMsgTypes[NUM_OF_HTTP_MSG_TYPES_1] =
{
   (const unsigned char *)"UNKNOWN",
   (const unsigned char *)"REQUEST",
   (const unsigned char *)"GET",
   (const unsigned char *)"POST",
   (const unsigned char *)"POST_DATA",
   (const unsigned char *)"POST_SUBDATA",
   (const unsigned char *)"REPLY",
};


const unsigned char *KpsockTagNames[KPSOCK_NUM_OF_HDTAGS_7 + 1] =
{
   (const unsigned char *)"Date:",                       // KPSOCK_HDTAG_Date
   (const unsigned char *)"Server:",                     // KPSOCK_HDTAG_Server
   (const unsigned char *)"Set-Cookie:",                 // KPSOCK_HDTAG_SetCookie
   (const unsigned char *)"Last-Modified:",              // KPSOCK_HDTAG_LastModified
   (const unsigned char *)"X-Powered-By:",               // KPSOCK_HDTAG_XPoweredBy
   (const unsigned char *)"ETag:",                       // KPSOCK_HDTAG_ETag
   (const unsigned char *)"Accept-Ranges:",              // KPSOCK_HDTAG_AcceptRanges
   (const unsigned char *)"Content-Length:",             // KPSOCK_HDTAG_ContentLength
   (const unsigned char *)"Transfer-Encoding:",          // KPSOCK_HDTAG_TransferEncoding
   (const unsigned char *)"Connection:",                 // KPSOCK_HDTAG_Connection
   (const unsigned char *)"Keep-Alive:",                 // KPSOCK_HDTAG_KeepAlive
   (const unsigned char *)"Content-Type:",               // KPSOCK_HDTAG_ContentType
   (const unsigned char *)"Content-Encoding:",           // KPSOCK_HDTAG_ContentEncoding
   (const unsigned char *)"Host:",                       // KPSOCK_HDTAG_Host
   (const unsigned char *)"User-Agent:",                 // KPSOCK_HDTAG_UserAgent
   (const unsigned char *)"Accept:",                     // KPSOCK_HDTAG_Accept
   (const unsigned char *)"Accept-Language:",            // KPSOCK_HDTAG_AcceptLanguage
   (const unsigned char *)"Accept-Encoding:",            // KPSOCK_HDTAG_AcceptEncoding
   (const unsigned char *)"Accept-Charset:",             // KPSOCK_HDTAG_AcceptCharset
   (const unsigned char *)"Pragma:",                     // KPSOCK_HDTAG_Pragma
   (const unsigned char *)"Cache-Control:",              // KPSOCK_HDTAG_CacheControl
   (const unsigned char *)"Referer:",                    // KPSOCK_HDTAG_Referer
   (const unsigned char *)"If-Modified-Since:",          // KPSOCK_HDTAG_IfModifiedSince
   (const unsigned char *)"If-None-Match:",              // KPSOCK_HDTAG_IfNoneMatch
   (const unsigned char *)"Content-Disposition:",        // KPSOCK_HDTAG_ContentDisposition
   (const unsigned char *)"Content-Transfer-Encoding:",  // KPSOCK_HDTAG_ContentTransferEncoding
   (const unsigned char *)"TE:",                         // KPSOCK_HDTAG_TE
   (const unsigned char *)"UA-CPU:",                     // KPSOCK_HDTAG_UA_CPU
   (const unsigned char *)"Location:",                   // KPSOCK_HDTAG_Location
   (const unsigned char *)"Acrobat-Version:",            // KPSOCK_HDTAG_AcrobatVersion
   (const unsigned char *)"Expires:",                    // KPSOCK_HDTAG_Expires
   (const unsigned char *)"Content-Description:",        // KPSOCK_HDTAG_ContentDescription
   NULL
};

const bool KpsockTagOccurences[KPSOCK_NUM_OF_HDTAGS_7][NUM_OF_HTTP_MSG_TYPES_1] =
{
// HTTP_MSG_TYPE_UNKNOWN
//       HTTP_REQUEST_UNKNOWN
//             HTTP_GET_REQUEST
//                   HTTP_POST_REQUEST
//                         HTTP_POST_DATA_SEGM
//                               HTTP_POST_SUBDATA_SEGM
//                                     HTTP_REPLY

   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_Date
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_Server
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_SetCookie
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_LastModified
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_XPoweredBy
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_ETag
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_AcceptRanges
   False,False,False,True, False,False,True,  // KPSOCK_HDTAG_ContentLength
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_TransferEncoding
   False,False,True, True, False,False,True,  // KPSOCK_HDTAG_Connection
   False,False,True, True, False,False,True,  // KPSOCK_HDTAG_KeepAlive
   False,False,False,True, True, False,True,  // KPSOCK_HDTAG_ContentType
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_ContentEncoding
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_Host
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_UserAgent
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_Accept
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_AcceptLanguage
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_AcceptEncoding
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_AcceptCharset
   False,False,True, False,False,False,True,  // KPSOCK_HDTAG_Pragma
   False,False,True, True, False,False,True,  // KPSOCK_HDTAG_CacheControl
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_Referer
   False,False,True, False,False,False,False, // KPSOCK_HDTAG_IfModifiedSince
   False,False,True, False,False,False,False, // KPSOCK_HDTAG_IfNoneMatch
   False,False,False,False,True, False,True,  // KPSOCK_HDTAG_ContentDisposition
   False,False,False,False,True, False,True,  // KPSOCK_HDTAG_ContentTransferEncoding
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_TE
   False,False,True, True, False,False,False, // KPSOCK_HDTAG_UA_CPU
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_Location
   False,False,False,True, False,False,True,  // KPSOCK_HDTAG_AcrobatVersion
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_Expires
   False,False,False,False,False,False,True,  // KPSOCK_HDTAG_ContentDescription
};


//---------------------
bool IsHTTPdataMsg(int iHTTP_RetCode)
{
return(iHTTP_RetCode/100==2);
}

bool IsHTTPcontinueMsg(int iHTTP_RetCode)
{
return(iHTTP_RetCode/100==1);
}

bool IsHTTPerrorMsg(int iHTTP_RetCode)
{
return(iHTTP_RetCode/100==4);
}


//---------------------
HRESULT TestIP(const unsigned char *lpszIpAddr)
{
HRESULT retc=S_OK;
unsigned char adr_buf[KP_MAX_FNAME_LEN+1];
int dot_count;
const unsigned char *pnts;
unsigned char *pntd;
int ii;

   if((lpszIpAddr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) if(strlen(lpszIpAddr)>=KP_MAX_FNAME_LEN)
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) strcpy(adr_buf, lpszIpAddr);
   if(SUCCEEDED(retc)) retc=RemoveSpaces(adr_buf);
   if(SUCCEEDED(retc))
   {
      dot_count=0;
      pnts=pntd=adr_buf;

      while(pntd && SUCCEEDED(retc))
      {
         pntd=strchr(pnts, '.');
         if(pntd)
         {
            *pntd++ = Nul;
            dot_count++;
         }

         ii=strlen(pnts);
         if(((ii>3) || (ii<1)) && SUCCEEDED(retc)) retc=E_INVALIDARG;
         if(SUCCEEDED(retc)) if(!TvIsNumber(pnts)) retc=E_INVALIDARG;
         if(SUCCEEDED(retc)) if(strchr(pnts, '-')!=NULL) retc=E_INVALIDARG;
         if(SUCCEEDED(retc)) if(sscanf((char *)pnts, "%d", &ii)<1) retc=E_INVALIDARG;
         if((ii>255) && SUCCEEDED(retc)) retc=E_INVALIDARG;

         pnts=pntd;
      }
   }

   if((dot_count!=3) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
//    KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

return(retc);
}


//---------------------
KpSocket::KpSocket(int type)
{
HRESULT retc = S_OK;
WSADATA wsa_data;
WORD ver_requested = 0x0101; // ver 1.1

   m_lhOpenResult = S_OK;

   m_hSocket=INVALID_SOCKET;
   m_hAccSock=INVALID_SOCKET;

   m_iMsgType = HTTP_MSG_TYPE_UNKNOWN;
   m_iRetCode = 0;
   m_lpszRetMsg[0] = Nul;
   m_lContLen = MAXLONG;
   m_iTrMode = NORMAL_HTTP_TR_MODE;
   m_lpszBoundary[0] = Nul;
   m_lpszEndBoundary[0] = Nul;
   m_lpszCtrlName[0] = Nul;

   m_PackedUrl.m_lpszServerName[0] = Nul;
   m_PackedUrl.m_lpszServerNameUnres[0] = Nul;
// m_PackedUrl.m_lAddr = INADDR_NONE;
   m_PackedUrl.m_Addr.S_un.S_addr = INADDR_NONE;
   m_PackedUrl.m_iProtocol = NO_PROT;
   m_PackedUrl.m_iPort = 0;
   m_PackedUrl.m_lpszFileName[0] = Nul;

   m_lpszHdrBuf = null;
   KP_NEWA(m_lpszHdrBuf, unsigned char, MAX_HTTP_HDR_LEN + 1);

   m_lRestChunkLength = 0L;
// m_lNextChunkLength = 0L;

   m_lpszChunkPos = m_lpszHdrBuf;
   m_lChunkRest = 0L;

// Init the sockets interface
   if(SUCCEEDED(retc))
      if(WSAStartup(ver_requested, &wsa_data))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), TRUE, __FILE__, __LINE__, 0L);

// create the socket
   if(SUCCEEDED(retc))
   {
      m_hSocket = socket(PF_INET, type /* SOCK_STREAM */, (type == SOCK_DGRAM)?IPPROTO_UDP:0);
//    m_hSocket = socket(PF_INET, SOCK_RAW, 0);
      if(INVALID_SOCKET == m_hSocket)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


//---------------------
HRESULT KpSocket::GetOpenResult(void)
{
return(m_lhOpenResult);
}


//---------------------
KpSocket::~KpSocket(void)
{
HRESULT retc = S_OK;

   if(m_hAccSock != INVALID_SOCKET)
      if(closesocket(m_hAccSock))
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), TRUE, __FILE__, __LINE__, 0L);
   m_hAccSock = INVALID_SOCKET;

   if(m_hSocket != INVALID_SOCKET)
      if(closesocket(m_hSocket)) // gali duoti klaidà, kai uþdarinëjam neacceptintà socketà, buvo atsitikæ tux_ipam (o gal dël threadø kas nors?)
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), False /* True */, __FILE__, __LINE__, 0L);
   m_hSocket = INVALID_SOCKET;

// if(WSACleanup() /* ==SOCKET_ERROR */)
// /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), TRUE, __FILE__, __LINE__, 0L);

   KP_DELETEA(m_lpszHdrBuf);
}


//---------------------
HRESULT KpSocket::Resolve(const unsigned char *lpszUrl, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char url_buf[KP_MAX_FNAME_LEN+1];
unsigned char *pnts;
unsigned char *pntd;
unsigned char *pntdd;
unsigned char *msg_buf=NULL;

struct hostent *p_host;

#if FALSE
unsigned char port[MAX_LONG_DIGITS+1];
struct addrinfo aiHints;
struct addrinfo *aiList = NULL;
int retVal;
#endif

   if((lpszUrl==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
      if(strlen(lpszUrl)>=KP_MAX_FNAME_LEN)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, lpszUrl, bOutMsg, __FILE__, __LINE__, 0L);
      }

   if(SUCCEEDED(retc))
   {
      strcpy(url_buf, lpszUrl);
      pnts=url_buf;

// protocol
      m_PackedUrl.m_iProtocol=HTTP_PROT;
      pntd=strstr(pnts, "//");
      if(pntd)
      {
         *pntd=Nul;
         if(strlen(pnts)>0)
         {
            pntdd=strchr(pnts, ':');
            if(pntdd==NULL)
            {
               retc=E_INVALIDARG;
               KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
               KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
               if(strlen(pntdd)!=1)
               {
                  retc=E_INVALIDARG;
                  KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }

            if(SUCCEEDED(retc))
            {
               *pntdd=Nul;
               retc=GetKwrdIndex((int *)&m_PackedUrl.m_iProtocol, pnts, ProtocolNames, NUM_OF_PROTS_1, False, True);
               if(retc==KP_E_KWD_NOT_FOUND)
               {
                  retc=E_INVALIDARG;
                  KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }
            }
         }

         pnts=pntd+2;
      }
   }

// server name & port
   if(SUCCEEDED(retc))
   {
      pntd=strchr(pnts, '/');
      if(pntd) *pntd=Nul;

// port
      m_PackedUrl.m_iPort=HTTP_PORT;
      pntdd=strchr(pnts, ':');
      if(pntdd)
      {
         *(pntdd++)=Nul;
         sscanf((const char *)pntdd, "%d", &m_PackedUrl.m_iPort);
      }

// server name
      if(strlen(pnts)>=KP_MAX_FNAME_LEN)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
      }
   }
   if(SUCCEEDED(retc))
   {
      strncpy(m_PackedUrl.m_lpszServerName, pnts, KP_MAX_FNAME_LEN);
      m_PackedUrl.m_lpszServerName[KP_MAX_FNAME_LEN] = Nul;
      strcpy(m_PackedUrl.m_lpszServerNameUnres, m_PackedUrl.m_lpszServerName);

// file name & query
      m_PackedUrl.m_lpszFileName[0]=Nul;
      if(pntd!=NULL)
      {
         *pntd='/';
         if(strlen(pntd)>=KP_MAX_FNAME_LEN)
         {
            retc=KP_E_BUFFER_OVERFLOW;
            KpErrorProc.OutputErrorMessage(retc, pntd, bOutMsg, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc)) strcpy(m_PackedUrl.m_lpszFileName, pntd);
      }
   }

// ------------------------------
   if(SUCCEEDED(retc))
   {
      if(strcmp(m_PackedUrl.m_lpszServerName, KP_IPADDR_BROADCAST) == 0)
      {
// ------------------------------
// broadcast
int on = 1;
         if(SOCKET_ERROR == setsockopt(m_hSocket, SOL_SOCKET, SO_BROADCAST, (const char *)&on, sizeof(on)))
         {
            retc = KP_E_SYSTEM_ERROR;
            KpErrorProc.OutputErrorMessage(retc, WSAGetLastError(), bOutMsg, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc)) if(SOCKET_ERROR == setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)))
         {
            retc = KP_E_SYSTEM_ERROR;
            KpErrorProc.OutputErrorMessage(retc, WSAGetLastError(), bOutMsg, __FILE__, __LINE__, 0L);
         }

         m_PackedUrl.m_Addr.S_un.S_addr = INADDR_BROADCAST; // INADDR_ANY; //
      }
      else // if(strcmp(m_PackedUrl.m_lpszServerName, KP_IPADDR_BROADCAST) == 0)
      {
// ------------------------------
// lookup the address for the server name
         m_PackedUrl.m_Addr.S_un.S_addr = inet_addr((const char *)m_PackedUrl.m_lpszServerName);
         if(INADDR_NONE==m_PackedUrl.m_Addr.S_un.S_addr)
         {
// ------------------
#if FALSE
            sprintf(port, m_PackedUrl.m_iPort);

            memset(&aiHints, 0, sizeof(aiHints));
            aiHints.ai_family = AF_INET;
            aiHints.ai_socktype = SOCK_STREAM;
            aiHints.ai_protocol = IPPROTO_TCP;

            retVal = getaddrinfo(m_PackedUrl.m_lpszServerName, port, &aiHints, &aiList);
            if(retVal)
            {
               KP_NEWA(msg_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

               if(SUCCEEDED(retc))
               {
                  strcpy(msg_buf, m_PackedUrl.m_lpszServerName);
                  strcat(msg_buf, ": ");
                  retc=KpErrorProc.FormatErrorMessageSystem(retVal, msg_buf+strlen(m_PackedUrl.m_lpszServerName)+2, True);
               }
               if(SUCCEEDED(retc))
               {
                  retc=KP_E_NO_CONN;
                  KpErrorProc.OutputErrorMessage(retc, msg_buf, bOutMsg, __FILE__, __LINE__, 0L);
               }

               KP_DELETEA(msg_buf);
            }
            if(SUCCEEDED(retc))
            {
               m_PackedUrl.m_Addr.S_un.S_addr=aiList....???;
            }
#endif

#if TRUE // FALSE
            p_host = gethostbyname((const char *)m_PackedUrl.m_lpszServerName);
            if(NULL == p_host)
            {
               KP_NEWA(msg_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

long retw = WSAGetLastError();
               if(SUCCEEDED(retc))
               {
                  strcpy(msg_buf, m_PackedUrl.m_lpszServerName);
                  strcat(msg_buf, ": ");
                  retc = KpErrorProc.FormatErrorMessageSystem(retw, msg_buf + strlen(m_PackedUrl.m_lpszServerName) + 2, True);
               }
               if(SUCCEEDED(retc))
               {
                  KP_WARNING0(KP_E_NO_CONN, m_PackedUrl.m_lpszServerName);
                  if(bOutMsg && (retw == WSANO_DATA /* WSAEACCES */)) PutMsgFirewall(KP_MSG_FIREWALL);
                  else KP_ASSERTE(False, KP_E_NO_CONN, msg_buf, bOutMsg);
                  retc = KP_E_NO_CONN;
               }

               KP_DELETEA(msg_buf);
            }

            if(SUCCEEDED(retc))
            {
               memcpy((char FAR *)&(m_PackedUrl.m_Addr.S_un.S_addr), p_host->h_addr, sizeof(unsigned long) /* p_host->h_length */);
//             m_PackedUrl.m_Addr.S_un.S_addr=(*p_host->h_addr);
            }
#endif
         }

      } // else // if(strcmp(m_PackedUrl.m_lpszServerName, KP_IPADDR_BROADCAST) == 0)

   }

#if FALSE // #ifdef Debug
char str_buf[1000];
sprintf(str_buf, "lpszServerName:   %s", m_PackedUrl.m_lpszServerName);
KP_TRACE(str_buf);
sprintf(str_buf, "m_lAddr:          %d.%d.%d.%d", m_PackedUrl.m_Addr.S_un.S_addr % 256, (m_PackedUrl.m_Addr.S_un.S_addr / 0x100) % 256, (m_PackedUrl.m_Addr.S_un.S_addr / 0x10000) % 256, (m_PackedUrl.m_Addr.S_un.S_addr / 0x1000000) % 256);
KP_TRACE(str_buf);
sprintf(str_buf, "m_iProtocol:      %s", ProtocolNames[m_PackedUrl.m_iProtocol]);
KP_TRACE(str_buf);
sprintf(str_buf, "m_iPort:          %d", m_PackedUrl.m_iPort);
KP_TRACE(str_buf);
sprintf(str_buf, "lpszFileName:     %s", m_PackedUrl.lpszFileName);
KP_TRACE(str_buf);
#endif

return(retc);
}


//---------------------
void PutMsgFirewall(const unsigned char *lpszMsgFmt)
{
HRESULT retc = S_OK;

static unsigned char ap_name[KP_MAX_FNAME_LEN + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char name[KP_MAX_FNAME_LEN + 1];
static unsigned char type[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszMsgFmt != null, E_INVALIDARG, null, True);

unsigned char *str_buf = null;
   KP_NEWA(str_buf, unsigned char, KP_MAX_FNAME_LEN + strlen(lpszMsgFmt) + 100);

   if(SUCCEEDED(retc)) retc = GetAppName(ap_name);
   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, name, type, ap_name);
   if(SUCCEEDED(retc))
   {
      strcpy(ap_name, name);
      strcat(ap_name, ".");
      strcat(ap_name, type);
   }
   if(FAILED(retc)) ap_name[0] = Nul;
   sprintf((char *)str_buf, (const char *)lpszMsgFmt, ap_name);
   KpMsgOut(str_buf, IDI_WARNING /* IDI_ERROR */, KP_MB_TESTI); // KP_MB_BAIGTI);

   KP_DELETEA(str_buf);
}


//---------------------
HRESULT KpSocket::Connect(bool bOutMsg)
{
HRESULT retc = S_OK;
SOCKADDR_IN sin;

   if((m_hSocket==INVALID_SOCKET) && SUCCEEDED(retc))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, KP_MSG_NO_SOCKET, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if((m_PackedUrl.m_Addr.S_un.S_addr == INADDR_NONE) && SUCCEEDED(retc))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, KP_MSG_SOCK_UNRESOLVED, bOutMsg, __FILE__, __LINE__, 0L);
   }

// connect to remote endpoint
   if(SUCCEEDED(retc))
   {
      sin.sin_family = AF_INET;
      sin.sin_addr.s_addr = m_PackedUrl.m_Addr.S_un.S_addr;
      sin.sin_port = htons(m_PackedUrl.m_iPort /* HTTP_PORT */);

      if(connect(m_hSocket, (LPSOCKADDR)&sin, sizeof (sin)))
      {
         retc = KP_E_NO_CONN;
long retw = WSAGetLastError();
         if(bOutMsg && (retw == WSAEACCES)) PutMsgFirewall(KP_MSG_FIREWALL);
         else KpErrorProc.OutputErrorMessage(retc, retw, bOutMsg, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}


//---------------------
HRESULT KpSocket::Bind(int iPort, unsigned long lAddr, bool bOutMsg)
{
HRESULT retc=S_OK;
// mingw 3.15 ir vëlesniems, Open Watcom v1.8 ( > 1.1)
#if FALSE // (((CompilerGr == Mingw) && (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION >= 315)) || ((CompilerGr == Watcom) && (__WATCOMC__ >= 1202)))
SOCKADDR_STORAGE sin;
#else
SOCKADDR_IN sin;
#endif
const unsigned char *ip_addr;


   if((m_hSocket==INVALID_SOCKET) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, KP_MSG_NO_SOCKET, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      memset(&sin, 0, sizeof(sin));
      ((SOCKADDR_IN *)&sin)->sin_family = AF_INET;
      ((SOCKADDR_IN *)&sin)->sin_addr.s_addr = lAddr; // ADDR_ANY;
      ((SOCKADDR_IN *)&sin)->sin_port = htons(iPort);
   }

   if(SUCCEEDED(retc))
   {
      m_PackedUrl.m_Addr.S_un.S_addr = lAddr;

      ip_addr = (const unsigned char *)inet_ntoa(sin.sin_addr);
      if(ip_addr == NULL)
      {
         KP_WARNING(KP_E_NO_CONN, null);
         ip_addr = KP_IPADDR_LOCAL_HOST;
      }
      strncpy(m_PackedUrl.m_lpszServerName, ip_addr, KP_MAX_FNAME_LEN);
      m_PackedUrl.m_lpszServerName[KP_MAX_FNAME_LEN] = Nul;
      strcpy(m_PackedUrl.m_lpszServerNameUnres, m_PackedUrl.m_lpszServerName);

      m_PackedUrl.m_iPort = iPort;
   }

// SO_REUSEADDR – Vistoje antrà kartà paleidþiant programà portà rodo uþimtà, nors socketas jau seniausiai sunaikintas
// http://msdn.microsoft.com/en-us/library/ms740621(VS.85).aspx
#if FALSE
   if(SUCCEEDED(retc))
   {
int optval = True; // -1;

      if(setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, WSAGetLastError(), True, __FILE__, __LINE__, 0L);
   }
#endif

// Multicast IP programming
// MCAST_JOIN_GROUP – Vistoje antrà kartà paleidþiant programà á naujà klausymo portà paketai neateina – senas lieka uþëmæs, nors procesas/threadas jau ir neveikia
// atrodo, problemos neiðsprendþia – veikia tik nuo Windows Server 2008, Vistos kliente ne
// be to: only valid on datagram and raw sockets
// http://msdn.microsoft.com/en-us/library/ms739172(VS.85).aspx
// http://msdn.microsoft.com/en-us/library/bb427440(VS.85).aspx
// mingw 3.15 ir vëlesniems, Open Watcom v1.8 ( > 1.1)
#if FALSE // (((CompilerGr == Mingw) && (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION >= 315)) || ((CompilerGr == Watcom) && (__WATCOMC__ >= 1202)))

static IP_ADAPTER_ADDRESSES adapters[100];

   if(SUCCEEDED(retc))
   {
ULONG ad_size = sizeof(adapters);
ULONG retw;

      retw = GetAdaptersAddresses(AF_INET, 0L, NULL, adapters, &ad_size);
      if(ERROR_SUCCESS != retw)
         retc = KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, retw, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
GROUP_REQ group_req;

      group_req.gr_interface = adapters[0].IfIndex;
      memcpy(&group_req.gr_group, &sin, sizeof(group_req.gr_group));

      if(setsockopt(m_hSocket, IPPROTO_IP, MCAST_JOIN_GROUP, (const char *)&group_req, sizeof(group_req)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, WSAGetLastError(), True, __FILE__, __LINE__, 0L);
   }

#endif

// connect to local listenning port
   if(SUCCEEDED(retc))
   {
      if(bind(m_hSocket, (LPSOCKADDR)&sin, sizeof (sin)))
      {
// tux_ipa reikia du kartus InitStApp(), antrà kartà portas jau uþimtas
//       retc = KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, WSAGetLastError(), True, __FILE__, __LINE__, 0L);
         retc = KP_E_NO_CONN;
         KpErrorProc.OutputErrorMessage(retc, WSAGetLastError(), bOutMsg, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}



//---------------------
HRESULT KpSocket::Listen(void)
{
HRESULT retc=S_OK;

//
// // Declare variables
// SOCKET ListenSocket;
// sockaddr_in saServer;
// hostent* localHost;
// char* localIP;
//
// // Create a listening socket
// ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
// // Get the local host information
// localHost = gethostbyname("");
// localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
//
// // Set up the sockaddr structure
// saServer.sin_family = AF_INET;
// saServer.sin_addr.s_addr = inet_addr(localIP);
// saServer.sin_port = htons(5150);
//
// // Bind the listening socket using the
// // information in the sockaddr structure
// bind( ListenSocket,(SOCKADDR*) &saServer, sizeof(saServer) );
//

   if((m_hSocket==INVALID_SOCKET) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, KP_MSG_NO_SOCKET, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_hAccSock!=INVALID_SOCKET)
         if(closesocket(m_hAccSock))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), True, __FILE__, __LINE__, 0L);
      m_hAccSock=INVALID_SOCKET;
   }

   if(SUCCEEDED(retc))
      if(listen(m_hSocket, 1 /* SOMAXCONN */))
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, WSAGetLastError(), True, __FILE__, __LINE__, 0L);

return(retc);
}


//---------------------
HRESULT KpSocket::Accept(void)
{
HRESULT retc=S_OK;
SOCKADDR_IN sin;
//
// struct sockaddr_in {
//         short   sin_family;
//         u_short sin_port;
//         struct  in_addr sin_addr;
//         char    sin_zero[8];
// };
// typedef struct in_addr {
//   union {
//     struct {
//       u_char s_b1,s_b2,s_b3,s_b4;
//     } S_un_b;
//     struct {
//       u_short s_w1,s_w2;
//     } S_un_w;
//     u_long S_addr;
//   } S_un;
// } IN_ADDR;
//

int addrlen;
const unsigned char *ip_addr;


   if((m_hSocket==INVALID_SOCKET) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, KP_MSG_NO_SOCKET, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_hAccSock!=INVALID_SOCKET)
         if(closesocket(m_hAccSock))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), True, __FILE__, __LINE__, 0L);
      m_hAccSock=INVALID_SOCKET;
   }

   if(SUCCEEDED(retc))
   {
      sin.sin_family=AF_INET;
      sin.sin_addr.s_addr = 0;
      sin.sin_port=htons(m_PackedUrl.m_iPort /* HTTP_PORT */);

      addrlen=sizeof(sin);

      m_hAccSock=accept(m_hSocket, (LPSOCKADDR)&sin, &addrlen);
      if(m_hAccSock==INVALID_SOCKET)
      {
// praneðimo nereikia, kai klaida atsiranda programos pabaigoje stabdant threadà
long ll = WSAGetLastError();
         if(ll != WSAEINTR) // 10004) // A blocking operation was interrupted by a call to WSACancelBlockingCall
            retc = KpErrorProc.OutputErrorMessage(KP_E_NO_CONN, ll, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      ip_addr = (const unsigned char *)inet_ntoa(sin.sin_addr);
      if(ip_addr == NULL)
      {
         KP_WARNING(KP_E_NO_CONN, null);
         ip_addr = KP_IPADDR_LOCAL_HOST;
      }

      strncpy(m_PackedUrl.m_lpszServerName, ip_addr, KP_MAX_FNAME_LEN);
      m_PackedUrl.m_lpszServerName[KP_MAX_FNAME_LEN] = Nul;
      strcpy(m_PackedUrl.m_lpszServerNameUnres, m_PackedUrl.m_lpszServerName);
      m_PackedUrl.m_Addr.S_un.S_addr = sin.sin_addr.S_un.S_addr;
      m_PackedUrl.m_iProtocol=HTTP_PROT;
      m_PackedUrl.m_iPort=sin.sin_port;
      m_PackedUrl.m_lpszFileName[0]=Nul;
   }

#if FALSE // #ifdef Debug
unsigned char str_buf[300];
sprintf((char *)str_buf,
"------------------- Socket accepted:\n"\
"   sin_family: %d\n"\
"   sin_port: %d\n"\
"   sin_addr.S_un.S_addr: %lx\n"\
"   sin_zero: %s\n"\
"   IP: %s\n",\
sin.sin_family,
sin.sin_port,
sin.sin_addr.S_un.S_addr,
sin.sin_zero,
inet_ntoa(sin.sin_addr)
);
KP_TRACE(str_buf);
#endif

return(retc);
}


//---------------------
HRESULT KpSocket::SendTo(const unsigned char *pBuf, long lBufLen, bool bOutMsg)
{
HRESULT retc = S_OK;
int retv = 0;
SOCKADDR_IN sin;

   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = m_PackedUrl.m_Addr.S_un.S_addr;
   sin.sin_port = htons(m_PackedUrl.m_iPort);

   retv = sendto(m_hSocket, (const char *)pBuf, lBufLen, 0, (SOCKADDR *)&sin, sizeof(sin));
   KP_ASSERT(retv != SOCKET_ERROR, retc = KP_E_TRANS_ERR, WSAGetLastError(), bOutMsg);

return(retc);
}


// -------------------------------------
HRESULT KpSocket::RecvFrom(unsigned char *pBuf, long *plBufLen, bool bOutMsg)
{
HRESULT retc = S_OK;
SOCKADDR_IN sin;
int sin_len = sizeof(SOCKADDR_IN);
long ll;
const unsigned char *ip_addr;

   KP_ASSERT(pBuf, E_INVALIDARG, null, True);
   KP_ASSERT(plBufLen, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      ll = *plBufLen;

      ll = recvfrom(m_hSocket, (char *)pBuf, ll, 0 /* MSG_PEEK */, (PSOCKADDR)&sin, &sin_len);
      KP_ASSERT(ll != SOCKET_ERROR, retc = KP_E_TRANS_ERR, WSAGetLastError(), bOutMsg);
   }

   if(SUCCEEDED(retc))
   {
      *plBufLen = ll;

      m_PackedUrl.m_Addr.S_un.S_addr = sin.sin_addr.s_addr;

      ip_addr = (const unsigned char *)inet_ntoa(sin.sin_addr);
      if(ip_addr == NULL)
      {
         KP_WARNING(KP_E_NO_CONN, null);
         ip_addr = KP_IPADDR_LOCAL_HOST;
      }
      strncpy(m_PackedUrl.m_lpszServerName, ip_addr, KP_MAX_FNAME_LEN);
      m_PackedUrl.m_lpszServerName[KP_MAX_FNAME_LEN] = Nul;
      strcpy(m_PackedUrl.m_lpszServerNameUnres, m_PackedUrl.m_lpszServerName);
   }

return(retc);
}


DWORD WINAPI RecvFromProc(LPVOID lpParameter)
{
HRESULT retc = S_OK;
RecvFromProcPars *pars_ptr = (RecvFromProcPars *)lpParameter;

   KP_ASSERT(pars_ptr, E_INVALIDARG, null, True);
   KP_ASSERT(pars_ptr->m_This, E_INVALIDARG, null, True);
   KP_ASSERT(pars_ptr->m_pBuf, E_INVALIDARG, null, True);
   KP_ASSERT(pars_ptr->m_plBufLen, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = pars_ptr->m_This->RecvFrom(pars_ptr->m_pBuf, pars_ptr->m_plBufLen, pars_ptr->m_bOutMsg);

// send notification
   if(SUCCEEDED(retc)) PostThreadMessage(pars_ptr->m_iCallersThreadId, KP_BLOCKED_SOCK_RELEASED, 0, 0L);

return(RET_CODE_MAIN(retc));
}


HRESULT KpSocket::RecvFromAsynch(unsigned char *pBuf, long *plBufLen, bool bOutMsg)
{
HRESULT retc = S_OK;
HANDLE rcv_thread;
UINT rcv_timer = 0;
MSG msg;
int retp;
RecvFromProcPars pars;
bool endfl = False;

   KP_ASSERT(pBuf, E_INVALIDARG, null, True);
   KP_ASSERT(plBufLen, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pars.m_This = this;
      pars.m_pBuf = pBuf;
      pars.m_plBufLen = plBufLen;
      pars.m_bOutMsg = bOutMsg;
      pars.m_iCallersThreadId = GetCurrentThreadId();

      rcv_thread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         RecvFromProc,      // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         (LPVOID)&pars,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         NULL     // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      KP_ASSERT(rcv_thread, retc = KP_E_SYSTEM_ERROR, GetLastError(), bOutMsg);
   }

   if(SUCCEEDED(retc))
   {
      rcv_timer = SetTimer(HWND_DESKTOP, KP_TIMEOUT_TIMER, KPSOCK_BLOCK_TIMEOUT * 1000, NULL);
      KP_ASSERT(rcv_timer, retc = KP_E_SYSTEM_ERROR, GetLastError(), bOutMsg);
   }

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0) KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp = LOWORD(msg.wParam);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case KP_BLOCKED_SOCK_RELEASED:
         endfl = True;
         break;

      case WM_TIMER:
         if(SUCCEEDED(retc)) if(retp == rcv_timer)
         {
            KP_ASSERT(TerminateThread(rcv_thread, RET_CODE_MAIN(KP_E_TIMEOUT)), KP_E_SYSTEM_ERROR, GetLastError(), False);
            rcv_thread = NULL;

            endfl = True;
            retc = KP_E_NO_CONN; // KP_E_TIMEOUT;

         } // if(SUCCEEDED(retc)) if(retp == rcv_timer)

         break; // case WM_TIMER:

      case WM_COMMAND:
         switch(retp)
         {
         case IDCANCEL:
            endfl = True;
            retc = KP_E_CANCEL;
            break;
         }
         break;

      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      } // if(SUCCEEDED(retc)) switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));

   if(FAILED(retc)){ if(bOutMsg) KP_ERROR(retc, null) else KP_WARNING0(retc, null);}

   if(rcv_timer) KillTimer(HWND_DESKTOP, rcv_timer);
   rcv_timer = 0;

return(retc);
}


//---------------------
HRESULT KpSocket::SendMsg(const unsigned char *pBuf, long lBufLen, bool bOutMsg)
{
HRESULT retc = S_OK;
const unsigned char *p_temp = pBuf;
int cb_sent;
int cb_remaining = lBufLen;
SOCKET socket = INVALID_SOCKET;

   if(lBufLen != 0)
   {
      if((pBuf == NULL) && SUCCEEDED(retc))
      {
         retc = E_INVALIDARG;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         socket = m_hSocket;
         if(m_hAccSock != INVALID_SOCKET) socket=m_hAccSock;
         if(socket == INVALID_SOCKET)
         {
            retc = KP_E_SYSTEM_ERROR;
            KpErrorProc.OutputErrorMessage(retc, KP_MSG_NO_SOCKET, bOutMsg, __FILE__, __LINE__, 0L);
         }
      }

// PutLogMessage_("SendMsg() 1: %d", cb_remaining);
      if(SUCCEEDED(retc))
      {
         while((cb_remaining>0) && SUCCEEDED(retc))
         {
            cb_sent = send(socket, (const char *)p_temp, cb_remaining, 0);
            if(SOCKET_ERROR == cb_sent)
            {
               retc = KP_E_TRANS_ERR;
               KpErrorProc.OutputErrorMessage(retc, WSAGetLastError(), bOutMsg, __FILE__, __LINE__, 0L);
               KpErrorProc.OutputErrorMessage(retc, m_PackedUrl.m_lpszServerName, False, __FILE__, __LINE__, (long)hKpInstance);
            }
// PutLogMessage_("SendMsg() 2: rem: %d sent: %d", cb_remaining, cb_sent);

            if(SUCCEEDED(retc))
            {
               p_temp += cb_sent;
               cb_remaining -= cb_sent;
            }
         }
      }

   } // if(cbBuf!=0)

// KP_TRACE(pBuf);

#if FALSE // #ifdef Debug // #if TRUE //
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("-- SendMsg() -------------------\n>>>\n", out_file);
fputs((const char *)pBuf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif

return(retc);
}


//---------------------
HRESULT KpSocket::SendStr(const unsigned char *lpszBuf)
{
return(SendMsg(lpszBuf, strlen(lpszBuf), True));
}


//---------------------
HRESULT KpSocket::SendStr(const char *lpszBuf)
{
return(SendMsg((const unsigned char *)lpszBuf, strlen(lpszBuf), True));
}


//---------------------
HRESULT KpSocket::SendHttpRequest(const unsigned char *lpszRequest, const unsigned char *lpszArg, bool bOutMsg,
   long lSimplyPostMsgLen, bool bAcroPostMsg, const unsigned char *lpszPostBoundary, const unsigned char *lpszHTTP_Template)
{
HRESULT retc=S_OK;
unsigned char *buf_ptr=NULL;
const unsigned char *http_tpl=(const unsigned char *)"";

   KP_ASSERT(lpszRequest != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszArg != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszHTTP_Template != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lSimplyPostMsgLen >= 0L, E_INVALIDARG, null, True);

   KP_ASSERTE(m_PackedUrl.m_iProtocol == HTTP_PROT, KP_E_SYSTEM_ERROR, null, bOutMsg);

   if(SUCCEEDED(retc)) if(strcmp(lpszRequest, HTTP_GET_REQUEST_CMD) == 0)
   {
      KP_ASSERTE(lSimplyPostMsgLen == 0L, E_INVALIDARG, null, bOutMsg);
      if(SUCCEEDED(retc)) http_tpl = lpszHTTP_Template;
   }

   if(SUCCEEDED(retc)) if(strcmp(lpszRequest, HTTP_POST_REQUEST_CMD) == 0)
   {
      if(lSimplyPostMsgLen==0L)
      {
         retc=E_NOTIMPL;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) http_tpl = bAcroPostMsg?HTTP_POST_REQ_TPL_ACRO:HTTP_POST_REQ_TPL;
   }

   KP_NEWA(buf_ptr, unsigned char, strlen(http_tpl) + strlen(lpszRequest) + strlen(lpszArg) + strlen(m_PackedUrl.m_lpszServerName) + 1000);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)buf_ptr, (const char *)http_tpl, lpszRequest, lpszArg, m_PackedUrl.m_lpszServerName, m_PackedUrl.m_iPort, lpszProdName, lSimplyPostMsgLen);
#if FALSE
// KP_TRACE(buf_ptr);
fstream out_file("KpPostHead.txt", ios_base::out | ios_base::binary);
out_file << buf_ptr;
out_file.close();
#endif
#ifdef TRACE_HTTP
{
static unsigned char str_buf_1[4500 + 1];
strncpy(str_buf_1, buf_ptr, 4500);
str_buf_1[4500] = Nul;
PutLogMessage_("KpSocket::SendHttpRequest() 1:\n%s\n", str_buf_1);
}
#endif
      retc = SendMsg(buf_ptr, strlen(buf_ptr), bOutMsg);
   }

   if((!bAcroPostMsg) && SUCCEEDED(retc)) if(strcmp(lpszRequest, HTTP_POST_REQUEST_CMD) == 0)
   {
      sprintf((char *)buf_ptr, (const char *)HTTP_POST_REQ_TAIL_TPL, m_PackedUrl.m_lpszServerName, lpszArg, lpszPostBoundary);
#if FALSE
// KP_TRACE(buf_ptr);
fstream out_file("KpPostHeadTail.txt", ios_base::out | ios_base::binary);
out_file << buf_ptr;
out_file.close();
#endif
#ifdef TRACE_HTTP
{
static unsigned char str_buf_1[4500 + 1];
strncpy(str_buf_1, buf_ptr, 4500);
str_buf_1[4500] = Nul;
PutLogMessage_("KpSocket::SendHttpRequest() 2:\n%s\n", str_buf_1);
}
#endif
      retc = SendMsg(buf_ptr, strlen(buf_ptr), bOutMsg);
   }

   KP_DELETEA(buf_ptr);

return(retc);
}


//---------------------
HRESULT KpSocket::ReceiveMsg(unsigned char *pBuf, long *plRead, bool bSingleMsg, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char *p_temp=pBuf;
long cb_read;
long cb_remaining;
long buf_len;
SOCKET socket=INVALID_SOCKET;

   if(((pBuf==NULL) || (plRead==NULL)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      buf_len=cb_remaining=*plRead;

      socket=m_hSocket;
      if(m_hAccSock!=INVALID_SOCKET) socket=m_hAccSock;
      if(socket==INVALID_SOCKET)
      {
         retc=KP_E_NO_CONN;
         KpErrorProc.OutputErrorMessage(retc, KP_MSG_NO_SOCKET, bOutMsg, __FILE__, __LINE__, 0L);
      }
   }

   while((cb_remaining > 0) && SUCCEEDED(retc))
   {
// KP_TRACE("ReceiveMsg(): entering recv()");
      cb_read = recv(socket, (char *)p_temp, cb_remaining, 0);
// KP_TRACE("ReceiveMsg(): recv()");

      if(SOCKET_ERROR == cb_read)
      {
         retc = KP_E_TRANS_ERR;
         KpErrorProc.OutputErrorMessage(retc, WSAGetLastError(), bOutMsg, __FILE__, __LINE__, 0L);
         KpErrorProc.OutputErrorMessage(retc, m_PackedUrl.m_lpszServerName, False, __FILE__, __LINE__, (long)hKpInstance);
      }

      if(SUCCEEDED(retc))
      {
         cb_remaining-=cb_read;
         p_temp+=cb_read;
      }

      if(cb_read==0) break;

      if(bSingleMsg) break;
   }

   if(SUCCEEDED(retc))
      *plRead=buf_len-cb_remaining;

return(retc);
}


//---------------------
HRESULT KpSocket::GetChar(unsigned char *pcInChar, bool bOutMsg)
{
HRESULT retc=S_OK;
long read = 1L;

   if((pcInChar==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) retc = ReceiveMsg(pcInChar, &read, True, bOutMsg);
// KP_TRACE("KpSocket::GetChar(): ReceiveMsg()");

   KP_ASSERTE(read >= 1L, KP_E_EOF, null, False /* bOutMsg */);

return(retc);
}


//---------------------
HRESULT KpSocket::GetCharD(unsigned char *pcInChar, bool bOutMsg)
{
HRESULT retc=S_OK;

   if((pcInChar==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lContLen--;
      if(m_lContLen<0L)
      {
         m_lContLen=0L;
         retc=KP_E_EOF;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) retc=GetChar(pcInChar, bOutMsg);

return(retc);
}


//---------------------
HRESULT KpSocket::GetLine(unsigned char *lpszStrBuf, int iBufLen, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char *pntd;
unsigned char in_ch;

   if(((lpszStrBuf==NULL) || (iBufLen<1)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      pntd=lpszStrBuf;

      do
      {
         retc=GetCharD(&in_ch, bOutMsg);

         if(retc==KP_E_EOF)
         {
            if(pntd>lpszStrBuf) // paskutine eilute be Lf
            {
               retc=S_OK;
               in_ch=Lf;
               *pntd=Nul;
            }
         }
         else if((in_ch!=Cr) && SUCCEEDED(retc))
         {
            if(in_ch==Lf) *pntd=Nul;
            else
            {
               if(pntd-lpszStrBuf>=iBufLen-1)
               {
                  *pntd=Nul;
                  retc=KP_E_BUFFER_OVERFLOW;
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }
               else (*pntd++) = in_ch;
            }
         }

      } while((in_ch!=Lf) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

return(retc);
}


//---------------------
HRESULT KpSocket::ReceiveHdr(HttpMsgTypes iMsgType, long *plRead, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char *pntd;
bool endfl=False;

// if((plRead==NULL) && SUCCEEDED(retc))
// {
//    retc=E_INVALIDARG;
//    KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
// }

   if(SUCCEEDED(retc)) pntd=m_lpszHdrBuf;

   while((!endfl) && SUCCEEDED(retc))
   {
      if(pntd-m_lpszHdrBuf >= MAX_HTTP_HDR_LEN - 1)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         if(iMsgType == HTTP_POST_DATA_SEGM) retc = GetCharD(pntd, bOutMsg);
         else retc = GetChar(pntd, bOutMsg);
// KP_TRACE_1("ReceiveHdr(): GetChar(): %c", *pntd);

         if(SUCCEEDED(retc)) pntd++;
         else if(retc == KP_E_EOF)
         {
            retc = S_OK;
            endfl = True;
         }
      }
      if(SUCCEEDED(retc)) *pntd = Nul;

      if(SUCCEEDED(retc)) if(pntd - m_lpszHdrBuf > 2) if(strcmp(pntd - 2, "\n\n") == 0) endfl = True;
      if(SUCCEEDED(retc)) if(pntd - m_lpszHdrBuf > 3) if(strcmp(pntd - 3, "\n\r\n") == 0) endfl = True;
   }
// KP_TRACE("ReceiveHdr(): hdr received");
// KP_TRACE(m_lpszHdrBuf);

   if((plRead) && SUCCEEDED(retc)) *plRead = pntd - m_lpszHdrBuf;

   if(
      (
         (pntd - m_lpszHdrBuf == 0) ||
         (pntd - m_lpszHdrBuf > MAX_HTTP_HDR_LEN) ||
         ((pntd - m_lpszHdrBuf < MIN_HTTP_HDR_LEN) && (iMsgType != HTTP_POST_DATA_SEGM))
      ) && SUCCEEDED(retc)
     )
   {
//    retc = KP_E_TRANS_ERR;
//    KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_TRANS_ERR, null, False, __FILE__, __LINE__, 0L);
   }

#if FALSE // #ifdef Debug // #if TRUE //
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("-- ReceiveHdr() -------------------\n>>>\n", out_file);
fputs((const char *)m_lpszHdrBuf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif

#if FALSE
KpMsgOut(m_lpszHdrBuf, IDI_ASTERISK, KP_MB_TESTI);
fstream out_file("rcv.txt", ios::out);
out_file << m_lpszHdrBuf;
out_file.close();
#endif

// PutLogMessage_("ReceiveHdr(): %x\n>>>\n%s\n<<<\n", retc, m_lpszHdrBuf);

return(retc);
}


// ======================================================
// HTTP_REPLY:

// HTTP/1.1 200 OK
// Date: Mon, 19 Jul 2004 06:43:58 GMT
// Server: Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2
// Last-Modified: Thu, 15 Jul 2004 16:29:04 GMT
// ETag: "23-40f6b0d0"
// Accept-Ranges: bytes
// Content-Length: 35
// Connection: close
// Content-Type: text/plain
//
// KpReg-Error: Licenzija jau u_imta

// HTTP/1.1 200 OK
// Date: Mon, 28 Aug 2006 12:48:24 GMT
// Server: Apache
// Keep-Alive: timeout=1, max=100
// Connection: Keep-Alive
// Transfer-Encoding: chunked
// Content-Type: text/html
// Content-Encoding: gzip
//
// 31
// º<<<
// <...>

// HTTP/1.1 200 OK
// Date: Mon, 28 Aug 2006 12:54:21 GMT
// Server: Apache
// Content-Encoding: none
// Keep-Alive: timeout=1, max=100
// Connection: Keep-Alive
// Transfer-Encoding: chunked
// Content-Type: text/html
//
// 1d
// KpReg-Ok: AA2L-3U81-21A7-GG4R
// 0
// <...> - dar pora baitu, atrodo


// atsakymas ið http://new.tev.lt/content.php

// HTTP/1.1 200 OK
// Date: Wed, 07 Sep 2011 15:29:11 GMT
// Server: Apache
// Set-Cookie: PHPSESSID=1e64d5b45db8cbb16a618dd6ec621c88; path=/
// Expires: Thu, 19 Nov 1981 08:52:00 GMT
// Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
// Pragma: no-cache
// Keep-Alive: timeout=1, max=100
// Connection: Keep-Alive
// Transfer-Encoding: chunked
// Content-Type: text/html
// Content-Encoding: gzip
//


// atsakymas ið http://mindep.puslapiai.lt/pr/MaTau-9v_diegimas.exe

// HTTP/1.1 404 Not Found
// Date: Wed, 07 Sep 2011 15:38:39 GMT
// Server: Apache
// Last-Modified: Sat, 13 Sep 2008 11:41:48 GMT
// ETag: "780890-69a-48cba6fc;4be2fc45"
// Accept-Ranges: bytes
// Content-Length: 1690
// Connection: close
// Content-Type: text/html
//


// atsakymas rezultatai.pdf failui i at'post'intus duomenis

// HTTP/1.1 200 OK
// Date: Mon, 19 Jul 2004 06:43:58 GMT             // ????
// Server: kpstlsvr
// Last-Modified: Thu, 15 Jul 2004 16:29:04 GMT    // ????
// ETag: "23-40f6b0d0"                             // ????
// Accept-Ranges: bytes                            // ????
// Content-Length: 35
// Connection: close
// Content-type: application/vnd.fdf
//
// <...> (xxx.fdf failas)

// --------------------------------------
// Gintaro atsakymas á Tado klausimà apie update

// kai POST /

// HTTP/1.1 302 Found
// Date: Wed, 27 Feb 2008 11:45:02 GMT
// Server: Apache
// Location: http://new.tev.lt/inc/rlink.php?sector=update&kalba=LT
// Transfer-Encoding: chunked
// Content-Type: text/html
//
// 0

// kai POST /versija.php

// HTTP/1.1 302 Found
// Date: Wed, 27 Feb 2008 13:35:53 GMT
// Server: Apache
// Location: http://new.tev.lt/
// Transfer-Encoding: chunked
// Content-Type: text/html
//
// 0

// kai Gintaras pataise, kad priimtu is User-Agent: lzdsh

// HTTP/1.1 200 OK
// Date: Wed, 27 Feb 2008 13:53:38 GMT
// Server: Apache
// Transfer-Encoding: chunked
// Content-Type: application/vnd.fdf

// ======================================================
// HTTP_REQUEST_UNKNOWN:
// HTTP_GET_REQUEST:

// GET /favicon.ico HTTP/1.1
// Host: 127.0.0.1:49494
// User-Agent: Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax)
// Accept: video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive

// ======================================================
// HTTP_GET_REQUEST:

// GET /abcd HTTP/1.1
// Host: 127.0.0.1:49494
// User-Agent: Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax)
// Accept: application/x-shockwave-flash,text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Cache-Control: max-age=0
//

// GET /prodreg.php?instcode=12JJ-GA96-E5UR-4EJ1 HTTP/1.1
// Host: www.tev.lt
// User-Agent: Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax)
// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
//

// Firefox 3.6.21:

// GET /links.htm HTTP/1.1
// Host: 127.0.0.1:14006
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; lt; rv:1.9.2.21) Gecko/20110830 Firefox/3.6.21
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: lt,en-us;q=0.8,en;q=0.6,ru;q=0.4,pl;q=0.2
// Accept-Encoding: gzip,deflate
// Accept-Charset: windows-1257,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 115
// Connection: keep-alive
// Referer: http://127.0.0.1:14006/
// If-Modified-Since: 2009.04.24
// If-None-Match: "1315402634"
//

// GET /rrr.exe HTTP/1.1
// Host: 127.0.0.1:14006
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; lt; rv:1.9.2.21) Gecko/20110830 Firefox/3.6.21
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: lt,en-us;q=0.8,en;q=0.6,ru;q=0.4,pl;q=0.2
// Accept-Encoding: gzip,deflate
// Accept-Charset: windows-1257,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 115
// Connection: keep-alive
// If-Modified-Since: 2011.09.07
// If-None-Match: "1315404252"
// Cache-Control: max-age=0
//

// ======================================================
// HTTP_GET_REQUEST, "reload current page":

// GET /friends.htm HTTP/1.1
// Host: 127.0.0.1:3010
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.0.6) Gecko/20060728 Firefox/1.5.0.6
// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Referer: http://127.0.0.1:3010/
// If-Modified-Since: 2006-08-23
// If-None-Match: "1156338348"
// Cache-Control: max-age=0
//

// ======================================================
// HTTP_GET_REQUEST, <meta http-equiv="refresh" content="5">:

// GET /status.htm HTTP/1.1
// Host: 127.0.0.1:3010
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.0.6) Gecko/20060728 Firefox/1.5.0.6
// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Pragma: no-cache
// Cache-Control: no-cache


// ======================================================
// HTTP_GET_REQUEST, Opera:

// GET / HTTP/1.1
// User-Agent: Opera/9.02 (Windows NT 5.0; U; en)
// Host: 127.0.0.1:13008
// Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1
// Accept-Language: lt-LT,lt;q=0.9,en;q=0.8
// Accept-Charset: iso-8859-1, utf-8, utf-16, *;q=0.1
// Accept-Encoding: deflate, gzip, x-gzip, identity, *;q=0
// Connection: Keep-Alive


// GET /friends.htm HTTP/1.1
// User-Agent: Opera/9.02 (Windows NT 5.0; U; en)
// Host: 127.0.0.1:13008
// Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1
// Accept-Language: lt-LT,lt;q=0.9,en;q=0.8
// Accept-Charset: iso-8859-1, utf-8, utf-16, *;q=0.1
// Accept-Encoding: deflate, gzip, x-gzip, identity, *;q=0
// Connection: Keep-Alive, TE
// TE: deflate, gzip, chunked, identity, trailers


// ======================================================
// HTTP_GET_REQUEST, IE 7:

// GET /results.htm HTTP/1.1
// Accept: */*
// Accept-Language: lt
// UA-CPU: x86
// Accept-Encoding: gzip, deflate
// If-Modified-Since: Sun, 03 Sep 2000 08:46:12 GMT
// If-None-Match: "1173429969"
// User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)
// Host: 10.2.0.24:13006
// Connection: Keep-Alive
//

// GET /results.htm HTTP/1.1
// Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*
// Accept-Language: lt
// UA-CPU: x86
// Accept-Encoding: gzip, deflate
// If-Modified-Since: Sun, 03 Sep 2000 08:18:38 GMT
// If-None-Match: "1173428315"
// User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)
// Host: 10.2.0.24:13006
// Connection: Keep-Alive
//


// ======================================================
// HTTP_GET_REQUEST, lynx:

// GET /admins.htm HTTP/1.1
// Host: 10.2.0.24:13006
// User-Agent: Links (1.00pre12; Linux 2.6.8-2-386 i686; 80x24) (Debian pkg 0.99+1.00pre12-1sarge1)
// Accept: */*
// Accept-Charset: us-ascii, ISO-8859-1, ISO-8859-2, ISO-8859-4, ISO-8895-5, ISO-8859-7, ISO-8895-9, ISO-8859-13, ISO-8859-15, ISO-8859-16, windows-1250, windows-1251, windows-1257, cp437, cp737, cp850, cp852, cp866, x-cp866-u, x-mac, x-mac-ce, x-kam-cs, koi8-r, koi8-u, TCVN-5712, VISCII, utf-8
// Connection: Keep-Alive
//


// ======================================================
// HTTP_POST_REQUEST, Firefox:
// paskutines dvi eilutes ateina kitu paketu
// is kpstlsvr.exe IP adresu ivedimo formos bandymu

// POST /friends.htm HTTP/1.1
// Host: 127.0.0.1:3010
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.0.6) Gecko/20060728 Firefox/1.5.0.6
// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Referer: http://127.0.0.1:3010/friends.htm
// Content-Type: multipart/form-data; boundary=---------------------------31673223865021
// Content-Length: 142
//


// ======================================================
// HTTP_POST_REQUEST, IE 7:

// POST /admins.htm HTTP/1.1
// Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*
// Referer: http://10.2.0.24:13006/admins.htm
// Accept-Language: lt
// Content-Type: multipart/form-data; boundary=---------------------------7d73089100ca
// UA-CPU: x86
// Accept-Encoding: gzip, deflate
// User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)
// Host: 10.2.0.24:13006
// Content-Length: 239
// Connection: Keep-Alive
// Cache-Control: no-cache
//
// -----------------------------7d73089100ca
// Content-Disposition: form-data; name="ButNum"
//
// 2
// -----------------------------7d73089100ca
// Content-Disposition: form-data; name="IP"
//
// 10.2.0.54
// -----------------------------7d73089100ca--


// ======================================================
// HTTP_POST_REQUEST, lynx:

// POST /admins.htm HTTP/1.1
// Host: 10.2.0.24:13006
// User-Agent: Links (1.00pre12; Linux 2.6.8-2-386 i686; 80x24) (Debian pkg 0.99+1.00pre12-1sarge1)
// Accept: */*
// Accept-Charset: us-ascii, ISO-8859-1, ISO-8859-2, ISO-8859-4, ISO-8895-5, ISO-8859-7, ISO-8895-9, ISO-8859-13, ISO-8859-15, ISO-8859-16, windows-1250, windows-1251, windows-1257, cp437, cp737, cp850, cp852, cp866, x-cp866-u, x-mac, x-mac-ce, x-kam-cs, koi8-r, koi8-u, TCVN-5712, VISCII, utf-8
// Connection: Keep-Alive
// Content-Type: multipart/form-data; boundary=00000000000000000000000000000000
// Content-Length: 217
//
// --00000000000000000000000000000000
// Content-Disposition: form-data; name="ButNum"
//
//
// --00000000000000000000000000000000
// Content-Disposition: form-data; name="IP"
//
// 10.2.0.13
// --00000000000000000000000000000000--


// is Tado rezultatai.pdf

// POST / HTTP/1.1
// Accept: */*
// Content-Type: application/x-www-form-urlencoded
// Content-Length: 92
// User-Agent: AcroForms
// Host: 127.0.0.1:18008
// Cache-Control: no-cache
//


// ======================================================
// HTTP_POST_DATA_SEGM:
// is kpstlsvr.exe IP adresu ivedimo formos bandymu

// -----------------------------31673223865021
// Content-Disposition: form-data; name="IP"
//
// 987
// -----------------------------31673223865021--

// ======================================================
// HTTP_POST_DATA_SEGM:
// HTTP_POST_REQUEST galas:
// is kpstlsvr.exe IP adresu ivedimo formos bandymu

// Content-Type: multipart/form-data; boundary=---------------------------31673223865021
// Content-Length: 142
//

// -----------------------------287452692419072
// Content-Disposition: form-data; name="IP"
//
// 123
// -----------------------------287452692419072
// Content-Disposition: form-data; name="Band"
//
// 456
// -----------------------------287452692419072--

// ======================================================
// HTTP_POST_DATA_SEGM:
// is kpstlsvr.exe IP adresu ivedimo formos
// nepazymeti checkboxai neperduodami

// -----------------------------265001916915724
// Content-Disposition: form-data; name="ButNum"
//
// 1
// -----------------------------265001916915724
// Content-Disposition: form-data; name="check[1]"
//
// on
// -----------------------------265001916915724
// Content-Disposition: form-data; name="check[2]"
//
// on
// -----------------------------265001916915724
// Content-Disposition: form-data; name="IP"
//
//
// -----------------------------265001916915724--

// ======================================================
// HTTP_POST_DATA_SEGM:
// is kpstlsvr.exe IP adresu ivedimo formos per Opera
// galas jau apdorotas, like tik kepures

// POST /friends.htm HTTP/1.1
// User-Agent: Opera/9.02 (Windows NT 5.0; U; en)
// Host: 127.0.0.1:13008
// Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1
// Accept-Language: lt-LT,lt;q=0.9,en;q=0.8
// Accept-Charset: iso-8859-1, utf-8, utf-16, *;q=0.1
// Accept-Encoding: deflate, gzip, x-gzip, identity, *;q=0
// Referer: http://127.0.0.1:13008/friends.htm
// Connection: Keep-Alive, TE
// TE: deflate, gzip, chunked, identity, trailers
// Content-Length: 224
// Content-Type: multipart/form-data; boundary=----------MewvlxgnyxIqwnyLYofnOt
//

// Content-Disposition: form-data; name="ButNum"
//

// Content-Disposition: form-data; name="IP"
//


// ======================================================
// is pavyzdzio apie POST: http://www.w3.org/TR/html4/interact/forms.html
// sitokie duomenys netinka - duomenys ilgesni nei viena eilute,
// be to keli duomenu strukturos lygiai:

// Content-Type: multipart/form-data; boundary=AaB03x
//
// --AaB03x
// Content-Disposition: form-data; name="submit-name"
//
// Larry
// --AaB03x
// Content-Disposition: form-data; name="files"
// Content-Type: multipart/mixed; boundary=BbC04y
//
// --BbC04y
// Content-Disposition: file; filename="file1.txt"
// Content-Type: text/plain
//
// ... contents of file1.txt ...
// --BbC04y
// Content-Disposition: file; filename="file2.gif"
// Content-Type: image/gif
// Content-Transfer-Encoding: binary
//
// ...contents of file2.gif...
// --BbC04y--
// --AaB03x--


// --------------------------------------
// AcroRead 6 ið Tado matau5e/cd/cd5_3.pdf

// POST /?&File_Name=cd5_3.pdf&Start_Time=&Lygis=1%20lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2 HTTP/1.1
// Accept: */*
// Content-Type: application/vnd.fdf
// Content-Length: 1841
// User-Agent: AcroForms
// Host: 127.0.0.1:13010
// Cache-Control: no-cache

// POST /?&File_Name=cd5_3.pdf&Stop_Time=2006.09.25%2014:07:22&Pateikta_uzd_sk=1&Teisingai_sk=&Neteisingai_sk=1 HTTP/1.1
// Accept: */*
// Content-Type: application/vnd.fdf
// Content-Length: 1862
// User-Agent: AcroForms
// Host: 127.0.0.1:13010
// Cache-Control: no-cache

// --------------------------------------
// AcroRead 7 ið Tado PP11-12 kreipinys á kpstisvr.exe dël ArkSh.exe paleidimo

// POST / HTTP/1.1
// Accept: */*
// Content-Type: application/x-www-form-urlencoded
// Content-Length: 42
// Acrobat-Version: 7.0.8
// User-Agent: AcroForms
// Host: 127.0.0.1:49494
// Connection: Keep-Alive
// Cache-Control: no-cache

// POST / HTTP/1.1
// Accept: */*
// Content-Type: application/x-www-form-urlencoded
// Content-Length: 44
// User-Agent: AcroForms
// Host: 127.0.0.1:49494
// Cache-Control: no-cache
//
// EXT_f1010101=failai%2ff1010101.doc&f1010101=
//

// --------------------------------------
// AcroRead ð ið Raimio EV9-10 klaidingas kreipinys á kpstisvr.exe dël .doc atvërimo

// POST / HTTP/1.1
// Accept: */*
// Content-Type: multipart/form-data; boundary=---------------------------703890824533759
// Content-Length: 162
// User-Agent: AcroForms
// Host: 127.0.0.1:49494
// Cache-Control: no-cache
//
// -----------------------------703890824533759
// Content-Disposition: form-data; name="EXT_failas"; filename=""
//
//
// -----------------------------703890824533759
// Content-Disposition: form-data; name="aktyvus_1sk_0"
//
//
// -----------------------------703890824533759--

// ----------------------------------------------------
// HTTP/1.1 200 OK
// Date: Thu, 03 May 2012 14:50:55 GMT
// Server: Apache
// Set-Cookie: PHPSESSID=5f15743c7c898d147cabe8385cc4afaa; path=/
// Content-Description: File Transfer
// Content-Disposition: attachment; filename=ekov910_lt_setup.exe
// Content-Transfer-Encoding: binary
// Expires: 0
// Cache-Control: must-revalidate, post-check=0, pre-check=0
// Pragma: public
// Content-Length: 23959329
// Keep-Alive: timeout=1, max=100
// Connection: Keep-Alive
// Content-Type: application/octet-stream
//
// ...
//


HRESULT KpSocket::ScanHdrFileName(unsigned char **plpszHdrPtrPtr, bool bOutMsg)
{
HRESULT retc = S_OK;
int ii;

   KP_ASSERT(plpszHdrPtrPtr != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(*plpszHdrPtrPtr != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      while(**plpszHdrPtrPtr && (strchr(lpszSpaces, **plpszHdrPtrPtr)!=NULL)) (*plpszHdrPtrPtr)++;
      if(strstr(*plpszHdrPtrPtr, "filename=") != *plpszHdrPtrPtr)
      {
         retc = KP_E_KWD_NOT_FOUND;
         KpErrorProc.OutputErrorMessage(retc, *plpszHdrPtrPtr, bOutMsg, __FILE__, __LINE__, 0L);
      }
      else *plpszHdrPtrPtr += strlen("filename=");
   }
   if(SUCCEEDED(retc))
      if(strlen(*plpszHdrPtrPtr) >= KP_KWD_LEN)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }
   if(SUCCEEDED(retc))
   {
      if(**plpszHdrPtrPtr == '\"') (*plpszHdrPtrPtr)++;
//    else
//    {
//       retc = KP_E_MSG_FORMAT;
//       KpErrorProc.OutputErrorMessage(retc, *plpszHdrPtrPtr, bOutMsg, __FILE__, __LINE__, 0L);
// //    KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
//    }
   }
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszCtrlName, *plpszHdrPtrPtr);
      ii = strlen(*plpszHdrPtrPtr) - 1;
      if(ii < 0)
      {
         retc = KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }
   }
   if(SUCCEEDED(retc))
   {
      if(m_lpszCtrlName[ii] == '\"') m_lpszCtrlName[ii] = Nul;
//    else
//    {
//       retc = KP_E_MSG_FORMAT;
//       KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
//    }
   }

return(retc);
}


HRESULT KpSocket::ScanHdr(HttpMsgTypes iInitMsgType, bool bOutMsg)
{
HRESULT retc = S_OK;
HRESULT retv = S_OK;
unsigned char *pntd;
unsigned char *pntd0;
unsigned char *pnts;
unsigned char sav_chr;
unsigned char url[KP_MAX_FNAME_LEN+1];
unsigned char url1[KP_MAX_FNAME_LEN+1];
int str_len;
int ii;
int jj;
KpSockHdTag http_tag;

   url[0]=Nul;

   m_iMsgType=iInitMsgType;
   if(((iInitMsgType<0) || (iInitMsgType>=NUM_OF_HTTP_MSG_TYPES)) && SUCCEEDED(retc))
   {
      retc = E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(
//    (iInitMsgType!=HTTP_POST_REQUEST) || // reikejo, kol RcvHttpRequest() buvo be RcvHdr()
      (iInitMsgType!=HTTP_POST_DATA_SEGM)
     )
   {
// sitie globalus parametrai jau priimti su pagrindine POST pranesimo antraste
      m_iRetCode = 0;
      m_lpszRetMsg[0] = Nul;
      m_iTrMode = NORMAL_HTTP_TR_MODE;
      m_lContLen = MAXLONG;
      m_lpszBoundary[0] = Nul;
      m_lpszEndBoundary[0] = Nul;
   }
   m_lpszCtrlName[0]=Nul;

   if(strlen(m_lpszHdrBuf)>=MAX_HTTP_HDR_LEN)
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      pnts=pntd=m_lpszHdrBuf;
      do
      {
         while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;

         sav_chr=(*pntd);
         *pntd=Nul;

         str_len=pntd-pnts;

#if FALSE // #ifdef Debug
// KP_TRACE(pnts);
#endif

         if(str_len>0)
         {
// pirma headerio eilute
            if((pnts==m_lpszHdrBuf) && ((m_iMsgType==HTTP_REPLY) || (m_iMsgType==HTTP_REQUEST_UNKNOWN)))
            {
               switch(m_iMsgType)
               {
               case HTTP_REPLY:
                  if(strstr(pnts, KPSOCK_HTTP_HDR_PREFIX)!=pnts) // 200 OK
                  {
                     retc=KP_E_TRANS_ERR;
                     KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc))
                  {
                     pnts+=strlen(KPSOCK_HTTP_HDR_PREFIX);
                     while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                     m_iRetCode=0;
                     sscanf((const char *)pnts, "%d", &m_iRetCode);

                     while(*pnts && TvIsDigit((KpChar)*pnts)) pnts++;
                     while(*pnts && (strchr(lpszSpaces, *pnts) != NULL)) pnts++;
                     strncpy(m_lpszRetMsg, pnts, KP_MAX_FILE_LIN_WDT);
                     m_lpszRetMsg[KP_MAX_FILE_LIN_WDT] = Nul;

                     retv = SUCCEEDED(KpErrorProcClass::TranslFromHTTP_RetCode(m_iRetCode))?S_OK:KP_E_NEG_ANSW; // KpErrorProcClass::TranslFromHTTP_RetCode(m_iRetCode); // KP_E_NEG_ANSW; // KP_E_TRANS_ERR;
// neigiami atsakymai normalu (kpstart.exe atsakymas nuo kpstisvr.exe á requestà "CD="
//                   if(FAILED(retv)) KP_WARNING(retv, pnts); // KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                  }
                  break;

               case HTTP_REQUEST_UNKNOWN:
                  if(strstr(pnts, "GET ") == pnts) // HTTP_GET_REQUEST_CMD
                  {
                     pnts += strlen(HTTP_GET_REQUEST_CMD); // "GET"
                     while(*pnts && (strchr(lpszSpaces, *pnts) != NULL)) pnts++;
                     m_iMsgType=HTTP_GET_REQUEST;
                  }
                  else if(strstr(pnts, "POST ") == pnts) // HTTP_POST_REQUEST_CMD
                  {
                     pnts += strlen(HTTP_POST_REQUEST_CMD); // "POST"
                     while(*pnts && (strchr(lpszSpaces, *pnts) != NULL)) pnts++;
//                   if(strchr(pnts, '?')) m_iMsgType=HTTP_GET_REQUEST; // Tado POST'ai su GET parametru sintakse
//                   else
                        m_iMsgType = HTTP_POST_REQUEST;
                  }
                  else
                     KpErrorProc.OutputErrorMessage(E_NOTIMPL, pnts, False, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc))
                  {
                     ii=strlen(pnts);
                     jj=strlen(" HTTP/1.1");
                     if(strstr(pnts, " HTTP/1.1")!=pnts+ii-jj)
                     {
//                      retc=E_NOTIMPL;
//                      KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                        KpErrorProc.OutputErrorMessage(E_NOTIMPL, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                     }
                     else
                     {
                        pnts[ii - jj] = Nul;
                        if(strlen(url)+ii-jj<KP_MAX_FNAME_LEN) strcat(url, pnts);
                        else
                           KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        pnts+=ii;
                     }
                  }
                  break;

               default:
                  KpErrorProc.OutputErrorMessage(retc, pnts, False, __FILE__, __LINE__, m_iMsgType);
                  break;
               }

            } // if((pnts==m_lpszHdrBuf) && ((m_iMsgType==HTTP_REPLY) || (m_iMsgType==HTTP_REQUEST_UNKNOWN))
            else
            {
// tolesnes headerio eilutes
               pntd0=strchr(pnts, ':');
               if(pntd0==NULL)
               {
                  retc=KP_E_MSG_FORMAT;
                  KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, m_iMsgType);
               }
               if(SUCCEEDED(retc))
               {
                  pntd0++;
                  if(*pntd0!=Spc)
                  {
                     retc = KP_E_MSG_FORMAT;
                     KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                     KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                  }
               }

               if(SUCCEEDED(retc))
               {
                  *pntd0=Nul;

                  retc=GetKwrdIndex(&ii, pnts, KpsockTagNames, KPSOCK_NUM_OF_HDTAGS, True, True);
                  if(SUCCEEDED(retc)) http_tag=(KpSockHdTag)ii;
                  if(retc==KP_E_KWD_NOT_FOUND)
                  {
                     KpErrorProc.OutputErrorMessage(retc, pnts, False, __FILE__, __LINE__, m_iMsgType);
                     retc = S_OK; // neatpaþintus headerio raktus praleidþiam
                  }
                  else if(SUCCEEDED(retc))
                  {
                     if(((http_tag<0) || (http_tag>=KPSOCK_NUM_OF_HDTAGS)) && SUCCEEDED(retc))
                     {
                        retc=KP_E_SYSTEM_ERROR;
                        KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc))
                        if(!KpsockTagOccurences[http_tag][m_iMsgType])
                        {
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, m_iMsgType);
                        }
                     if(SUCCEEDED(retc))
                     {
                        pnts=pntd0+1;
                        while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                     }

                     if(SUCCEEDED(retc)) switch(http_tag)
                     {
// HTTP_REPLY
                     case KPSOCK_HDTAG_Date:                            // Date: Fri, 22 Oct 2004 07:13:17 GMT
                        break;
                     case KPSOCK_HDTAG_Server:                          // Server: Apache/1.3.29 (Unix)
                        break;                                          // Server: Apache/1.3.29 (Unix) (Red-Hat/Linux) PHP/3.0.15 mod_ssl/2.8.7 OpenSSL/0.9h tomcat/1.0 mod_jk/1.2.0
                                                                  // Server: Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2
                                                                  // Server: Apache

                     case KPSOCK_HDTAG_SetCookie:                       // Set-Cookie: JSESSIONID=2C6444E9BE0D74D7E5FE24042673459F;Path=/services
                        break;                                          //    gali ir nebuti

                     case KPSOCK_HDTAG_LastModified:                    // Last-Modified: Thu, 17 Jan 2002 12:58:44 GMT
// !!! scan file date                                             //    tik statiniams puslapiams
                        break;

                     case KPSOCK_HDTAG_XPoweredBy:                      // X-Powered-By: PHP/4.3.4
                        break;                                          //    dinaminiams puslapiams, gali ir nebuti

                     case KPSOCK_HDTAG_ETag:                            // ETag: cb992-26b-3c46ca84
                        break;                                          // ETag: 23-40f6b0d0
                                                                  //    gali ir nebuti (yra tik statiniams puslapiams?)

                     case KPSOCK_HDTAG_AcceptRanges:                    // Accept-Ranges: bytes
                        if(strcmp(pnts, "bytes")==0){}                  //    gali ir nebuti (yra tik statiniams puslapiams?)
                        else
                        {
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;

                     case KPSOCK_HDTAG_ContentLength:                   // Content-Length: 619
                                                                  //    gali ir nebuti - tada "Transfer-Encoding:"
// pranesimo duomenu dalies ilgis - baitu skaicius be headerio ir tuscios eilutes - atskyrejo tarp headerio ir duomenu
// !!! tikrinti, kad butu tik skaicius ir nieko daugiau
                        m_lContLen=MAXLONG;
                        if(sscanf((const char *)pnts, "%ld", &m_lContLen)<1)
                        {
                           m_lContLen=MAXLONG;
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;

                     case KPSOCK_HDTAG_TransferEncoding:                // Transfer-Encoding: chunked
                                                                  //    gali ir nebuti - tada "Content-Length:"
                                                                  //    zr. HTTP_TR_CHUNK_MODE
                        if(SUCCEEDED(retc)) retc=GetKwrdIndex(&ii, pnts, TransferModeNames, NUM_OF_HTTP_TR_MODES_0, True, True);
                        if(SUCCEEDED(retc)) m_iTrMode = (HttpTransferModes)ii;
                        if(retc == KP_E_KWD_NOT_FOUND)
                           KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);

//                      if(m_lpszEndBoundary[0] != Nul) KP_ASSERT(m_iTrMode == HTTP_TR_CHUNK_MODE, KP_E_MSG_FORMAT, pnts, False);
                        break;

                     case KPSOCK_HDTAG_Connection:                      // Connection: close
                                                                  // Connection: keep-alive
                                                                  // Connection: Keep-Alive
                                                                  // Connection: Keep-Alive, TE
                                                                  //    jei "keep-alive" - tada "Keep-Alive:"
                        if(strcmp(pnts, "close")==0){}                  //    jei "TE" - tada "TE:"
                        else if((strcmp(pnts, "keep-alive")==0) || (strstr(pnts, "Keep-Alive")==pnts)){}
                        else
                        {
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;

                     case KPSOCK_HDTAG_KeepAlive:                       // Keep-Alive: timeout=15, max=100
                        break;                                          // Keep-Alive: 300
                                                                  //    tik jei "Connection: keep-alive"
                                                                  //    !!! tikrinti, kad butu tik jei "Connection: keep-alive",
                                                                  //       !!! bet "Connection: keep-alive" buna po "Keep-Alive:"
                                                                  //    !!! tikrinti, kad butu skaicius

                     case KPSOCK_HDTAG_TE:                              // TE: deflate, gzip, chunked, identity, trailers
                        break;                                          // kazkas panasaus i Accept-Encoding:
                                                                  // po Connection: Keep-Alive, TE
// ------------------------------------------------------
// Content-Type := type "/" subtype *[";" parameter]
// type :=          "application"     / "audio"
//           / "image"           / "message"
//           / "multipart"  / "text"
//           / "video"           / x-token
// x-token := <The two characters "X-" followed, with no
//            intervening white space, by any token>
// subtype := token
// parameter := attribute "=" value
// attribute := token
// value := token / quoted-string
// token := 1*<any CHAR except SPACE, CTLs, or tspecials>
// tspecials :=  "(" / ")" / "<" / ">" / "@"  ; Must be in
//            /  "," / ";" / ":" / "\" / <">  ; quoted-string,
//            /  "/" / "[" / "]" / "?" / "."  ; to use within
//            /  "="                        ; parameter values
// Note that the definition of "tspecials" is the same as the RFC 822 definition of "specials" with the addition of the three characters "/", "?", and "=".
// Note also that a subtype specification is MANDATORY. There are no default subtypes.
// The type, subtype, and parameter names are not case sensitive. For example, TEXT, Text, and TeXt are all equivalent. Parameter values are normally case sensitive, but certain parameters are interpreted to be case- insensitive, depending on the intended use. (For example, multipart boundaries are case-sensitive, but the "access- type" for message/External-body is not case-sensitive.)
// Beyond this syntax, the only constraint on the definition of subtype names is the desire that their uses must not conflict. That is, it would be undesirable to have two different communities using "Content-Type: application/foobar" to mean two different things. The process of defining new content-subtypes, then, is not intended to be a mechanism for imposing restrictions, but simply a mechanism for publicizing the usages. There are, therefore, two acceptable mechanisms for defining new Content-Type subtypes:
//     Private values (starting with "X-") may be defined bilaterally between two cooperating agents without outside registration or standardization.
//     New standard values must be documented, registered with, and approved by IANA, as described in Appendix F. Where intended for public use, the formats they refer to must also be defined by a published specification, and possibly offered for standardization.
// The seven standard initial predefined Content-Types are detailed in the bulk of this document. They are:
// text – textual information. The primary subtype, "plain", indicates plain (unformatted) text. No special software is required to get the full meaning of the text, aside from support for the indicated character set. Subtypes are to be used for enriched text in forms where application software may enhance the appearance of the text, but such software must not be required in order to get the general idea of the content. Possible subtypes thus include any readable word processor format. A very simple and portable subtype, richtext, is defined in this document.
// multipart – data consisting of multiple parts of independent data types. Four initial subtypes are defined, including the primary "mixed" subtype, "alternative" for representing the same data in multiple formats, "parallel" for parts intended to be viewed simultaneously, and "digest" for multipart entities in which each part is of type "message".
// message – an encapsulated message. A body of Content-Type "message" is itself a fully formatted RFC 822 conformant message which may contain its own different Content-Type header field. The primary subtype is "rfc822". The "partial" subtype is defined for partial messages, to permit the fragmented transmission of bodies that are thought to be too large to be passed through mail transport facilities. Another subtype, "External-body", is defined for specifying large bodies by reference to an external data source.
// image – image data. Image requires a display device (such as a graphical display, a printer, or a FAX machine) to view the information. Initial subtypes are defined for two widely-used image formats, jpeg and gif.
// audio – audio data, with initial subtype "basic". Audio requires an audio output device (such as a speaker or a telephone) to "display" the contents.
// video – video data. Video requires the capability to display moving images, typically including specialized hardware and software. The initial subtype is "mpeg".
// application – some other kind of data, typically either uninterpreted binary data or information to be processed by a mail-based application. The primary subtype, "octet-stream", is to be used in the case of uninterpreted binary data, in which case the simplest recommended action is to offer to write the information into a file for the user. Two additional subtypes, "ODA" and "PostScript", are defined for transporting ODA and PostScript documents in bodies. Other expected uses for "application" include spreadsheets, data for mail-based scheduling systems, and languages for "active" (computational) email. (Note that active email entails several securityconsiderations, which are discussed later in this memo, particularly in the context of application/PostScript.)
// Default RFC 822 messages are typed by this protocol as plain text in the US-ASCII character set, which can be explicitly specified as "Content-type: text/plain; charset=us-ascii". If no Content-Type is specified, either by error or by an older user agent, this default is assumed. In the presence of a MIME-Version header field, a receiving User Agent can also assume that plain US-ASCII text was the sender's intent. In the absence of a MIME-Version specification, plain US-A
// ------------------------------------------------------
                     case KPSOCK_HDTAG_ContentType:                     // Content-Type: text/plain
                        if(m_iMsgType==HTTP_REPLY)                      // Content-Type: text/html
                        {                                               // Content-Type: text/html; charset=ISO-8859-1
                           if(strcmp(pnts, "text/plain")==0){}
                           else if(strcmp(pnts, "text/html")==0){}
                           else if(strstr(pnts, "text/html; charset=")==pnts){}
                           else if(strcmp(pnts, "image/bmp")==0){}
                           else if(strcmp(pnts, "image/png")==0){}
                           else if(strstr(pnts, "image/jpeg")==0){} // JPEG JFIF image
                           else if(strstr(pnts, "image/gif")==0){} // GIF image
                           else if(strstr(pnts, "image/vnd.microsoft.icon")==0){} // ICO image
                           else if(strstr(pnts, "application/unknown")==0){}
                           else if(strstr(pnts, "application/octet-stream")==0){} // common binary uninterpreted
                           else if(strcmp(pnts, "application/x-msdownload")==0){}
                           else if(strstr(pnts, "application/vnd.xls")==0){} // MS Excel
                           else if(strstr(pnts, "application/vnd.ms-excel")==0){} // Microsoft Excel (tm)
                           else if(strstr(pnts, "application/ms-word")==0){} // MS Word
                           else if(strstr(pnts, "application/msword")==0){} // Microsoft Word
                           else if(strstr(pnts, "application/vnd.ms-powerpoint")==0){} // Microsoft Powerpoint (tm)
                           else if(strstr(pnts, "application/pdf")==0){} // Portable Document Format
                           else if(strcmp(pnts, "application/vnd.fdf")==0){}
                           else if(strstr(pnts, "application/zip")==0){} // ZIP file
                           else
                              KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        else if(m_iMsgType==HTTP_POST_REQUEST)          // Content-Type: multipart/form-data; boundary=---------------------------287452692419072
                                                                  // Content-Type: multipart/form-data; boundary=----------MewvlxgnyxIqwnyLYofnOt
                        {                                               // Content-Type: application/x-www-form-urlencoded
                           if(strstr(pnts, "multipart/form-data;")==pnts)  //             tada turi buti Content-Length:
                           {                                            // Content-Type: application/vnd.fdf
                              pnts += strlen("multipart/form-data;");
                              while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                              if(strstr(pnts, "boundary=")==pnts)
                              {
                                 pnts+=strlen("boundary=");
                                 if(strlen(pnts)>=KP_MAX_FILE_LIN_WDT)
                                 {
                                    retc=KP_E_BUFFER_OVERFLOW;
                                    KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    strcpy(m_lpszBoundary, "--");
                                    strcat(m_lpszBoundary, pnts);
//                                  strcpy(m_lpszBoundary, pnts);

                                    strcpy(m_lpszEndBoundary, m_lpszBoundary);
                                    strcat(m_lpszEndBoundary, "--");
                                 }

//                               m_iTrMode = HTTP_TR_CHUNK_MODE; // ne – boundary naudojamas formos laukø atskyrimui, ne chunk'ø
                              }
                              else
                              {
                                 retc = KP_E_MSG_FORMAT;
                                 KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                              }
                           }
                           else if(strcmp(pnts, "application/x-www-form-urlencoded")==0){}
                           else if(strcmp(pnts, "application/vnd.fdf")==0){}
                           else
                           {
                              retc=E_NOTIMPL;
                              KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                           }
                        }
                        else if(m_iMsgType==HTTP_POST_DATA_SEGM)        // Content-Type: multipart/mixed; boundary=BbC04y
                        {                                               // Content-Type: text/plain
                           retc=E_NOTIMPL;                              // Content-Type: image/gif
                           KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;

                     case KPSOCK_HDTAG_ContentEncoding:                 // Content-Encoding: gzip
                        if(strcmp(pnts, "gzip")==0)                     // Content-Encoding: none
                           KpErrorProc.OutputErrorMessage(E_NOTIMPL, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        else if(strcmp(pnts, "none")==0){}
                        else
                        {
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;

// HTTP_REQUEST_UNKNOWN
                     case KPSOCK_HDTAG_Host:                            // Host: 127.0.0.1:49494
                        if(strlen(KPSOCK_URL_HTTP_PREFIX) + strlen(pnts) + strlen(url)>=KP_MAX_FNAME_LEN)
                           KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
                        else
                        {
                           strcpy(url1, KPSOCK_URL_HTTP_PREFIX);
                           strcat(url1, pnts);
                           strcat(url1, url);
                           strcpy(url, url1);
                        }
                        break;

                     case KPSOCK_HDTAG_UserAgent:                       // User-Agent: Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax)
                                                                  // User-Agent: AcroForms
                                                                  // User-Agent: Opera/9.02 (Windows NT 5.0; U; en)
                        break;

                     case KPSOCK_HDTAG_Accept:                          // Accept: video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
                                                                  // Accept: application/x-shockwave-flash,text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
                                                                  // Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
                                                                  // Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1
                                                                  // Accept: */*
                        break;

                     case KPSOCK_HDTAG_AcceptLanguage:                  // Accept-Language: en-us,en;q=0.5
                                                                  // Accept-Language: lt-LT,lt;q=0.9,en;q=0.8
                        break;

                     case KPSOCK_HDTAG_AcceptEncoding:                  // Accept-Encoding: gzip,deflate
                                                                  // Accept-Encoding: deflate, gzip, x-gzip, identity, *;q=0
                        break;

                     case KPSOCK_HDTAG_AcceptCharset:                   // Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
                                                                  // Accept-Charset: iso-8859-1, utf-8, utf-16, *;q=0.1
                        break;

                     case KPSOCK_HDTAG_Pragma:                          // Pragma: no-cache
                        if(strcmp(pnts, "no-cache")==0){}
                        if(strcmp(pnts, "public")==0){}
                        else
                           KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        break;

                     case KPSOCK_HDTAG_CacheControl:                    // Cache-Control: max-age=0
                        if(strstr(pnts, "max-age=")==pnts){}            // Cache-Control: no-cache
                        else if(strcmp(pnts, "no-cache")==0){}
                        else                                            // Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
                        {
//                         KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        }
                        break;




                     case KPSOCK_HDTAG_Referer:                         // Referer: http://127.0.0.1:3010/friends.htm
                        break;                                          // Referer: http://127.0.0.1:3010/
                                                                        //    GET requestuose tik jei "reload current page"

                     case KPSOCK_HDTAG_IfModifiedSince:                 // If-Modified-Since: 2006-08-23
                        break;                                          //    tik jei "reload current page"

                     case KPSOCK_HDTAG_IfNoneMatch:                     // If-None-Match: 1156338348
                        break;                                          //    tik jei "reload current page"

                     case KPSOCK_HDTAG_UA_CPU:                          // UA-CPU: x86
                        if(strcmp(pnts, "x86")==0){}
                        else
                           KpErrorProc.OutputErrorMessage(E_NOTIMPL, pnts, False, __FILE__, __LINE__, m_iMsgType);
                        break;

// HTTP_POST_DATA_SEGM
                     case KPSOCK_HDTAG_ContentDisposition:
                        if(strstr(pnts, "form-data;") == pnts)              // Content-Disposition: form-data; name="IP"
                        {
                           pnts += strlen("form-data;");

                           if(SUCCEEDED(retc))
                           {
                              while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                              if(strstr(pnts, "name=")!=pnts)
                              {
                                 retc=KP_E_KWD_NOT_FOUND;
                                 KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                              }
                              else pnts+=strlen("name=");
                           }
                           if(SUCCEEDED(retc))
                              if(strlen(pnts) >= KP_KWD_LEN)
                              {
                                 retc=KP_E_BUFFER_OVERFLOW;
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                              }
                           if(SUCCEEDED(retc))
                           {
                              if(*pnts=='\"') pnts++;
                              else
                              {
                                 retc=KP_E_MSG_FORMAT;
                                 KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                              }
                           }
                           if(SUCCEEDED(retc))
                           {
                              strcpy(m_lpszCtrlName, pnts);
                              ii=strlen(pnts)-1;
                              if(ii<0)
                              {
                                 retc=KP_E_MSG_FORMAT;
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                              }
                           }
                           if(SUCCEEDED(retc))
                           {
                              if(m_lpszCtrlName[ii]=='\"') m_lpszCtrlName[ii] = Nul;
                              else
                              {
                                 retc=KP_E_MSG_FORMAT;
                                 KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                              }
                           }
                        }
                        else if(strstr(pnts, "file;") == pnts)              // Content-Disposition: file; filename="file1.txt"
                        {
                           pnts += strlen("file;");

                           retc = ScanHdrFileName(&pnts, bOutMsg);
                        }
                        else if(strstr(pnts, "attachment;") == pnts)       // Content-Disposition: attachment; filename=ekov910_lt_setup.exe
                        {
                           pnts += strlen("attachment;");

                           retc = ScanHdrFileName(&pnts, bOutMsg);
                        }
                        else
                        {
                           retc=E_NOTIMPL;
                           KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                        }
                        break;

                     case KPSOCK_HDTAG_ContentTransferEncoding:
                        if(strstr(pnts, "binary") == pnts)                 // Content-Transfer-Encoding: binary
                           pnts += strlen("binary");
                        else
                        {
                           retc = E_NOTIMPL;
                           KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                        }
                        break;

                     } // if(SUCCEEDED(retc)) switch(http_tag)

                  } // else // if(retc==KP_E_KWD_NOT_FOUND)

               } // if(SUCCEEDED(retc))

            } // else // if((pnts==m_lpszHdrBuf) && ((m_iMsgType==HTTP_REPLY) || (m_iMsgType==HTTP_REQUEST_UNKNOWN))

         } // if(str_len>0)

         *pntd=sav_chr;

//    while(*pntd && (strchr(lpszEols, *pntd)!=NULL)) pntd++;
         if(*pntd==Cr) pntd++;
         if(*pntd==Lf) pntd++;

         pnts=pntd;

      } while((*pnts) && (str_len>0) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

// gale headerio gale turi buti tuscia eilute
   if(SUCCEEDED(retc))
      if(
         (*pnts==Nul) && (str_len>0) // &&
// tuscios eilutes gale nebudavo, kol RcvHttpRequest() buvo be RcvHdr() - headerio galas ateidavo
//    kitu paketu pries duomenis
//       ((m_iMsgType!=HTTP_POST_REQUEST) || (iInitMsgType!=HTTP_REQUEST_UNKNOWN))
        )
         KpErrorProc.OutputErrorMessage(KP_E_TRANS_ERR, null, False, __FILE__, __LINE__, 0L);


   if(
      (
         (m_iMsgType==HTTP_GET_REQUEST) ||
         (
            (m_iMsgType==HTTP_POST_REQUEST) // &&
//          (iInitMsgType!=HTTP_POST_REQUEST) // reikejo, kol RcvHttpRequest() buvo be RcvHdr()
         )
      ) && SUCCEEDED(retc)
     )
   {
      retc=Resolve(url, bOutMsg);

#if FALSE // #ifdef Debug
KpMsgOut(url, IDI_ASTERISK, KP_MB_TESTI);
#endif
   }

   if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}


//---------------------
HRESULT KpSocket::RcvHdr(HttpMsgTypes iInitMsgType, bool bOutMsg)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc = ReceiveHdr(iInitMsgType, NULL, bOutMsg);
// KP_TRACE("RcvHdr(): ReceiveHdr()");
// KP_TRACE("--------------- Request received:");
// KP_TRACE(m_lpszHdrBuf);

#ifdef TRACE_HTTP
{
static unsigned char str_buf_1[4500 + 1];
strncpy(str_buf_1, m_lpszHdrBuf, 4500);
str_buf_1[4500] = Nul;
PutLogMessage_("KpSocket::RcvHdr(): \n%s", str_buf_1);
}
#endif

   if(SUCCEEDED(retc))
   {
      retc = ScanHdr(iInitMsgType, bOutMsg);
// KP_TRACE("RcvHdr(): ScanHdr()");

//    if(retc == KP_E_NEG_ANSW)
//    {
// iðsaugojam KP_E_NEG_ANSW
//       retv = retc;
//       retc = S_OK;
//    }
   }

// if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}


// ===============================================
//---------------------
HRESULT KpSocket::GetByte(unsigned char *pcInCh, bool bOutMsg)
{
HRESULT retc=S_OK;

   if(pcInCh==NULL)
   {
      retc = E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(m_lChunkRest == 0L)
   {
      m_lpszChunkPos = m_lpszHdrBuf;
      m_lChunkRest = MAX_HTTP_HDR_LEN;

      retc = ReceiveMsg(m_lpszHdrBuf, &m_lChunkRest, True, bOutMsg);

      KP_ASSERTE((m_lChunkRest >= 0L) && (m_lChunkRest <= MAX_HTTP_HDR_LEN), KP_E_TRANS_ERR, null, bOutMsg);
   }

   if(SUCCEEDED(retc))
   {
      if(m_lChunkRest > 0L)
      {
         *pcInCh = (*(m_lpszChunkPos++));
         m_lChunkRest--;
      }
      else
      {
         *pcInCh = Nul;
         retc = KP_E_EOF;
      }
   }

return(retc);
}


//---------------------
HRESULT KpSocket::UnGetByte(unsigned char cInCh, bool bOutMsg)
{
HRESULT retc=S_OK;

   KP_ASSERTE(m_lpszChunkPos > m_lpszHdrBuf, KP_E_DOUBLE_UNGET, null, bOutMsg);

   if(SUCCEEDED(retc))
   {
      (*(--m_lpszChunkPos)) = cInCh;
      m_lChunkRest++;
   }

return(retc);
}


//---------------------
HRESULT KpSocket::GetChunk(long lChunkLength, unsigned char **ppOutBufPtr, unsigned char *pBuf, long lBufLen, bool bOutMsg, bool bFullChunk)
{
HRESULT retc=S_OK;
long ll;

   for(ll = 0; (ll < lChunkLength) && SUCCEEDED(retc); ll++)
   {
      KP_ASSERTE(*ppOutBufPtr - pBuf < lBufLen - 1, KP_E_BUFFER_OVERFLOW, null, bOutMsg);
      if(SUCCEEDED(retc)) retc = GetByte((*ppOutBufPtr)++, bOutMsg);
   }

   if(SUCCEEDED(retc)) **ppOutBufPtr = Nul;

// skip EOL
   if(bFullChunk && SUCCEEDED(retc))
   {
unsigned char ch;

      if(SUCCEEDED(retc)) retc = GetByte(&ch, bOutMsg);
      KP_ASSERTE(TvStrChr(lpszEols, (KpChar)ch) != NULL, KP_E_FILE_FORMAT, null, bOutMsg);

      if((ch == Cr) && SUCCEEDED(retc))
      {
         retc = GetByte(&ch, bOutMsg);
         if((ch != Lf) && SUCCEEDED(retc))
            retc = UnGetByte(ch, bOutMsg);
      }
   }

return(retc);
}


//---------------------
HRESULT KpSocket::GetChunkLength(long *plChunkLength, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char ch;
unsigned char len_buf[MAX_LONG_DIGITS + 1];
unsigned char *pntd;

   if(plChunkLength==NULL)
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   pntd = len_buf;
   if(SUCCEEDED(retc)) do
   {
      retc = GetByte(&ch, bOutMsg);
      if((TvStrChr(lpszEols, (KpChar)ch) == NULL) && SUCCEEDED(retc))
      {
         if(pntd - len_buf >= MAX_LONG_DIGITS)
         {
            retc = KP_E_BUFFER_OVERFLOW;
            KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
         }
         if(SUCCEEDED(retc)) *(pntd++)=ch;
      }
      else break;
   } while(SUCCEEDED(retc));

   if((ch==Cr) && SUCCEEDED(retc))
   {
      retc = GetByte(&ch, bOutMsg);
      if((ch != Lf) && SUCCEEDED(retc))
         retc = UnGetByte(ch, bOutMsg);
   }

   *pntd=Nul;

   if(SUCCEEDED(retc)) retc=CutInitTrailSpcs(len_buf);
   if(SUCCEEDED(retc))
      if(!TvIsHexNum(len_buf))
      {
         retc=KP_E_FILE_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, len_buf, bOutMsg, __FILE__, __LINE__, 0L);
      }

   if(SUCCEEDED(retc)) sscanf((char *)len_buf, "%lx", plChunkLength);

return(retc);
}


//---------------------
// HTTP/1.1 200 OK
HRESULT KpSocket::RcvHttpMsg(unsigned char *pBuf, long *plRead, bool bOutMsg, bool bRcvHdr)
{
HRESULT retc = S_OK;
HRESULT retv = S_OK;
unsigned char *pntd;
long read;
long buf_len;
long chunk_length;

   if(((pBuf==NULL) || (plRead==NULL)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(bRcvHdr && SUCCEEDED(retc))
   {
// -------- dar kabo nepabaigtas ankstesnis praneðimas
      KP_ASSERTE(m_lRestChunkLength == 0L, KP_E_DOUBLE_CALL, null, bOutMsg);
//    KP_ASSERTE(m_lNextChunkLength == 0L, KP_E_DOUBLE_CALL, null, bOutMsg);

// -------------------------------------------------
      retc = RcvHdr(HTTP_REPLY, bOutMsg);
      if(retc == KP_E_NEG_ANSW)
      {
static char str_buf[KP_MAX_FILE_LIN_WDT + 100];
         sprintf(str_buf, "%d %s", m_iRetCode, m_lpszRetMsg);
// iðsaugojam KP_E_NEG_ANSW
         retv = retc;
         KP_WARNING(retc, str_buf);
         retc = S_OK;
      }

   } // if(bRcvHdr && SUCCEEDED(retc))

#if FALSE // #if TRUE //
KpMsgOut(m_lpszHdrBuf, IDI_ASTERISK, KP_MB_TESTI);
fstream out_file("rcv.txt", ios::out);
out_file << m_lpszHdrBuf << endl;
out_file << "--------------------------" << endl;
// out_file.close();
#endif

// -------------------------------------------------
// receive header tail with chunk header???
   if(SUCCEEDED(retc))
   {
      read = MAX_HTTP_HDR_LEN;

      retc = ReceiveMsg(m_lpszHdrBuf, &read, True, bOutMsg);
   }

#if FALSE // #ifdef Debug
if(SUCCEEDED(retc)) KP_TRACE("----------------------- Message received:");
#endif

// KpMsgOut(m_lpszHdrBuf, IDI_ASTERISK, KP_MB_TESTI);

   if(SUCCEEDED(retc)) m_lpszHdrBuf[read] = Nul;
#ifdef TRACE_HTTP
{
static unsigned char str_buf_1[4500 + 1];
strncpy(str_buf_1, m_lpszHdrBuf, 4500);
str_buf_1[4500] = Nul;
PutLogMessage_("KpSocket::RcvHttpMsg() 1:\n%s", str_buf_1);
}
#endif

#if FALSE // #if TRUE //
// KpMsgOut(m_lpszHdrBuf, IDI_ASTERISK, KP_MB_TESTI);
// fstream out_file("rcv.txt", ios::out);
out_file << m_lpszHdrBuf << endl;
out_file.close();
#endif

   m_lpszChunkPos = m_lpszHdrBuf;

// receive data part
   if(SUCCEEDED(retc))
   {
//    m_lChunkRest = strlen(m_lpszChunkPos);

//    m_lChunkRest = read - (m_lpszChunkPos - m_lpszHdrBuf); // rest of bytes from m_lpszChunkPos to end of received piece
      m_lChunkRest = read;

// TODO: èia gal kaþkaip iðkviesti RcvHttpRest()?

      buf_len = *plRead;
      KP_ASSERTE(buf_len > 1, E_INVALIDARG, null, bOutMsg); // paliekam vietos galiniam nuliui
   }

   if(SUCCEEDED(retc))
   {
      *plRead = 0;  // jau priimtu baitu sk.
      pntd = pBuf;  // pointeris priemimo buferyje

// ----------------------------- Transfer-Encoding: chunked
      if(m_iTrMode == HTTP_TR_CHUNK_MODE)
      {
         KP_ASSERTE(m_lContLen == MAXLONG, KP_E_FILE_FORMAT, null, True);

         do
         {
// ---------- chunk length
            chunk_length = 0;
            if((m_lRestChunkLength == 0) && SUCCEEDED(retc)) retc = GetChunkLength(&chunk_length, bOutMsg);

            if((chunk_length > 0) && SUCCEEDED(retc))
            {
// ---------- jei netilps á buferá – nukandam
               if(SUCCEEDED(retc))
               {
                  m_lRestChunkLength = 0L;
                  if(chunk_length > buf_len - (pntd - pBuf) - 1)
                     m_lRestChunkLength = chunk_length - (buf_len - (pntd - pBuf) - 1);

// ---------- tiek skaitysim ið dabartinio chunk
                  chunk_length -= m_lRestChunkLength;

// ---------- chunk
                  if(chunk_length > 0)
                     retc = GetChunk(chunk_length, &pntd, pBuf, buf_len, bOutMsg, m_lRestChunkLength == 0);

               } // if(SUCCEEDED(retc))

            } // if((chunk_length > 0) && SUCCEEDED(retc))

         } while((chunk_length>0) && SUCCEEDED(retc));

// kai paskutinis gabalas, gali likti nebent Cr/Lf (2 baitai)
         if(m_lRestChunkLength == 0L)
//       if(m_lNextChunkLength == 0L)
            KP_ASSERT(m_lChunkRest <= 2L, KP_E_SYSTEM_ERROR, null, False);

      }
// -----------------------------
      else // if(m_iTrMode == HTTP_TR_CHUNK_MODE)
      {
//       KP_ASSERTE(m_lContLen != MAXLONG, E_NOTIMPL, null, bOutMsg); // Content-Length: 999 // gali bûti MAXLONG, jei praneðime nebuvo ContentLength: arba praneðimas ið viso tuðèias

         KP_ASSERTE(m_lChunkRest <= m_lContLen, KP_E_TRANS_ERR, null, bOutMsg);

         if(SUCCEEDED(retc))
         {
            read = m_lContLen;
            if(read > buf_len - 1) read = buf_len - 1;

            m_lRestChunkLength = m_lContLen - read;

#if FALSE // #ifdef Debug
char str_buf[1000];
sprintf(str_buf, "m_lpszChunkPos[%d] >>>%s<<<", read, m_lpszChunkPos);
KP_TRACE(str_buf);
#endif
            for(long ll = 0L; (ll < read) && SUCCEEDED(retc); ll++)
                retc = GetByte(pntd++, bOutMsg);
         }

      } // else // if(m_iTrMode == HTTP_TR_CHUNK_MODE)

      if(SUCCEEDED(retc))
      {
         *plRead = pntd - pBuf;
         *pntd = Nul;
      }

   } // if(SUCCEEDED(retc))

// KpMsgOut(pBuf, IDI_ASTERISK, KP_MB_TESTI);

   if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}


//---------------------
HRESULT KpSocket::RcvHttpRest(unsigned char *pBuf, long *plRead, bool bOutMsg)
{
HRESULT retc = S_OK;
unsigned char *pntd;
long buf_len;
long chunk_length;

   KP_ASSERT(pBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(plRead != NULL, E_INVALIDARG, null, True);

// -----------------------------
   if(SUCCEEDED(retc))
   {
      buf_len = *plRead;
      KP_ASSERTE(buf_len > 1, E_INVALIDARG, null, bOutMsg); // paliekam vietos galiniam nuliui
   }

   if(SUCCEEDED(retc))
   {
      *plRead = 0;  // jau priimtu baitu sk.

      pntd = pBuf;  // pointeris priemimo buferyje

      if(m_iTrMode == HTTP_TR_CHUNK_MODE)
      {
         KP_ASSERTE(m_lContLen == MAXLONG, KP_E_FILE_FORMAT, null, True);

         chunk_length = m_lRestChunkLength; // m_lNextChunkLength;
         m_lRestChunkLength = 0L; // m_lNextChunkLength = 0L;

         while((chunk_length > 0) && SUCCEEDED(retc))
         {
// ---------- jei netilps á buferá – nukandam
            if(SUCCEEDED(retc))
            {
               m_lRestChunkLength = 0L;
               if(chunk_length > buf_len - (pntd - pBuf) - 1)
                  m_lRestChunkLength = chunk_length - (buf_len - (pntd - pBuf) - 1);
            }

// ---------- tiek skaitysim ið dabartinio chunk
            if(SUCCEEDED(retc)) chunk_length -= m_lRestChunkLength;

// ---------- chunk
            if((chunk_length > 0) && SUCCEEDED(retc))
            {
               retc = GetChunk(chunk_length, &pntd, pBuf, buf_len, bOutMsg, m_lRestChunkLength == 0L);

// ---------- next chunk length
               chunk_length = 0;
               if((m_lRestChunkLength == 0L) && SUCCEEDED(retc)) retc = GetChunkLength(&chunk_length, bOutMsg);
            }

         } // while((chunk_length > 0) && SUCCEEDED(retc))

// kai paskutinis gabalas, gali likti nebent Cr/Lf (2 baitai)
         if(m_lRestChunkLength == 0L)
//       if(m_lNextChunkLength == 0L)
            KP_ASSERT(m_lChunkRest <= 2L, KP_E_SYSTEM_ERROR, null, False);

      } // if(m_iTrMode == HTTP_TR_CHUNK_MODE)
// ------------------------
      else
      {
         KP_ASSERTE(m_lContLen != MAXLONG, E_NOTIMPL, null, bOutMsg); // Content-Length: 999

long read = m_lRestChunkLength;
         if(read > buf_len - 1) read = buf_len - 1;

         m_lRestChunkLength -= read;

         for(long ll = 0L; (ll < read) && SUCCEEDED(retc); ll++)
             retc = GetByte(pntd++, bOutMsg);

      } // else // if(m_iTrMode == HTTP_TR_CHUNK_MODE)

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      *pntd = Nul;
      *plRead = pntd - pBuf;
   }

return(retc);
}


#define KPSOCK_RCVBUF_CHUNK_SIZE KP_MAX_FILE_LIN_LEN

HRESULT KpSocket::RcvHttpMsg(unsigned char **ppBuf, long *plRead, bool bOutMsg, bool bRcvHdr)
{
HRESULT retc = S_OK;

   KP_ASSERT(ppBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(plRead != NULL, E_INVALIDARG, null, True);

// ---------------------------------------
   if(SUCCEEDED(retc)) *plRead = 0L;
long cur_buf_size = KPSOCK_RCVBUF_CHUNK_SIZE;
   KP_NEWA(*ppBuf, unsigned char, cur_buf_size + KPSOCK_RCVBUF_CHUNK_SIZE + 100);

long read = KPSOCK_RCVBUF_CHUNK_SIZE;
unsigned char *pntd = null;
   if(SUCCEEDED(retc)) pntd = *ppBuf;

   if(SUCCEEDED(retc)) retc = RcvHttpMsg(pntd, &read, bOutMsg, bRcvHdr);
   KP_ASSERTE(read <= KPSOCK_RCVBUF_CHUNK_SIZE, KP_E_BUFFER_OVERFLOW, null, bOutMsg);
   if(SUCCEEDED(retc))
   {
      pntd[read] = Nul;
      *plRead += read;
      pntd += read;
   }

   if(SUCCEEDED(retc)) do
   {
      read = KPSOCK_RCVBUF_CHUNK_SIZE;
      retc = RcvHttpRest(pntd, &read, bOutMsg);
      KP_ASSERTE(read <= KPSOCK_RCVBUF_CHUNK_SIZE, KP_E_BUFFER_OVERFLOW, null, bOutMsg);
      if((read > 0) && SUCCEEDED(retc))
      {
         pntd[read] = Nul;
         *plRead += read;

// realokuojam
unsigned char *buf_ptr_sav = *ppBuf;
         *ppBuf = null;
         cur_buf_size += KPSOCK_RCVBUF_CHUNK_SIZE;
         KP_NEWA(*ppBuf, unsigned char, cur_buf_size + KPSOCK_RCVBUF_CHUNK_SIZE + 100);
         memcpy(*ppBuf, buf_ptr_sav, cur_buf_size);
         KP_DELETEA(buf_ptr_sav);

         pntd = *ppBuf + *plRead;
      }

   } while((read > 0) && SUCCEEDED(retc));

return(retc);
}


// -------------------------------------------------------
// GET /favicon.ico HTTP/1.1
// POST /friends.htm HTTP/1.1
HRESULT KpSocket::RcvHttpRequest(bool bOutMsg)
{
HRESULT retc=S_OK;
#if FALSE
long read;

   read = MAX_HTTP_HDR_LEN;

   if(SUCCEEDED(retc)) retc = ReceiveMsg(m_lpszHdrBuf, &read, True, bOutMsg);
// -------------------------------------------------

   if(SUCCEEDED(retc))
   {
      m_lpszHdrBuf[read] = Nul;

#  if FALSE // #ifdef Debug
KP_TRACE("--------------- Request received:");
KP_TRACE(m_lpszHdrBuf);
#  endif
// KpMsgOut(m_lpszHdrBuf, IDI_ASTERISK, KP_MB_TESTI);

#  ifdef Debug // #if TRUE //
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab"); // "http_req.txt"
fputs("-- RcvHttpRequest() -------------------\n>>>\n", out_file);
fputs((const char *)m_lpszHdrBuf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#  endif
      retc = ScanHdr(HTTP_REQUEST_UNKNOWN, bOutMsg);

//    if(retc == KP_E_NEG_ANSW)
//    {
// iðsaugojam KP_E_NEG_ANSW
//       retv = retc;
//       retc = S_OK;
//    }

   }
#endif

   if(SUCCEEDED(retc))
   {
      retc = RcvHdr(HTTP_REQUEST_UNKNOWN, bOutMsg);
// KP_TRACE("RcvHttpRequest(): RcvHdr()");

//    if(retc == KP_E_NEG_ANSW)
//    {
// iðsaugojam KP_E_NEG_ANSW
//       retv = retc;
//       retc = S_OK;
//    }
   }

// if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}


//---------------------
// HTTP/1.1 200 OK
// Date: Mon, 19 Jul 2004 06:43:58 GMT
// Server: Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2
// Last-Modified: Thu, 15 Jul 2004 16:29:04 GMT
// ETag: "23-40f6b0d0"
// Accept-Ranges: bytes
// Content-Length: 35
// Connection: close
// Content-Type: text/plain
//
// KpReg-Error: Licenzija jau u_imta

HRESULT KpSocket::SendHttpMsg(const unsigned char *lpszMsg, bool bOutMsg, const unsigned char *lpszFileType, int iHTTP_RetCode)
{
HRESULT retc = S_OK;
unsigned char *buf_ptr = NULL;
struct tm *tm_time;
time_t t_time;
unsigned char e_tag[MAX_LONG_DIGITS + 10];
unsigned char *pntd = NULL;
unsigned char date_buf[WND_DATE_TEXT_LENGTH+1];
const unsigned char *msg_ptr = (unsigned char *)"";

   if(
      ((lpszMsg == NULL) || (lpszFileType == NULL)) &&
      IsHTTPdataMsg(iHTTP_RetCode) && SUCCEEDED(retc)
     )
   {
      retc = E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   if(lpszMsg && SUCCEEDED(retc)) msg_ptr = lpszMsg;

   if((m_PackedUrl.m_iProtocol != HTTP_PROT) && SUCCEEDED(retc))
   {
      retc = KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

   KP_NEWA(buf_ptr, unsigned char, MAX_HTTP_HDR_LEN + strlen(msg_ptr) + strlen(m_PackedUrl.m_lpszServerName) + 100);

   if(SUCCEEDED(retc))
   {
      time(&t_time);
      sprintf((char *)e_tag, "%ld", t_time);
      tm_time = localtime(&t_time);
      strcpy(date_buf, asctime(tm_time));
      pntd = strchr(date_buf, '\n');
      if(pntd) *pntd=Nul;

      if(IsHTTPdataMsg(iHTTP_RetCode) || (lpszMsg))
         sprintf((char *)buf_ptr, (const char *)HTTP_DATA_HDR_TPL, 1.1, iHTTP_RetCode, KpErrorProc.FormatErrorMessageHTTP(iHTTP_RetCode), date_buf,
            lpszProdName, lpszProdDate, e_tag, "bytes", strlen(msg_ptr)+2, lpszFileType);
      else if(IsHTTPcontinueMsg(iHTTP_RetCode))
         sprintf((char *)buf_ptr, (const char *)HTTP_CONT_HDR_TPL, 1.1, iHTTP_RetCode, KpErrorProc.FormatErrorMessageHTTP(iHTTP_RetCode), date_buf,
            lpszProdName, lpszProdDate, e_tag, 300);
      else
         sprintf((char *)buf_ptr, (const char *)HTTP_NOTIF_HDR_TPL, 1.1, iHTTP_RetCode, KpErrorProc.FormatErrorMessageHTTP(iHTTP_RetCode), date_buf,
            lpszProdName, lpszProdDate, e_tag);
#if FALSE // #ifdef Debug
KP_TRACE("---------------------- Answer sent:");
KP_TRACE(buf_ptr);
#endif
      if(lpszMsg)
      {
         strcat(buf_ptr, lpszMsg);
         strcat(buf_ptr, "\r\n");
      }

#if FALSE // #ifdef Debug
KP_TRACE("---------------------- Answer sent:");
KP_TRACE(buf_ptr);
#endif

      retc = SendMsg(buf_ptr, strlen(buf_ptr), bOutMsg);
   }

   KP_DELETEA(buf_ptr);

return(retc);
}


// =================================================
#if FALSE
HRESULT KpSocket::GetPostVars(RecListEntry **pVarList, bool bOutMsg)
{
HRESULT retc=S_OK;
long read;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char sav_chr;
int str_len;
int ii;
long buf_len = 0L;
bool endfl = False;
unsigned char *data_buf = NULL;
PostVarRec var_rec;
   var_rec.m_lpszVarName[0] = Nul;
   var_rec.m_lpszVarData[0] = Nul;
bool header_level = True;


   if((pVarList==NULL) && SUCCEEDED(retc))
   {
      retc = E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

// --------------------------------------- receive data header
// headerio galas siaip ateina antru paketu, bet dabar jau apdorojamas RcvHttpRequest() su RcvHdr()
// if(SUCCEEDED(retc))
// {
//    retc = RcvHdr(HTTP_POST_REQUEST, bOutMsg);

//    if(retc == KP_E_NEG_ANSW)
//    {
// iðsaugojam KP_E_NEG_ANSW
//       retv = retc;
//       retc = S_OK;
//    }
// }

// ------------------------------ receive data part
   if(SUCCEEDED(retc))
   {
      buf_len = MAX_HTTP_HDR_LEN;
      if(m_lContLen != MAXLONG) buf_len = m_lContLen;

      KP_NEWA(data_buf, unsigned char, buf_len + 1);
   }

   if(SUCCEEDED(retc))
   {
      pntd=data_buf;
      endfl=False;
      *pntd=Nul;
      do
      {
         if(m_lContLen!=MAXLONG){ if(pntd-data_buf>=m_lContLen) endfl=True; }
         else if(pntd-data_buf>=buf_len)
         {
            retc=KP_E_BUFFER_OVERFLOW;
            KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
         }

         if((!endfl) && SUCCEEDED(retc))
         {
            read=buf_len-(pntd-data_buf);

            retc = ReceiveMsg(pntd, &read, True, bOutMsg);

            if(SUCCEEDED(retc))
            {
               pntd[read]=Nul;
// KP_TRACE(pntd);
               if(strstr(pntd, m_lpszEndBoundary)) endfl=True;

               pntd+=read;
            }

         } // if(!endfl)

      } while((!endfl) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

#ifdef Debug // #if TRUE //
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab"); // "http_post_data.txt"
fputs("-- GetPostVars() -------------------\n>>>\n", out_file);
fputs((const char *)data_buf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif



// -----------------------------287452692419072
// Content-Disposition: form-data; name="IP"
//
// 123
// -----------------------------287452692419072
// Content-Disposition: form-data; name="Band"
//
// 456
// -----------------------------287452692419072--

// ------------------------------ scan data part
   if(SUCCEEDED(retc))
   {
      pnts=pntd=data_buf;

// praleidziam pirma boundary
      while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;

      sav_chr = (*pntd);
      *pntd = Nul;

      if(strstr(pnts, m_lpszBoundary)!=NULL)
      {
         if(strcmp(pnts, m_lpszBoundary)!=0)
            KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);

         *pntd=sav_chr;

//       while(*pntd && (strchr(lpszEols, *pntd)!=NULL)) pntd++;
         if(*pntd==Cr) pntd++;
         if(*pntd==Lf) pntd++;

         pnts=pntd;
      }
      else
      {
#if FALSE
KP_TRACE(".....................>>>");
KP_TRACE(pnts);
KP_TRACE(m_lpszBoundary);
KP_TRACE(".....................<<<");
#endif
         KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);
         *pntd=sav_chr;
         pntd=(unsigned char *)pnts;
      }

      var_rec.m_lpszVarName[0]=Nul;
      var_rec.m_lpszVarData[0]=Nul;
      header_level=True;

      do
      {
         while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;

         sav_chr=(*pntd);
         *pntd=Nul;

         str_len=pntd-pnts;

         if(header_level)
         {
            if(str_len==0)header_level=False;
            else
            {
               if(strchr(pnts, ':')==NULL)
               {
                  retc=KP_E_TRANS_ERR;
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }

               if(strstr(pnts, "Content-Disposition:")==pnts)  // form-data; name="IP"
               {                                               // file; filename="file1.txt"
                  pnts += strlen("Content-Disposition:");
                  while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                  if(strstr(pnts, "form-data;")!=pnts)
                  {
                     retc=E_NOTIMPL;
                     KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                  }
                  else pnts += strlen("form-data;");
                  if(SUCCEEDED(retc))
                  {
                     while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
                     if(strstr(pnts, "name=")!=pnts)
                     {
                        retc=KP_E_KWD_NOT_FOUND;
                        KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                        else pnts+=strlen("name=");
                     }
                  if(SUCCEEDED(retc))
                     if(strlen(pnts)>=KP_KWD_LEN)
                     {
                        retc=KP_E_BUFFER_OVERFLOW;
                        KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                  if(SUCCEEDED(retc))
                  {
                     if(*pnts=='\"') pnts++;
                     else
                     {
                        retc=KP_E_MSG_FORMAT;
                        KpErrorProc.OutputErrorMessage(retc, pnts, bOutMsg, __FILE__, __LINE__, 0L);
                        KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                  }
                  if(SUCCEEDED(retc))
                  {
                     strcpy(var_rec.m_lpszVarName, pnts);
                     ii=strlen(pnts)-1;
                     if(ii<0)
                     {
                        retc=KP_E_MSG_FORMAT;
                        KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                  }
                  if(SUCCEEDED(retc))
                  {
                     if(var_rec.m_lpszVarName[ii]=='\"') var_rec.m_lpszVarName[ii] = Nul;
                     else
                     {
                        retc=KP_E_MSG_FORMAT;
                        KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                     }
                  }
               }
               else if(strstr(pnts, "Content-Type:")==pnts)    // multipart/mixed; boundary=BbC04y
               {                                               // text/plain
                  retc=E_NOTIMPL;                              // image/gif
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }
               else if(strstr(pnts, "Content-Transfer-Encoding:")==pnts)  // binary
               {
                  retc=E_NOTIMPL;
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }
               else if(strstr(pnts, m_lpszBoundary)!=NULL)
               {
                  retc=KP_E_MSG_FORMAT;
                  KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
               }
               else
               {
                  KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, pnts, False, __FILE__, __LINE__, 0L);
                  KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);
               }

            } // if(str_len>0)

         } // if(header_level)
         else
         {
            if(strstr(pnts, m_lpszBoundary)!=NULL)
            {
               if(strstr(pnts, m_lpszBoundary)!=pnts)
                  KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
                  if(var_rec.m_lpszVarName[0]!=Nul)
                  {
                     if(*pVarList) (*pVarList)->PutToEnd(&var_rec, sizeof(PostVarRec));
                     else KP_NEWO(*pVarList, RecListEntry_tag(&var_rec, sizeof(PostVarRec)));
                  }
                  else
                     KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  var_rec.m_lpszVarName[0]=Nul;
                  var_rec.m_lpszVarData[0]=Nul;
                  header_level=True;
               }
            }
            else
            {
               if(var_rec.m_lpszVarData[0]!=Nul)
                  KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  if(strlen(pnts)>=KP_MAX_FILE_LIN_WDT)
                  {
                     retc=KP_E_BUFFER_OVERFLOW;
                     KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
                  }
               if(SUCCEEDED(retc)) strcpy(var_rec.m_lpszVarData, pnts);
            }

         } // else // if(header_level)

         *pntd=sav_chr;

//       while(*pntd && (strchr(lpszEols, *pntd)!=NULL)) pntd++;
         if(*pntd==Cr) pntd++;
         if(*pntd==Lf) pntd++;

         pnts=pntd;

      } while((*pnts) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

   KP_DELETEA(data_buf);

// if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}
#endif


// =================================================
HRESULT KpSocket::GetPostVars(KpTreeEntry **pVarList, bool bOutMsg)
{
HRESULT retc = S_OK;
HRESULT retv = S_OK;
PostVarRec var_rec;
   var_rec.m_lpszVarName[0]=Nul;
   var_rec.m_lpszVarData[0]=Nul;
unsigned char line_buf[KP_MAX_FILE_LIN_WDT+1];


   if((pVarList==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, bOutMsg, __FILE__, __LINE__, 0L);
   }

// -----------------------------287452692419072
// Content-Disposition: form-data; name="IP"
//
// 123
// -----------------------------287452692419072
// Content-Disposition: form-data; name="Band"
//
// 456
// -----------------------------287452692419072--


// ==================================================
// Mozilla FireFox:

// POST /admins.htm HTTP/1.1
// Host: 127.0.0.1:13006
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.0.10) Gecko/20070216 Firefox/1.5.0.10
// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
// Accept-Language: en-us,en;q=0.5
// Accept-Encoding: gzip,deflate
// Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Referer: http://127.0.0.1:13006/admins.htm
// Content-Type: multipart/form-data; boundary=---------------------------305932780025036
// Content-Length: 246
//
// -----------------------------305932780025036
// Content-Disposition: form-data; name="ButNum"
//
// 2
// -----------------------------305932780025036
// Content-Disposition: form-data; name="IP"
//
// 2.2.2.2
// -----------------------------305932780025036--


// ======================================================
// IE 7:

// POST /admins.htm HTTP/1.1
// Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*
// Referer: http://10.2.0.24:13006/admins.htm
// Accept-Language: lt
// Content-Type: multipart/form-data; boundary=---------------------------7d73089100ca
// UA-CPU: x86
// Accept-Encoding: gzip, deflate
// User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)
// Host: 10.2.0.24:13006
// Content-Length: 239
// Connection: Keep-Alive
// Cache-Control: no-cache
//
// -----------------------------7d73089100ca
// Content-Disposition: form-data; name="ButNum"
//
// 2
// -----------------------------7d73089100ca
// Content-Disposition: form-data; name="IP"
//
// 10.2.0.54
// -----------------------------7d73089100ca--


// ======================================================
// lynx:

// POST /admins.htm HTTP/1.1
// Host: 10.2.0.24:13006
// User-Agent: Links (1.00pre12; Linux 2.6.8-2-386 i686; 80x24) (Debian pkg 0.99+1.00pre12-1sarge1)
// Accept: */*
// Accept-Charset: us-ascii, ISO-8859-1, ISO-8859-2, ISO-8859-4, ISO-8895-5, ISO-8859-7, ISO-8895-9, ISO-8859-13, ISO-8859-15, ISO-8859-16, windows-1250, windows-1251, windows-1257, cp437, cp737, cp850, cp852, cp866, x-cp866-u, x-mac, x-mac-ce, x-kam-cs, koi8-r, koi8-u, TCVN-5712, VISCII, utf-8
// Connection: Keep-Alive
// Content-Type: multipart/form-data; boundary=00000000000000000000000000000000
// Content-Length: 217
//
// --00000000000000000000000000000000
// Content-Disposition: form-data; name="ButNum"
//
//
// --00000000000000000000000000000000
// Content-Disposition: form-data; name="IP"
//
// 10.2.0.13
// --00000000000000000000000000000000--


#ifdef Debug // #if TRUE //
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab"); // "http_post_data.txt"
fputs("-- GetPostVars() -------------------\n>>>\n", out_file);
fclose(out_file);
#endif

// KP_TRACE("================================");

   do
   {
// boundary
      if(SUCCEEDED(retc)) retc=GetLine(line_buf, KP_MAX_FILE_LIN_WDT, bOutMsg);
#ifdef Debug // #if TRUE //
out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs((const char *)line_buf, out_file);
fputs("\n", out_file);
fclose(out_file);
#endif

      if(SUCCEEDED(retc)) if(strstr(line_buf, m_lpszBoundary)!=line_buf)
      {
         retc=KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, line_buf, bOutMsg, __FILE__, __LINE__, 0L);
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }

// end boundary
      if(SUCCEEDED(retc)) if(strstr(line_buf, m_lpszEndBoundary)==line_buf) break;

// data segment header
      if(SUCCEEDED(retc))
      {
         retc=RcvHdr(HTTP_POST_DATA_SEGM, bOutMsg);
#ifdef Debug // #if TRUE // RcvHdr() jau isveda
out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs((const char *)m_lpszHdrBuf, out_file);
fclose(out_file);
#endif
         if(retc == KP_E_NEG_ANSW)
         {
// iðsaugojam KP_E_NEG_ANSW
            retv = retc;
            retc = S_OK;
         }
      }

      if((strlen(m_lpszCtrlName)==0) && SUCCEEDED(retc))
      {
         retc=KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }

// value
      if(SUCCEEDED(retc)) retc=GetLine(line_buf, KP_MAX_FILE_LIN_WDT, bOutMsg);
#ifdef Debug // #if TRUE //
out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs((const char *)line_buf, out_file);
fputs("\n", out_file);
fclose(out_file);
#endif

      if(SUCCEEDED(retc)) if(strstr(line_buf, m_lpszBoundary)==line_buf)
      {
         retc=KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, line_buf, bOutMsg, __FILE__, __LINE__, 0L);
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc)) if(m_lpszCtrlName[0]==Nul)
      {
         retc=KP_E_MSG_FORMAT;
         retc=KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) if(strlen(line_buf)>=KP_MAX_FILE_LIN_WDT)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc))
      {
         strcpy(var_rec.m_lpszVarName, m_lpszCtrlName);
         strcpy(var_rec.m_lpszVarData, line_buf);

// KP_TRACE(var_rec.m_lpszVarName);
// KP_TRACE(var_rec.m_lpszVarData);

         if(*pVarList) (*pVarList)->PutToEnd(&var_rec, sizeof(PostVarRec));
         else KP_NEWO(*pVarList, KpTreeEntry(&var_rec, sizeof(PostVarRec), NULL));
      }

   } while(SUCCEEDED(retc));

#ifdef Debug // #if TRUE //
out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("<<<\n", out_file);
fclose(out_file);
#endif

   if(SUCCEEDED(retc)) retc = retv; // gràþinam KP_E_NEG_ANSW

return(retc);
}
