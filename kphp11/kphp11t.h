// ------------------------------
// kphp11t.h
// local Win32 thread functions
//


#ifndef Kphp11t
#define Kphp11t

//------------------------------------ bendravimas su pagrindine Win32 aplikacija
#define KPHP11_POLL_TIMEOUT 100

// #define KPHP11_RC_TIMEOUT KP_TIMEOUT_TIMEOUT
#define KPHP11_RC_TIMEOUT 15000 // 3000

//------------------------------------
typedef struct KpHp11IdlePars_tag
{
   HINSTANCE hInstance;
   bool bOpenConsole;
} KpHp11IdlePars;

//----------------- funkcijos pagrindinei Win32 aplikacijai,
//                  veikia pagrindiniam thread'e
//                  siuncia pranesimus hp11 threado aplikacijai KpHp11Idle
class EmuTt
{
public:
   DWORD volatile m_lKphp11ThreadId;
   DWORD volatile m_lMainThreadId; // semaphore, to avoid duplicated EmuTt::RequestRemoteCall()
   DWORD volatile m_lPrevThreadId; // previous value of m_lMainThreadId, for duplicated WM_KP_REMOTE_CALL_DONE in EmuD_RCt::putw() 

   bool volatile m_bRCdone; // RC iškvietimo sinchronizacija, per WM_KP_REMOTE_CALL_DONE neišeina – xGecko praryja
   
   EmuTt(void);

// remote call processing
   HRESULT ExecRemoteCall(KpRcPars *pPars, bool bCheckErrors = False);
   HRESULT RequestRemoteCall(KpRcPars *pPars, bool bOutputErrorMessages = True);
   HRESULT WaitForRemoteCallCompletion(KpRcPars *pPars = NULL, bool bCheckErrors = False);

// main thread function, without starting of new thread
//    bOpenConsole - start emulator with opened console
// extern int PASCAL cWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
   int APIENTRY /* WinMain */ KpHp11Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, bool bOpenConsole);

// start idle loop in new thread
//    bOpenConsole - start emulator with opened console
   HRESULT KpHp11CreateThread(HINSTANCE hInstance, bool bOpenConsole);
   HRESULT StopThread(void);

   HRESULT GetHp11Variable(int *piVarPtr, int iHp11Address); // iskviecia KP_RC_GET_VARIABLE
   HRESULT GetHp11VariableLong(long *plVarPtr, int iHp11Address);
   HRESULT SetHp11Variable(int iValue, int iHp11Address); // iskviecia KP_RC_SET_VARIABLE

   HRESULT CallRCCallBack(KpCommonCallBackIxs iCallBackIx, bool bCheckErrors = False); // iškviečia iCallBackIx per hp11 RC mechanizmą 
   HRESULT CallRCCallBackRetC(KpCommonCallBackIxs iCallBackIx, bool bCheckErrors = False); // iškviečia iCallBackIx per hp11 RC mechanizmą; grąžina klaidos kodą iš iCallBackIx funkcijos 
};

extern EmuTt EmuTv;

// main idle loop - main function of hp11 thread
//    pPars->bOpenConsole - start emulator with opened console
extern DWORD WINAPI KpHp11Idle(LPVOID lpParameter); 


// ---------------------------
// atkelta iš kphp11rc.h
// callback funkciju lentele RC operacijoms, priklauso nuo KpRcOpCodes
// funkcijos offset lenteleje perduodamas lauke KpRcPars.enc.iCallBackIx
typedef HRESULT (*KpHp11ExtFun)(void *pPars);
extern int KpHp11NumOfExtFun;
extern KpHp11ExtFun KpHp11ExtFunTab[/* KpHp11NumOfExtFun */];

#endif
