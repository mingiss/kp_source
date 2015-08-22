//---------------------
// kpsock.h
// Win32 sockets
//


#ifndef kpsock_included
#define kpsock_included


#define HTTP_GET_REQUEST_CMD ((const unsigned char *)"GET")
#define HTTP_POST_REQUEST_CMD ((const unsigned char *)"POST")

#define KPSOCK_URL_HTTP_PREFIX ((const unsigned char *)"http://")
#define KPSOCK_URL_FTP_PREFIX ((const unsigned char *)"ftp://")

#define KPSOCK_HTTP_HDR_PREFIX ((const unsigned char *)"HTTP/1.1")

#define KPSOCK_BLOCK_TIMEOUT 5

// pranesimo (requesto/atsakymo su/be papildomu duomenu gabalu) tipai 
typedef enum
{
   HTTP_MSG_TYPE_UNKNOWN,  // 0  // former NO_REQUEST,
     
// request'ai:
   HTTP_REQUEST_UNKNOWN,   // 1  // HTTP_GET_REQUEST arba HTTP_POST_REQUEST
   HTTP_GET_REQUEST,       // 2
   HTTP_POST_REQUEST,      // 3

// post duomenys:   
   HTTP_POST_DATA_SEGM,    // 4  // paprastas duomenu gabaliukas
   HTTP_POST_SUBDATA_SEGM, // 5  // POST duomenu gabalas, kurio viduje yra kiti gabaliukai, 
                                 //    pradeda nauja rekursyvine POST_DATA_CHUNK seka su nauja boundary=
// atsakymas:
   HTTP_REPLY,             // 6  // atsakymas i requesta   
     
   NUM_OF_HTTP_MSG_TYPES   // 7  // former NUM_OF_REQUESTS

} HttpMsgTypes; // taip pat ir headeriu tipai // former RequestTypes

#define NUM_OF_HTTP_MSG_TYPES_1 NUM_OF_HTTP_MSG_TYPES

// HTTP header tags
typedef enum
{
   KPSOCK_HDTAG_None = (-1),

   KPSOCK_HDTAG_Date,
   KPSOCK_HDTAG_Server,
   KPSOCK_HDTAG_SetCookie,
   KPSOCK_HDTAG_LastModified,
   KPSOCK_HDTAG_XPoweredBy,
   KPSOCK_HDTAG_ETag,
   KPSOCK_HDTAG_AcceptRanges,
   KPSOCK_HDTAG_ContentLength,
   KPSOCK_HDTAG_TransferEncoding,
   KPSOCK_HDTAG_Connection,
   KPSOCK_HDTAG_KeepAlive,
   KPSOCK_HDTAG_ContentType,
   KPSOCK_HDTAG_ContentEncoding,
   KPSOCK_HDTAG_Host,
   KPSOCK_HDTAG_UserAgent,
   KPSOCK_HDTAG_Accept,
   KPSOCK_HDTAG_AcceptLanguage,
   KPSOCK_HDTAG_AcceptEncoding,
   KPSOCK_HDTAG_AcceptCharset,
   KPSOCK_HDTAG_Pragma,
   KPSOCK_HDTAG_CacheControl,
   KPSOCK_HDTAG_Referer,
   KPSOCK_HDTAG_IfModifiedSince,
   KPSOCK_HDTAG_IfNoneMatch,
   KPSOCK_HDTAG_ContentDisposition,
   KPSOCK_HDTAG_ContentTransferEncoding,
   KPSOCK_HDTAG_TE,
   KPSOCK_HDTAG_UA_CPU,
   KPSOCK_HDTAG_Location,
   KPSOCK_HDTAG_AcrobatVersion,
   KPSOCK_HDTAG_Expires,
   KPSOCK_HDTAG_ContentDescription,

   KPSOCK_NUM_OF_HDTAGS

} KpSockHdTag;

#define KPSOCK_NUM_OF_HDTAGS_7 KPSOCK_NUM_OF_HDTAGS

