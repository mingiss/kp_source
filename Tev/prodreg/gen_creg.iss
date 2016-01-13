;------------------------
; gen_creg.iss
; Installation script
; MTP5E
; 'Matematika Tau plius - 5E uþdaviniø sprendyklë'
;


[Setup]
AppPublisher = TEV
AppPublisherURL = http://www.tev.lt/
AppVersion = {code:GetVerStr}
VersionInfoCompany = TEV

VersionInfoProductName = {code:GetProdNameStr}
VersionInfoProductTextVersion = {code:GetVerNameStr}

AppName = {code:GetProdNameStr}
AppVerName = {code:GetVerNameStr}

;ProdVer = {code:GetProdVerStr}

DefaultDirName = {code:GetProdDirStr}

UninstallDisplayIcon = {code:GetAppPathStr}\{code:GetIconFNameStr}

DefaultGroupName = {code:GetProdGroupStr}

;OutputDir = Output\setup
;OutputDir = .

;OutputBaseFilename = MTP5E_v1.01.1_diegimas
OutputBaseFilename = MTP5E_diegimas
;OutputBaseFilename = MTP5E

UsePreviousLanguage = no

AlwaysUsePersonalGroup = yes
PrivilegesRequired = none

InfoBeforeFile = infobefore.rtf


[Files]


[Icons]
Name: "{group}\{code:GetProdFNameStr}"; Filename: "{code:GetLaunchStr}"; IconFilename:"{code:GetAppPathStr}\{code:GetIconFNameStr}"; WorkingDir: "{code:GetAppPathStr}";

Name: "{userdesktop}\{code:GetProdFNameStr}"; Filename: "{code:GetLaunchStr}"; IconFilename:"{code:GetAppPathStr}\{code:GetIconFNameStr}"; WorkingDir: "{code:GetAppPathStr}";


[Code]

var
   bFinishedInstall: Boolean;


