//-------------------------------------------
HRESULT KpStApp::InitAcro60(void)
{
HRESULT retc=S_OK;
DWORD data_val;
char *str_val;
bool eboard = False;
// int wnd_y;
// HDC dc = NULL;
HKEY key = NULL;
LONG retw = ERROR_SUCCESS;

// if(SUCCEEDED(retc)) retc=GetIniEboard(&eboard);
   eboard = False;

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0] // patikrint, ar susikuria??!!!

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AdsInReader] // Tado.5c9

// "bShowAds"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdsInReader", "bShowAds", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "sAdsLastUpdate"=hex:32,30,30,38,30,38,31,33,30,38,34,33,31,31,5a,00
// "20080813111803Z"
   if(eboard && SUCCEEDED(retc))
   {
      str_val="20080813111803Z";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdsInReader", "sAdsLastUpdate", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AdobeViewer]

// kad neklaustu licenzijos
// "EULA"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "EULA", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// kad maksimizuotu langa
// "MaxApp"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "MaxApp", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// kad maksimizuotų dokumentą - projektas pprc
// išmesti parametrą "MaxDoc"=dword:00000000
   if(SUCCEEDED(retc))
   {
      if(ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer",
            0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &key, NULL))
      {
         retc = KP_E_KWD_NOT_FOUND;
//       retc=KpErrorProc.OutputErrorMessage(retc, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         retw = RegDeleteValue(key, "MaxDoc");
//       if(retw != ERROR_SUCCESS)
//          retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      }

      if(key) RegCloseKey(key);
      key = NULL;

      retc = S_OK;
   }


// "DialogX0"=dword:000000cf
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x0000008a;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX0", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY0"=dword:000000cf
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x0000008a;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY0", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW0"=dword:00000438
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000438;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW0", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH0"=dword:0000027a
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x0000027a;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH0", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogX1"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX1", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY1"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY1", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW1"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW1", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH1"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH1", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogX2"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX2", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY2"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY2", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW2"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW2", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH2"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH2", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogX3"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX3", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY3"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY3", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW3"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW3", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH3"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH3", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogX4"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX4", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY4"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY4", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW4"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW4", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH4"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH4", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogX5"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogX5", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogY5"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogY5", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogW5"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogW5", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "DialogH5"=dword:ffff8000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0xffff8000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "DialogH5", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "xRes"=dword:000005a0
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x000005a0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "xRes", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "yRes"=dword:00000384
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000384;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer", "yRes", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVAlert] // patikrint, ar susikuria??!!!

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVAlert\cCheckbox]

// "iwarnFieldsWillNotBeSaved"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVAlert\\cCheckbox", "iwarnFieldsWillNotBeSaved", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iexitWithExternalDocsOpen"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVAlert\\cCheckbox", "iexitWithExternalDocsOpen", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// kad nepasakotu kazko apie paveikslus
// "iPictureTasksFeaturesNotice"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVAlert\\cCheckbox", "iPictureTasksFeaturesNotice", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iUBDontShowAgain"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVAlert\\cCheckbox", "iUBDontShowAgain", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral] // Tado.5c9

// "bToolbarsLocked"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral", "bToolbarsLocked", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bLastExitNormal"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral", "bLastExitNormal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "sInDocTabs"=hex:2a,42,6f,6f,6b,6d,61,72,6b,73,2c,53,69,67,6e,61,74,75,72,65,73,2c,4f,70,74,43,6f,6e,74,2c,54,68,75,6d,62,6e,61,69,6c,73,00
// "*Bookmarks,Signatures,OptCont,Thumbnails,AnnotManager."
   if(eboard && SUCCEEDED(retc))
   {
      str_val="*Bookmarks,Signatures,OptCont,Thumbnails,AnnotManager.";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral", "sInDocTabs", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars] // patikrint, ar susikuria??!!!

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c0]