extern const unsigned char *KpsockMsgTypes[NUM_OF_HTTP_MSG_TYPES];
extern const unsigned char *KpsockTagNames[KPSOCK_NUM_OF_HDTAGS+1]; // gale NULL
extern const bool KpsockTagOccurences[KPSOCK_NUM_OF_HDTAGS][NUM_OF_HTTP_MSG_TYPES];

//---------------------
#define HTTP_PORT 80

#define KP_IPADDR_LOCAL_HOST ((const unsigned char *)"127.0.0.1") // former LOCAL_HOST
#define KP_INADDR_LOOPBACK  0x0100007f // sisteminis  atbulas: INADDR_LOOPBACK 0x7f000001

#define KP_IPADDR_BROADCAST ((const unsigned char *)"255.255.255.255") // former IP_BROADCAST

#define KP_MIN_USER_PORT 10000
#define KP_UDP_PORT_OFFSET 100

// former HTTP_REQ_TPL_1
#if TRUE // #if FALSE
#define HTTP_GET_REQ_TPL_MAIN ((const unsigned char *)\
   "%s %s HTTP/1.1\r\n" \
   "Host: %s:%d\r\n"          /* 127.0.0.1:80 */ \
   "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
   "Accept: */*\r\n" \
   "Accept-Language: lt\r\n"  /* en-us,en;q=0.5 */ \
   "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
   "Accept-Charset: ISO-8859-13\r\n"  /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
   "Keep-Alive: 300\r\n" \
   "Connection: keep-alive\r\n" \
   "\r\n")
#define HTTP_GET_REQ_TPL_TEXT ((const unsigned char *)\
   "%s %s HTTP/1.1\r\n" \
   "Host: %s:%d\r\n"          /* 127.0.0.1:80 */ \
   "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
   "Accept: text/*\r\n" \
   "Accept-Language: lt\r\n"  /* en-us,en;q=0.5 */ \
   "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
   "Accept-Charset: ISO-8859-13\r\n"  /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
   "Keep-Alive: 300\r\n" \
   "Connection: keep-alive\r\n" \
   "\r\n")
#define HTTP_GET_REQ_TPL_BIN ((const unsigned char *)\
   "%s %s HTTP/1.1\r\n" \
   "Host: %s:%d\r\n"          /* 127.0.0.1:80 */ \
   "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
   "Accept: */*\r\n" \
/* "Accept-Language: lt\r\n" */ /* en-us,en;q=0.5 */ \
   "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
/* "Accept-Charset: ISO-8859-13\r\n" */  /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
   "Keep-Alive: 300\r\n" \
   "Connection: keep-alive\r\n" \
   "\r\n")
#else
#define HTTP_GET_REQ_TPL_MAIN ((const unsigned char *)\
   "%s %s HTTP/1.1\r\n" \
   "Host: %s:%d\r\n" \
   "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; lt; rv:1.9.2.21) Gecko/20110830 Firefox/3.6.21\r\n" \
   "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n" \
   "Accept-Language: lt,en-us;q=0.8,en;q=0.6,ru;q=0.4,pl;q=0.2\r\n" \
   "Accept-Encoding: gzip,deflate\r\n" \
   "Accept-Charset: windows-1257,utf-8;q=0.7,*;q=0.7\r\n" \
   "Keep-Alive: 115\r\n" \
   "Connection: keep-alive\r\n" \
   "If-Modified-Since: 2011.09.07\r\n" \
   "If-None-Match: \"1315404252\"\r\n" \
   "Cache-Control: max-age=0\r\n" \
   "\r\n")
#endif

// Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1
// "Accept: text\r\n"  
// "Accept: text/*\r\n" 

// Tado Acrobato POST pranesimu kepure
#define HTTP_POST_REQ_TPL_ACRO ((unsigned char *) \
   "%s %s HTTP/1.1\r\n"       /* POST / HTTP/1.1 */ \
   "Host: %s:%d\r\n"          /* 127.0.0.1:80 */ \
   "User-Agent: %s\r\n"       /* AcroForms */ \
   "Accept: */*\r\n" \
   "Content-Type: application/x-www-form-urlencoded\r\n" \
   "Content-Length: %ld\r\n" \
   "Cache-Control: no-cache\r\n" \
   "\r\n")

