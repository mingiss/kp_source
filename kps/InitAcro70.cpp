//-------------------------------------------
HRESULT KpStApp::InitAcro70(void)
{
HRESULT retc=S_OK;
DWORD data_val;
char *str_val;

// KpMsgOut("Pries InitAcro70", IDI_ASTERISK, KP_MB_TESTI);

#if FALSE
// ------------------------------------
// HKEY_CURRENT_USER, "Software\\Adobe\\Acrobat Reader\\7.0\\AdobeViewer"

// kad nemestu acrobato licenzijos
// "EULA"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "Software\\Adobe\\Acrobat Reader\\7.0\\AdobeViewer", "EULA", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "Software\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox"

// kad nemestu kazkokios informacijos apie viena is acrobato pluginu
// "iPictureTasksFeaturesNotice"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "Software\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox", "iPictureTasksFeaturesNotice", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }
#endif


// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AdsInReader"

// "bShowAds"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AdsInReader", "bShowAds", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AdobeViewer"

// kad neklaustu licenzijos
// "EULA"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AdobeViewer", "EULA", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// kad maksimizuotu langa
// "MaxApp"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AdobeViewer", "MaxApp", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVAlert] // patikrint, ar susikuria??!!!

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox"

// "iwarnFieldsWillNotBeSaved"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox", "iwarnFieldsWillNotBeSaved", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "iexitWithExternalDocsOpen"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox", "iexitWithExternalDocsOpen", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// kad nepasakotu kazko apie paveikslus
// "iPictureTasksFeaturesNotice"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVAlert\\cCheckbox", "iPictureTasksFeaturesNotice", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral"

// "bToolbarsLocked"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral", "bToolbarsLocked", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bLastExitNormal"=dword:00000001
// "sInDocTabs"=hex:2a,42,6f,6f,6b,6d,61,72,6b,73,2c,53,69,67,6e,61,74,75,72,65,73,2c,4f,70,74,43,6f,6e,74,2c,54,68,75,6d,62,6e,61,69,6c,73,00

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral\cToolbars] // patikrint, ar susikuria??!!!

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c0"

// "sToolBarName"=hex:46,69,6c,65,00 // "File"
   if(SUCCEEDED(retc))
   {
      str_val="File";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c0", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c0", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c11"

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
   if(SUCCEEDED(retc))
   {
      str_val="Navigation";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c11", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c11", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c12"

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
   if(SUCCEEDED(retc))
   {
      str_val="Navigation";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c12", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c12", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c13"

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
   if(SUCCEEDED(retc))
   {
      str_val="Properties";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c13", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c13", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c14"

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
   if(SUCCEEDED(retc))
   {
      str_val="Properties";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c14", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c14", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c15"

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
   if(SUCCEEDED(retc))
   {
      str_val="Commenting";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c15", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c15", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c16"

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
   if(SUCCEEDED(retc))
   {
      str_val="Commenting";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c16", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c16", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c17"

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
   if(SUCCEEDED(retc))
   {
      str_val="JSToolBar";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c17", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000000 // 00000001
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c17", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c18"

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
   if(SUCCEEDED(retc))
   {
      str_val="JSToolBar";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c18", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000000 // 00000001
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c18", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c2"

// "sToolBarName"=hex:42,61,73,69,63,54,6f,6f,6c,73,00 // "BasicTools"
   if(SUCCEEDED(retc))
   {
      str_val="BasicTools";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c2", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c2", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c4"

// "sToolBarName"=hex:56,69,65,77,69,6e,67,00 // "Viewing"
   if(SUCCEEDED(retc))
   {
      str_val="Viewing";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c4", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c4", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c7"

// "sToolBarName"=hex:52,6f,74,61,74,65,00 // "Rotate"
   if(SUCCEEDED(retc))
   {
      str_val="Rotate";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c7", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c7", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c9"

// "sToolBarName"=hex:54,61,73,6b,73,00 // "Tasks"
   if(SUCCEEDED(retc))
   {
      str_val="Tasks";
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c9", "sToolBarName", REG_BINARY, (LPBYTE)str_val, strlen(str_val)+1);
   }

// "bHidden"=dword:00000001 // 00000000
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c9", "bHidden", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// -------------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FeatureLockdown"

// "bShowAdsAllow"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FeatureLockdown", "bShowAdsAllow", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bUpdater"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FeatureLockdown", "bUpdater", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs"

// "bAutoCompleteOnTab"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bAutoCompleteOnTab", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bFocusRect"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bFocusRect", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bInlineAutoComplete"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bInlineAutoComplete", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bRecordNewEntries"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bRecordNewEntries", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bRuntimeHighlight"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bRuntimeHighlight", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bRuntimeShowOverflow"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bRuntimeShowOverflow", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bShowDropDown"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bShowDropDown", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bStoreNumericEntries"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bStoreNumericEntries", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bUserAskedToEnableAutoComplete"=dword:00000001
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\FormsPrefs", "bUserAskedToEnableAutoComplete", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\JSPrefs"

// "bEnableJS"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\JSPrefs", "bEnableJS", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals"

// "bDisplayAboutDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals", "bDisplayAboutDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "iTrustedMode"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals", "iTrustedMode", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bBrowserIntegration"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals", "bBrowserIntegration", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bBrowserCheck"=dword:00000000
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals", "bBrowserCheck", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bSkipDeleteWarnings"=dword:00000001 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=1;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Originals", "bSkipDeleteWarnings", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "sProofingSpace"=hex:55,2e,53,2e,20,57,65,62,20,43,6f,61,74,65,64,20,28,53,57,4f,50,29,20,76,32,00

// ------------------------------------
// HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Updater"

// "bShowAutoUpdateConfDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Updater", "bShowAutoUpdateConfDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "bShowNotifDialog"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Updater", "bShowNotifDialog", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// "iUpdateFrequency"=dword:00000000 // Tado.5c9
   if(SUCCEEDED(retc))
   {
      data_val=0;
      retc = KpRegSetValue(KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\Updater", "iUpdateFrequency", REG_DWORD, (LPBYTE)&data_val, sizeof(data_val));
   }

// KpMsgOut("Po InitAcro70", IDI_ASTERISK, KP_MB_TESTI);

return(retc);
}