function KpRegSoftWriteDWordValue(const SubKeyName, ValueName: String; const Data: Cardinal; const Message: String): Boolean;
var retw: Boolean;
begin

   retw := True;

   if(not RegWriteDWordValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, Data)) then
   begin
         RegWriteDWordValue(HKEY_CURRENT_USER, 'Software\' + SubKeyName, ValueName, Data)
   end;

Result := retw;
end;


function KpRegSoftWriteStringValue(const SubKeyName, ValueName, Data, Message: String): Boolean;
var retw: Boolean;
begin

   retw := True;

   if(not RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, Data)) then
   begin
         RegWriteStringValue(HKEY_CURRENT_USER, 'Software\' + SubKeyName, ValueName, Data)
   end;

Result := retw;
end;


function KpRegSoftQueryDWordValue(const SubKeyName, ValueName: String; var ResVal: dword): Boolean;
var found: Boolean;
begin

   found := False;

   if(not found) then found := RegQueryDWordValue(HKEY_CURRENT_USER, 'Software\' + SubKeyName, ValueName, ResVal);
   if(not found) then found := RegQueryDWordValue(HKEY_CURRENT_USER, 'Software\Wow6432Node\' + SubKeyName, ValueName, ResVal);
   if(not found) then found := RegQueryDWordValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, ResVal);
   if(not found) then found := RegQueryDWordValue(HKEY_LOCAL_MACHINE, 'Software\Wow6432Node\' + SubKeyName, ValueName, ResVal);

Result := found;
end;


function KpRegSoftQueryStringValue(const SubKeyName, ValueName: String; var ResultStr: String): Boolean;
var found: Boolean;
begin

   found := False;

   if(not found) then found := RegQueryStringValue(HKEY_CURRENT_USER, 'Software\' + SubKeyName, ValueName, ResultStr);
   if(not found) then found := RegQueryStringValue(HKEY_CURRENT_USER, 'Software\Wow6432Node\' + SubKeyName, ValueName, ResultStr);
   if(not found) then found := RegQueryStringValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, ResultStr);
   if(not found) then found := RegQueryStringValue(HKEY_LOCAL_MACHINE, 'Software\Wow6432Node\' + SubKeyName, ValueName, ResultStr);

Result := found;
end;


function GetProdVer: String;
begin
Result := '1359';
end;


function GetProdVerStr(Param: String): String;
begin
Result := GetProdVer;
end;


function GetVer: String;
begin
Result := 'v1.01.1';
end;


function GetVerStr(Param: String): String;
begin
Result := GetVer;
end;


function GetFirstVer: String;
begin
Result := 'v1.01';
end;


function ShouldSkipPage(PageID: Integer): Boolean;
var retv: Boolean;
var launch: String;
begin
   retv := False;
   if(PageID = wpInfoBefore) then
   begin
      if(RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\AcroRd32.exe', '', launch)) then
         retv := True;
   end;
Result := retv;
end;


function GetProdNameRaw: String;
begin
Result := 'Matematika Tau plius - 5E uþdaviniø sprendyklë';
end;


function GetProdName: String;
begin
Result := GetProdNameRaw;
end;


function GetProdNameStr(Param: String): String;
begin
Result := GetProdName;
end;


function GetFirstVerName: String;
begin
Result := GetProdNameRaw + ' ' + GetFirstVer;
end;


function GetVerName: String;
begin
Result := GetProdName + ' ' + GetVer;
end;


function GetVerNameStr(Param: String): String;
begin
Result := GetVerName;
end;


function GetProdFNameRaw(UseAccLetLoc: Boolean): String;
var retv: String;
var group_name: String;
begin

   retv := 'Matematika Tau plius-5E';

// Padubliuoti ir visiems buvusiems skirtingiems ProdName, ProdDir ir ProdGroup – kai diegiama ant virðaus
   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\' + GetProdName + '_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then
   begin
      if(group_name = 'TEV\Matematika Tau plius-5E') then // èia senasis ProdGroup (su paukðèiukais)
         retv := 'Matematika Tau plius-5E' // èia senasis ProdFNameRaw (su paukðèiukais)
      else
         retv := 'Matematika Tau plius-5E'; // èia senasis ProdFNameRaw (be paukðèiukø)
   end;

   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\Matematika Tau plius - 5E uþdaviniø sprendyklë_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then
   begin
      if(group_name = 'TEV\Matematika Tau plius-5E') then // èia senasis ProdGroup (su paukðèiukais)
         retv := 'Matematika Tau plius-5E' // èia senasis ProdFNameRaw (su paukðèiukais)
      else
         retv := 'Matematika Tau plius-5E'; // èia senasis ProdFNameRaw (be paukðèiukø)
   end;

Result := retv;
end;


function GetProdFName: String;
begin
Result := GetProdFNameRaw(False);
end;


function GetProdFNameStr(Param: String): String;
begin
Result := GetProdFName;
end;


function GetProdDir: String;
var retv: String;
var dir_name: String;
begin

   retv := ExpandConstant('{userappdata}\TEV\');
   retv := retv + GetProdFNameRaw(False);

// Padubliuoti su visais buvusiais ProdName – kai diegiama ant virðaus
   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\' + GetProdName + '_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: App Path', dir_name)) then retv := dir_name;

   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\Matematika Tau plius - 5E uþdaviniø sprendyklë_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: App Path', dir_name)) then retv := dir_name;

Result := retv;
end;


function GetProdDirStr(Param: String): String;
begin
Result := GetProdDir;
end;


function GetProdGroup: String;
var retv: String;
var group_name: String;
begin

   retv := 'TEV\';
   retv := retv + GetProdFNameRaw(False);

// Padubliuoti ir visiems buvusiems skirtingiems ProdName – kai diegiama ant virðaus
   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\' + GetProdName + '_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then retv := group_name;

   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\Matematika Tau plius - 5E uþdaviniø sprendyklë_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then retv := group_name;

Result := retv;
end;


function GetProdGroupStr(Param: String): String;
begin
Result := GetProdGroup;
end;


function GetProjID: String;
begin
Result := 'MTP5E';
end;


function GetProjIDStr(Param: String): String;
begin
Result := GetProjID;
end;


function GetPdfFName: String;
begin
Result := 'titulinis.pdf';
end;


function GetExeFName: String;
begin
Result := 'MTP5E';
end;


function GetExeFNameStr(Param: String): String;
begin
Result := GetExeFName;
end;


function GetIconFNameStr(Param: String): String;
begin
Result := 'MTP5.ico';
end;


function GetUpdNum: Integer;
begin
Result := 1;
end;


function GetAppPath: String;
begin
Result := ExpandConstant('{app}');
end;


function GetAppPathStr(Param: String): String;
begin
Result := GetAppPath;
end;


function GetLaunch: String;
begin
Result := GetAppPath + '\' + GetPdfFName;
end;


function GetLaunchStr(Param: String): String;
begin
Result := GetLaunch;
end;


procedure CurStepChanged(CurStep: TSetupStep);
begin
   if(CurStep = ssPostInstall) then
      bFinishedInstall := True;
end;


function InitializeSetup: Boolean;
var retw: Boolean;
begin
   bFinishedInstall := False;

   retw := True;

   if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'Installed', 0, 'Diegimui reikalingos administratoriaus teisës');

Result := retw;
end;


procedure DeinitializeSetup;
var retv: Integer;
var retw: Boolean;
var launch: String;
begin
   retw := True;

   if(bFinishedInstall) then
   begin

      if(not Exec(GetAppPath + '\Launcher.exe', 'reg', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then
         MsgBox('Nepavyko paleisti failo Launcher.exe', mbError, MB_OK);

      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdName', GetProdName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Ver', GetVer, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProjID', GetProjID, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ExeFName', GetExeFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdFName', GetProdFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdGroup', ExpandConstant('{group}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdDir', GetAppPath, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Launch', GetLaunch, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Uninst', ExpandConstant('{uninstallexe}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'Installed', GetUpdNum, 'Diegimui reikalingos administratoriaus teisës');

      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cAlwaysTrustedForJavaScript', 't20', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cCrossdomain', 't15', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cDataInjection', 't19', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cExternalStream', 't16', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cFileAttachment', 't23', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cJavaScript', 't17', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cJavaScriptURL', 't21', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cMultiMedia', 't22', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cScriptInjection', 't18', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cSilentPrint', 't13', GetAppPath + '\' + GetPdfFName);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Adobe\Acrobat Reader\9.0\TrustManager\cTrustedFolders\cWeblink', 't14', GetAppPath + '\' + GetPdfFName);

      RegWriteStringValue(HKEY_CLASSES_ROOT, '.tev', '', 'tev_auto_file');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Classes\.tev', '', 'tev_auto_file');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.tev\OpenWithList', 'a', 'AcroRd32.exe');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.tev\OpenWithList', 'MRUList', 'a');
      RegWriteDWordValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.tev\OpenWithProgids', 'tev_auto_file', 0);
      RegWriteDWordValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\ApplicationAssociationToasts', 'Applications\AcroRd32.exe_.tev', 0);
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.tev\UserChoice', 'Hash', 'XpC8g74bfEk=');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.tev\UserChoice', 'ProgId', 'Applications\AcroRd32.exe');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\Roaming\OpenWith\FileExts\.tev\UserChoice', 'Hash', '01gD+R2twrQ=');
      RegWriteStringValue(HKEY_CURRENT_USER, 'Software\Microsoft\Windows\Roaming\OpenWith\FileExts\.tev\UserChoice', 'ProgId', 'Applications\AcroRd32.exe');

      if(RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\AcroRd32.exe', '', launch)) then
         RegWriteStringValue(HKEY_CLASSES_ROOT, 'tev_auto_file\Shell\Open\Command', '', '"' + launch + '" "%1"');

      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdName', GetProdName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Ver', GetVer, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProjID', GetProjID, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ExeFName', GetExeFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdFName', GetProdFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdGroup', ExpandConstant('{group}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'ProdDir', GetAppPath, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Launch', GetLaunch, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'Uninst', ExpandConstant('{uninstallexe}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'Installed', GetUpdNum, 'Diegimui reikalingos administratoriaus teisës');

   end;
end;


function InitializeUninstall: Boolean;
var retv: Integer;
var retw: Boolean;
begin

   retw := True;

   if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'Installed', 0, 'Panaikinimui reikalingos administratoriaus teisës');

// if(retw) then
      if(not Exec(GetAppPath + '\Launcher.exe', 'unreg', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then
         MsgBox('Nepavyko paleisti failo Launcher.exe', mbError, MB_OK);

Result := retw;
end;