#define HTTP_POST_REQ_TPL ((unsigned char *) \
   "%s %s HTTP/1.1\r\n"       /* POST /diag.php HTTP/1.1 */ \
   "Host: %s:%d\r\n"          /* Host: www.tev.lt:80 */ \
   "User-Agent: %s\r\n"       /* User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1) */ \
   "Accept: */*\r\n" \
   "Content-Length: %ld\r\n" \
   "Cache-Control: no-cache\r\n" \
   "Accept-Language: lt\r\n" \
   "UA-CPU: x86\r\n" \
   "Accept-Encoding: none\r\n" /* Accept-Encoding: gzip, deflate */ \
   "Connection: Keep-Alive\r\n")


#define HTTP_POST_REQ_TAIL_TPL ((unsigned char *) \
   "Referer: http://%s%s\r\n" /* Referer: http://www.tev.lt/diag.php */ \
   "Content-Type: multipart/form-data; boundary=%s\r\n" /* Content-Type: multipart/form-data; boundary=----------------------tv689907.tmp */ \
   "\r\n")

#define HTTP_POST_HDR_TPL ((unsigned char *)\
   "Content-Type: multipart/form-data; boundary=%s" /* ---------------------------287452692419072 */ \
   "Content-Length: %d"       /* 242 */ \
   "\r\n")
  

#define HTTP_DATA_HDR_TPL ((unsigned char *)\
   "HTTP/%1.1f %d %s\r\n"     /* 1.1 200 OK */ \
   "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
   "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
   "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
   "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
   "Accept-Ranges: %s\r\n"    /* bytes */ \
   "Content-Length: %d\r\n"   /* 35 */ \
   "Connection: close\r\n" \
   "Content-Type: %s\r\n"     /* text/plain */ \
   "\r\n")
              
#define HTTP_CONT_HDR_TPL ((unsigned char *)\
   "HTTP/%1.1f %d %s\r\n"     /* 1.1 100 Continue */ \
   "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
   "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
   "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
   "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
   "Keep-Alive: %d\r\n"       /* 300 */ \
   "Connection: keep-alive\r\n" \
   "\r\n")
              
#define HTTP_NOTIF_HDR_TPL ((unsigned char *)\
   "HTTP/%1.1f %d %s\r\n"     /* 1.1 404 File not found */ \
   "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
   "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
   "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
   "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
   "Connection: close\r\n" \
   "\r\n")

              
#define MIN_HTTP_HDR_LEN (min(min(strlen(HTTP_DATA_HDR_TPL), strlen(HTTP_CONT_HDR_TPL)), strlen(HTTP_NOTIF_HDR_TPL)))

// #define MAX_HTTP_HDR_LEN (max(max(strlen(HTTP_DATA_HDR_TPL), strlen(HTTP_CONT_HDR_TPL)), strlen(HTTP_NOTIF_HDR_TPL)))
// #define MAX_HTTP_HDR_LEN KP_MAX_FILE_LIN_LEN
// #define MAX_HTTP_HDR_LEN 8000
// #define MAX_HTTP_HDR_LEN 8001
// #define MAX_HTTP_HDR_LEN 100001L
#define MAX_HTTP_HDR_LEN ((100L * 1024) + 1) 

#define VAR_POST_BUF_LEN 4000 // max. GetPostVars() duomenu kiekis 

#define MIN_HTTP_POST_HDR_LEN (strlen(HTTP_POST_HDR_TPL))

#define HTTP_ANSW_OK 200               // 200 OK
#define HTTP_ANSW_FOUND 302            // 302 Found
#define HTTP_ANSW_FILE_NOT_FOUND 404
#define HTTP_ANSW_CONTINUE 100
#define HTTP_ANSW_CONFLICT 409

extern bool IsHTTPdataMsg(int iHTTP_RetCode);
extern bool IsHTTPcontinueMsg(int iHTTP_RetCode);
extern bool IsHTTPerrorMsg(int iHTTP_RetCode);

extern HRESULT TestIP(const unsigned char *lpszIpAddr);  // grazina E_INVALIDARG jei blogas formatas
                                                         // pranesimu neisveda