// "sToolBarName"=hex:46,69,6c,65,00 // "File"
   if(SUCCEEDED(retc))
   {
      str_val="File";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c0", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c11]

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
   if(SUCCEEDED(retc))
   {
      str_val="Navigation";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c11", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c12]

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
   if(SUCCEEDED(retc))
   {
      str_val="Navigation";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iDockPosition"=dword:00000004
   if(eboard && SUCCEEDED(retc))
   {
      data_val=4;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iDockPosition", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:7fffffff
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x7fffffff;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOrder"=dword:00000005
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000005;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iOrder", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000001;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bWindowHidden"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "bWindowHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c12", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c13]

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
   if(SUCCEEDED(retc))
   {
      str_val="Properties";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c13", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c14]

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
   if(SUCCEEDED(retc))
   {
      str_val="Properties";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iDockPosition"=dword:00000004
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000004;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iDockPosition", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:7fffffff
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x7fffffff;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOrder"=dword:00000005
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000005;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iOrder", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000002
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000002;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bWindowHidden"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "bWindowHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c14", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c15]

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
   if(SUCCEEDED(retc))
   {
      str_val="Commenting";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bWindowHidden"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "bWindowHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c15", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c16]

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
   if(SUCCEEDED(retc))
   {
      str_val="Commenting";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iDockPosition"=dword:00000004
   if(eboard && SUCCEEDED(retc))
   {
      data_val=4;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iDockPosition", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:7fffffff
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x7fffffff;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOrder"=dword:0000000a
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x0000000a;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iOrder", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000001;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bWindowHidden"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "bWindowHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:80000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x80000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c16", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c17]

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
   if(SUCCEEDED(retc))
   {
      str_val="JSToolBar";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000000 // 00000001
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iDockPosition"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iDockPosition", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

#if FALSE
   if(eboard && SUCCEEDED(retc))
   {
      wnd_y = iWndCaptionHgt;

      dc=GetDC(HWND_DESKTOP);
      if(dc==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
      else
         wnd_y = GetDeviceCaps(dc, VERTRES) - 24 - iWndCaptionHgt;
   }
#endif

// #if FALSE
// "iWindowBottom"=dword:00000037
   if(eboard && SUCCEEDED(retc))
   {
      data_val = 0x0000006e; // 0x000000ca; // wnd_y + 24;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000013
   if(eboard && SUCCEEDED(retc))
   {
      data_val = 0x0000004a; // 0x000000a6; // wnd_y;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }
// #endif

// "iWindowLeft"=dword:00000000
// "iWindowLeft"=dword:00000036
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000036; // 0x0000092;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000400
// "iWindowRight"=dword:0000045e
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x0000045e; // 0x000004ba;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c17", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c18]

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
   if(SUCCEEDED(retc))
   {
      str_val="JSToolBar";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000000 // 00000001
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bInDoc"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "bInDoc", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iLayout"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iLayout", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:7fffffff
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x7fffffff;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOrder"=dword:00000032
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000032;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iOrder", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000001
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000001;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c18", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c2]

// "sToolBarName"=hex:42,61,73,69,63,54,6f,6f,6c,73,00 // "BasicTools"
   if(SUCCEEDED(retc))
   {
      str_val="BasicTools";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c2", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c4]

// "sToolBarName"=hex:56,69,65,77,69,6e,67,00 // "Viewing"
   if(SUCCEEDED(retc))
   {
      str_val="Viewing";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c4", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c7]

// "sToolBarName"=hex:52,6f,74,61,74,65,00 // "Rotate"
   if(SUCCEEDED(retc))
   {
      str_val="Rotate";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c7", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c9]

// "sToolBarName"=hex:54,61,73,6b,73,00 // "Tasks"
   if(SUCCEEDED(retc))
   {
      str_val="Tasks";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bExternal"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "bExternal", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iOffset"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iOffset", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iStackNum"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iStackNum", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowBottom"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iWindowBottom", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowLeft"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iWindowLeft", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowRight"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iWindowRight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iWindowTop"=dword:00000000
   if(eboard && SUCCEEDED(retc))
   {
      data_val=0x00000000;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AVGeneral\\cToolbars\\c9", "iWindowTop", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }


// -------------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\FeatureLockdown] // Tado.5c9

// "bShowAdsAllow"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FeatureLockdown", "bShowAdsAllow", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bUpdater"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FeatureLockdown", "bUpdater", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\FormsPrefs]

// "bAutoCompleteOnTab"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bAutoCompleteOnTab", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bFocusRect"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bFocusRect", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bInlineAutoComplete"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bInlineAutoComplete", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bRecordNewEntries"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bRecordNewEntries", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bRuntimeHighlight"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bRuntimeHighlight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bRuntimeShowOverflow"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bRuntimeShowOverflow", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bShowDropDown"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bShowDropDown", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bStoreNumericEntries"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bStoreNumericEntries", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bUserAskedToEnableAutoComplete"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\FormsPrefs", "bUserAskedToEnableAutoComplete", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\JSPrefs] // Tado.5c9

// "bEnableJS"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\JSPrefs", "bEnableJS", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Originals]

// "bDisplayAboutDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "bDisplayAboutDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iTrustedMode"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "iTrustedMode", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bBrowserIntegration"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "bBrowserIntegration", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bBrowserCheck"=dword:00000000
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "bBrowserCheck", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bSkipDeleteWarnings"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "bSkipDeleteWarnings", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "sProofingSpace"=hex:55,2e,53,2e,20,57,65,62,20,43,6f,61,74,65,64,20,28,53,57,4f,50,29,20,76,32,00
// "U.S. Web Coated (SWOP) v2"
   if(eboard && SUCCEEDED(retc))
   {
      str_val="U.S. Web Coated (SWOP) v2";
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Originals", "sProofingSpace", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1, True);
   }


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Updater] // Tado.5c9

// "bShowAutoUpdateConfDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Updater", "bShowAutoUpdateConfDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "bShowNotifDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Updater", "bShowNotifDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// "iUpdateFrequency"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\Updater", "iUpdateFrequency", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), True);
   }

// KpSleep(5000, m_hBitmapWindow); // eboard ka_ko kartais nesuveikia
// KpMsgOut("InitAcro60()", IDI_ASTERISK, KP_MB_TESTI);

return(retc);
}