typedef enum
{ 
   NO_PROT,

   HTTP_PROT,
   FTP_PROT,
   
   NUM_OF_PROTS_0

} Protocols;   
#define NUM_OF_PROTS_1 NUM_OF_PROTS_0
extern const unsigned char *ProtocolNames[NUM_OF_PROTS_0];

typedef enum
{ 
   NORMAL_HTTP_TR_MODE, // visi duomenys vienu gabalu // former NO_MODE,
   
   HTTP_TR_CHUNK_MODE,    // tuscia eilute pries kiekviena gabaliuka
                  // po to - viena eilute - segmento ilgis - sesioliktainis skaicius
                  // pabaiga - segmentas su ilgiu 0
   
   NUM_OF_HTTP_TR_MODES_0

} HttpTransferModes;
#define NUM_OF_HTTP_TR_MODES_1 NUM_OF_HTTP_TR_MODES_0
extern const unsigned char *TransferModeNames[NUM_OF_HTTP_TR_MODES_0];

typedef struct
{
   unsigned char m_lpszServerName[KP_MAX_FNAME_LEN + 1]; // remote IP address or server name
   IN_ADDR m_Addr; // unsigned long m_lAddr; // resolved remote IP address
   Protocols m_iProtocol;
   int m_iPort;
   unsigned char m_lpszFileName[KP_MAX_FNAME_LEN+1]; // remote file name with possible query string
   unsigned char m_lpszServerNameUnres[KP_MAX_FNAME_LEN+1]; // remote IP address as get from the message header, before Resolve()
   
} PackedUrl;

typedef struct
{
   unsigned char m_lpszVarName[KP_KWD_LEN+1];
   unsigned char m_lpszVarData[KP_MAX_FILE_LIN_WDT+1];
}
PostVarRec;

//---------------------
class KpSocket                  
{                                            
   HRESULT m_lhOpenResult;
   SOCKET m_hSocket; // main socket
   SOCKET m_hAccSock;   // accepted socked for server applications

public:     
// priimamo paketo atributai, uzpildo ScanHdr()  
   HttpMsgTypes m_iMsgType; // former m_iReqType
   int m_iRetCode;            // 200 OK etc.
   unsigned char m_lpszRetMsg[KP_MAX_FILE_LIN_WDT /* MAX_HTTP_HDR_LEN */ + 1]; // klaidos praneðimas iðtrauktas ið HTTP headerio, tekstas einantis po 200, 404
   long m_lContLen;           // Content-Length:
   HttpTransferModes m_iTrMode;   // Transfer-Encoding:                  
   unsigned char m_lpszBoundary[KP_MAX_FILE_LIN_WDT /* MAX_HTTP_HDR_LEN */ +2+1]; // riba tarp POST duomenu segmentu
   unsigned char m_lpszEndBoundary[KP_MAX_FILE_LIN_WDT /* MAX_HTTP_HDR_LEN */ +4+1]; // paskutinio POST duomenu segmento galas
   unsigned char m_lpszCtrlName[KP_KWD_LEN+1];
  
   unsigned char *m_lpszHdrBuf; // [MAX_HTTP_HDR_LEN + 1];   

   PackedUrl m_PackedUrl;

   long m_lRestChunkLength; // RcvHttpMsg() dabar skaitomo chunk likæs ilgis, jei netilpo á pBuf[]; reikia iðkvietinëti RcvHttpRest(), kol perskaitytas ilgis bus 0L
// long m_lNextChunkLength; // sekanèio neperskaityto chunk ilgis, kai pasibaigia RcvHttpMsg() buferis, tokiu atveju iðkvietinëti RcvHttpRest(), kol perskaitytas ilgis bus 0L
   
   unsigned char *m_lpszChunkPos;   // GetChunkLength()/GetChunk() skaitymo pozicija buferyje m_lpszHdrBuf[] 
                                    // former pnts RcvHttpMsg()/RcvHttpRest()
                                    // former ppInBufPtr parametras GetChunkLength()/GetChunk() ir GetByte()     
   long m_lChunkRest; // GetChunkLength()/GetChunk() baitø skaièius nuo m_lpszChunkPos iki paskutiniu GetByte() perskaitytø baitø masyvo skaièiaus buferyje m_lpszHdrBuf[] 
                      // former rest RcvHttpMsg()/RcvHttpRest()
                      // former plRest parametras GetChunkLength()/GetChunk() ir GetByte()
   
   KpSocket(int type = SOCK_STREAM); // creates m_hSocket // type gali bûti SOCK_STREAM arba SOCK_DGRAM
   ~KpSocket();
   HRESULT GetOpenResult(void);        
   
// client routines
   HRESULT Resolve(const unsigned char *lpszUrl, bool bOutMsg); // saves resolved server address, protocol, port and file name to m_PackedUrl
   HRESULT Connect(bool bOutMsg); // connects m_hSocket to m_lAddr

// server routines
   HRESULT Bind(int iPort, unsigned long lAddr, bool bOutMsg = False); // binds m_hSocket to localhost:iPort for listening
                                        // lAddr: ADDR_ANY, INADDR_LOOPBACK
   HRESULT Listen(void); // switches m_hSocket to listening status, waits for incoming messages
   HRESULT Accept(void); // accepts incomming through m_hSocket message to new socket m_hAccSock
                         // fills m_PackedUrl
   
// ---------------------- lowest level, datagramm broadcast
   HRESULT SendTo(const unsigned char *pBuf, long lBufLen, bool bOutMsg);
                        // siunèia adresu m_PackedUrl.m_Addr.S_un.S_addr

   HRESULT RecvFromAsynch(unsigned char *pBuf, long *plBufLen, bool bOutMsg); // neblokuojantis, laukia KPSOCK_BLOCK_TIMEOUT sec.
                                                                           // paleidþia RecvFromProc atskiram threade
   HRESULT RecvFrom(unsigned char *pBuf, long *plBufLen, bool bOutMsg);
                        // *plBufLen áeinant turi turëti buferio max ilgá,
                        //          iðeinant gràþinamas priimtø baitø skaièius
                        // m_PackedUrl.m_Addr.S_un.S_addr ir m_PackedUrl.lpszServerName uþpildomas priimto praneðimo siuntëjo adresu –
                        //    jeigu reikia dar broadcastinti, m_PackedUrl.m_Addr.S_un.S_addr 
                        //    vël turi bûti nustatytas á INADDR_BROADCAST

// ---------------------- low level, stream sockets
   HRESULT SendMsg(const unsigned char *pBuf, long lBufLen, bool bOutMsg);
   HRESULT SendStr(const unsigned char *lpszBuf);
   HRESULT SendStr(const char *lpszBuf);

   HRESULT ReceiveMsg(unsigned char *pBuf, long *plRead, bool bSingleMsg, bool bOutMsg);
                                                            // on entering *plRead must be filled with length of pBuf
                                                            //    bSingleMsg==True - expected length of message unknown, receive only one block as header


   HRESULT GetChar(unsigned char *pcInChar, bool bOutMsg);  // actually ReceiveMsg(pcInChar, &1, True, bOutMsg);
                                                            // grazina KP_E_EOF jei negavo

   HRESULT GetCharD(unsigned char *pcInChar, bool bOutMsg); // GetChar() 
                                                            // dekrementuoja m_lContLen, jei ne 0
                                                            // jei dekrementavus pasiekia 0, duoda KP_E_EOF 
                                                            // naudojamas POST duomenu headeriams (HTTP_POST_DATA_SEGM)
                                                            //    ir patiems duomenims
   HRESULT GetLine(unsigned char *lpszStrBuf, int iBufLen, bool bOutMsg);
                                                            // GetCharD() iki eilutes pabaigos
                                                            
private: 
// ------------- methods used for RcvHttpMsg()
   HRESULT GetByte                  // read character through m_lpszHdrBuf[]
   (                                // uses m_lpszChunkPos and m_lChunkRest 
      unsigned char *pcInCh,        // character to read
//    long *plRest,                 // moved to m_lChunkRest // rest of received bytes after *ppBufPtr in m_lpszHdrBuf
//    unsigned char **ppInBufPtr,   // moved to m_lpszChunkPos // pointer of current byte in m_lpszHdrBuf
      bool bOutMsg
   );
   HRESULT UnGetByte                // unget character to m_lpszHdrBuf[]
   (                                // uses m_lpszChunkPos and m_lChunkRest
      unsigned char cInCh,          // character to unget
//    long *plRest,                 // moved to m_lChunkRest // rest of received bytes after *ppBufPtr in m_lpszHdrBuf
//    unsigned char **ppInBufPtr,   // moved to m_lpszChunkPos // pointer of current byte in m_lpszHdrBuf
      bool bOutMsg
   );
   HRESULT GetChunk                 // get HTTP chunk through m_lpszHdrBuf[]
   (                                // uses m_lpszChunkPos and m_lChunkRest
      long lChunkLength,
//    long *plRest,                 // moved to m_lChunkRest // rest of received bytes after *ppBufPtr in m_lpszHdrBuf
//    unsigned char **ppInBufPtr,   // moved to m_lpszChunkPos // pointer of current byte in m_lpszHdrBuf
      unsigned char **ppOutBufPtr,  // pointer of current byte in pBuf
      unsigned char *pBuf,          // output buffer itself
      long lBufLen,                 // size of pBuf
      bool bOutMsg,
      bool bFullChunk               // False – skaitomas tik gabalas chunk'o nuo einamosios pozicijos, nereikia suvalgyt chunko uodegoje esanèiø Cr/Lf
   );
   HRESULT GetChunkLength           // get HTTP chunk length from chunk header in current position of m_lpszHdrBuf[]
   (                                // uses m_lpszChunkPos and m_lChunkRest
      long *plChunkLength,          // scanned HTTP chunk length
//    long *plRest,                 // moved to m_lChunkRest // rest of received bytes after *ppBufPtr in m_lpszHdrBuf
//    unsigned char **ppInBufPtr,   // moved to m_lpszChunkPos // pointer of current byte in m_lpszHdrBuf
      bool bOutMsg
   );
public:                                      

// ------------------------------ HTTP level
   HRESULT SendHttpRequest(const unsigned char *lpszRequest, const unsigned char *lpszArg, bool bOutMsg, long lSimplyPostMsgLen = 0L, 
      bool bAcroPostMsg = True, const unsigned char *lpszPostBoundary = (const unsigned char *)"", const unsigned char *lpszHTTP_Template = HTTP_GET_REQ_TPL_MAIN);
                                                            // lpszArg – failo vardas

   HRESULT ReceiveHdr(HttpMsgTypes iMsgType, long *plRead, bool bOutMsg); 
                                    // priima iki tuscios eilutes i m_lpszHdrBuf
                                    // gale prideda Nul
                                    // *plRead pradzioj nustatyti nereikia
                                    // plRead gali buti NULL
                                    // iMsgType HTTP_MSG_TYPE_UNKNOWN, HTTP_POST_DATA_SEGM arba HTTP_REPLY

   HRESULT ScanHdrFileName(unsigned char **plpszHdrPtrPtr, bool bOutMsg); // ScanHdr() paprogramë 
   HRESULT ScanHdr(HttpMsgTypes iInitMsgType, bool bOutMsg);   
                                    // skanuoja m_lpszHdrBuf turini 
                                    // uzpildo memberius:
                                    //    m_iMsgType, m_iRetCode, m_lContLen, m_iTrMode, m_lpszBoundary, m_lpszEndBoundary
                                    //    TODO: uþpildyt m_lpszRetMsg
                                    // iInitMsgType HTTP_MSG_TYPE_UNKNOWN, HTTP_POST_DATA_SEGM arba HTTP_REPLY
                                    // jei priimta be klaidø, bet yra neigiamas HTTP atsakymas, praneðimo neiðveda (nepriklausomai nuo bOutMsg), bet gràþina klaidos kodà KP_E_NEG_ANSW

   HRESULT RcvHdr(HttpMsgTypes iInitMsgType, bool bOutMsg); // ReceiveHdr() + ScanHdr()    
                                    // jei priimta be klaidø, bet yra neigiamas HTTP atsakymas, praneðimo neiðveda (nepriklausomai nuo bOutMsg), bet gràþina klaidos kodà KP_E_NEG_ANSW

   HRESULT RcvHttpRequest(bool bOutMsg);
                                    // the same as RcvHdr()
                                    // receives and scans HTTP request header from newly accepted socket
                                    // fills m_PackedUrl structure, destroys data previously filled by Accept()
                                    // bOutMsg=False - do not output error messages, error code is still returned as result
   HRESULT RcvHttpMsg(unsigned char *pBuf, long *plRead, bool bOutMsg, bool bRcvHdr = True);
                                    // on entering *plRead must be filled with length of pBuf
                                    // scans and skips HTTP header RcvHdr()
                                    // bOutMsg=False - do not output error messages, error code is still returned as result
                                    // TODO - o gal ir visus GetByte() ir Co keist i GetChar()?
                                    // jei priimta be klaidø, bet yra neigiamas HTTP atsakymas, praneðimo neiðveda (nepriklausomai nuo bOutMsg), bet gràþina klaidos kodà KP_E_NEG_ANSW
                                    // jei pasibaigia pBuf, sustoja po eilinio chunk ilgio perskaitymo, uþpildo m_lNextChunkLength ir gráþta.
                                    // po to reikia iðkvietinëti RcvHttpRest(), kol perskaitytas ilgis bus 0L
                                    // TODO: problema, jei HTTP chunk ilgis pasitaikys didesnis, negu pBuf ilgis, kaþkà daryt – dalint eiliná chunk gabalais
                                    // jei bRcvHdr == False, RcvHdr() neiðkvieèia (naudojam, kai jau bûna priimtas anksèiau, tik paties (chunked) praneðimo kûno priëmimui)  
   HRESULT RcvHttpRest(unsigned char *pBuf, long *plRead, bool bOutMsg);
                                    // tæsia RcvHttpMsg() pradëtà praneðimo siuntimà
                                    // iðkvietinëti, kol *plRead gràþins 0L                                      
   HRESULT RcvHttpMsg(unsigned char **ppBuf, long *plRead, bool bOutMsg, bool bRcvHdr = True); 
                                    // RcvHttpMsg() su dinaminiu buferio iðskyrimu; 
                                    // *ppBuf áeinant turi bûti NULL, *plRead bet koks
                                    // jei ið pirmo karto nepataiko iðskirt uþtektinai, buferá didina ir iðkvietinëja RcvHttpRest()
   HRESULT SendHttpMsg(const unsigned char *lpszMsg, bool bOutMsg, const unsigned char *lpszFileType, int iHTTP_RetCode);
                                    // bOutMsg=False - do not output error messages, error code is still returned as result
                                    // lpszFileType parameter for Content-Type: HTTP tag:
                                    //    Content-Type: text/plain
                                    //    Content-Type: text/html; charset=ISO-8859-1
                                    //    Content-Type: image/jpeg
                                    // iHTTP_RetCode - look KpErrorProc_tag::FormatErrorMessageHTTP()
   HRESULT GetPostVars(KpTreeEntry **pVarList, bool bOutMsg);
                                    // priima POST metodu atsiustu kintamuju reiksmes
                                    // kintamuju reiksmes tik po viena eilute, 
                                    // duomenys siunciami tik vieno lygmens struktura
                                    //    netinka trecio tipo pranesimas (zr. GetPostVars() realizacija)
                                    // TODO perdaryt rekursiskai - lokalus headerio buferis,
                                    //    kai gauna nauja boundary Content-Type: multipart/mixed; boundary=BbC04y
                                    //    iskviecia save rekursiskai su tuo nauja boundary,
                                    //    po to grizta testi bloku su sena boundary
};


// parametrai RecvFromProc()
typedef struct{
KpSocket *m_This;
unsigned char *m_pBuf;
long *m_plBufLen;
bool m_bOutMsg;
DWORD m_iCallersThreadId;
} RecvFromProcPars;
   
extern DWORD WINAPI RecvFromProc(LPVOID lpParameter); // KpSocket::RecvFromAsynch() threado procedura; lpParameter - rodyklë á RecvFromProcPars  

extern void PutMsgFirewall(const unsigned char *lpszMsgFmt);

#endif
