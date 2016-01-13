;------------------------
; gen_svr.iss
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

;OutputDir = .
;OutputDir = ..\arkim_acrobat\files
;OutputDir = ..\Acrobat_Beb\files
;OutputDir = files
;OutputDir = Output_svr
OutputDir = Output_net

OutputBaseFilename = MTP5E_v1.01.1_serverio_diegimas
;OutputBaseFilename = MTP5E_serveris

AlwaysRestart = yes
UninstallRestartComputer = yes

UsePreviousLanguage = no


[Files]
Source: "files_svr\mat5svr.e_e"; DestDir: "{code:GetAppPathStr}"; DestName: "mat5svr.exe"; Flags: onlyifdoesntexist;
Source: "files_svr\Win2K\srvany.e_e"; DestDir: "{code:GetAppPathStr}\Win2K"; DestName: "srvany.exe"; Flags: onlyifdoesntexist;
Source: "files_svr\WinNT\srvany.e_e"; DestDir: "{code:GetAppPathStr}\WinNT"; DestName: "srvany.exe"; Flags: onlyifdoesntexist;


[Icons]
Name: "{group}\Serverio valdymas"; Filename: "{code:GetAppPathStr}\{code:GetSvrFNameStr}.url"; IconFilename:"{code:GetAppPathStr}\service01.ico"; WorkingDir: "{code:GetAppPathStr}";
Name: "{group}\{code:GetCleanIconNameStr}"; Filename: "{code:GetProdDirStr}\rezultatai\trinam_{code:GetSvrFNameStr}.bat"; IconFilename:"{code:GetAppPathStr}\uninst01.ico"; WorkingDir: "{code:GetProdDirStr}\rezultatai"; Flags: closeonexit;
Name: "{group}\Parinktys"; Filename: "{code:GetAppPathStr}\edini.exe"; Parameters: """{code:GetAppPathStr}\{code:GetSvrFNameStr}.ini"""; IconFilename:"{code:GetAppPathStr}\setup01.ico"; WorkingDir: "{code:GetAppPathStr}";

Name: "{commondesktop}\{code:GetProdFNameStr} serveris"; Filename: "{code:GetAppPathStr}\{code:GetSvrFNameStr}.url"; IconFilename:"{code:GetAppPathStr}\service01.ico"; WorkingDir: "{code:GetAppPathStr}";


[Code]

var
   bFinishedInstall: Boolean;
   AccLetAsked: Boolean;
   UseAccLet: Boolean;


function KpRegSoftWriteDWordValue(const SubKeyName, ValueName: String; const Data: Cardinal; const Message: String): Boolean;
var retw: Boolean;
begin

   retw := True;

   if(not RegWriteDWordValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, Data)) then
   begin
         MsgBox(Message, mbCriticalError, MB_OK);
         retw := False;
   end;

Result := retw;
end;


function KpRegSoftWriteStringValue(const SubKeyName, ValueName, Data, Message: String): Boolean;
var retw: Boolean;
begin

   retw := True;

   if(not RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\' + SubKeyName, ValueName, Data)) then
   begin
         MsgBox(Message, mbCriticalError, MB_OK);
         retw := False;
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


function GetProdNameRaw: String;
begin
Result := 'Matematika Tau plius - 5E uþdaviniø sprendyklë';
end;


function GetProdName: String;
begin
Result := GetProdNameRaw + ' serveris';
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

   if(not AccLetAsked) then
   begin
      AccLetAsked := True;
      UseAccLet := (MsgBox('Lietuviðkas raides su diakritiniais þenklais (nosinëmis, paukðèiukais ir kt.) failø varduose galima naudoti tik tuo atveju, jei Jûsø operacinëje sistemoje Windows nustatytos Lietuvos regiono parinktys ir Jûs nesiruoðiate jø keisti.'+Chr(10)+Chr(10)+'Ar norite tokias raides naudoti failø varduose?',
         mbConfirmation, MB_YESNO) = IDYES );
   end;

   if(UseAccLet and UseAccLetLoc) then retv := 'Matematika Tau plius-5E'
   else retv := 'Matematika Tau plius-5E';

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
var retv, prod_fname: String;
begin
   prod_fname := GetProdFNameRaw(True);

   if(UseAccLet) then retv := GetProdFNameRaw(UseAccLet)
   else retv := GetProdFNameRaw(UseAccLet);

Result := retv;
end;


function GetProdFNameStr(Param: String): String;
begin
Result := GetProdFName;
end;


function GetProdDir: String;
var retv: String;
var dir_name: String;
var prod_fname: String;
begin

   prod_fname := GetProdFNameRaw(True);

   retv := ExpandConstant('{pf}\');

   if(UseAccLet) then retv := retv + 'TEV\'
   else retv := retv + 'TEV\';

   if(UseAccLet) then retv := retv + GetProdFNameRaw(UseAccLet)
   else retv := retv + GetProdFNameRaw(UseAccLet);

// Padubliuoti su visais buvusiais ProdName – kai diegiama ant virðaus
   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\' + GetProdName + '_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: App Path', dir_name)) then retv := dir_name;

   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\Matematika Tau plius - 5E uþdaviniø sprendyklë_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: App Path', dir_name)) then retv := dir_name;

Result := retv + ' serveris';
end;


function GetProdDirStr(Param: String): String;
begin
Result := GetProdDir;
end;


function GetProdGroup: String;
var retv: String;
var group_name: String;
var prod_fname: String;
begin

   prod_fname := GetProdFNameRaw(True);

   if(UseAccLet) then retv := 'TEV\'
   else retv := 'TEV\';

   if(UseAccLet) then retv := retv + GetProdFNameRaw(UseAccLet)
   else retv := retv + GetProdFNameRaw(UseAccLet);

// Padubliuoti ir visiems buvusiems skirtingiems ProdName – kai diegiama ant virðaus
   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\' + GetProdName + '_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then retv := group_name;

   if(KpRegSoftQueryStringValue('Microsoft\Windows\CurrentVersion\Uninstall\Matematika Tau plius - 5E uþdaviniø sprendyklë_is1', // èia ávesti senàjá ProdName tekstà
      'Inno Setup: Icon Group', group_name)) then retv := group_name;

Result := retv + ' serveris';
end;


function GetProdGroupStr(Param: String): String;
begin
Result := GetProdGroup;
end;


function GetCleanIconNameStr(Param: String): String;
var retv, prod_fname: String;
begin
   prod_fname := GetProdFNameRaw;

   if(UseAccLet) then retv := 'Senø rezultatø valymas'
   else retv := 'Senu rezultatu valymas';

Result := retv;
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


function GetSvrFName: String;
begin
Result := 'mat5svr';
end;


function GetSvrFNameStr(Param: String): String;
begin
Result := GetSvrFName;
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
Result := GetAppPath + '\' + GetExeFName + '.exe';
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
   AccLetAsked := False;
   UseAccLet := True;

   retw := True;

   if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'SrvInstalled', 0, 'Diegimui reikalingos administratoriaus teisës');

Result := retw;
end;


procedure DeinitializeSetup;
var retv: Integer;
var retw: Boolean;
begin
   retw := True;

   if(bFinishedInstall) then
   begin

      if(not Exec(GetAppPath + '\kpstlsvi.exe', '0', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then
         MsgBox('Nepavyko paleisti failo kpstlsvi.exe', mbError, MB_OK);

      RestartReplace(GetAppPath + '\' + GetSvrFName + '.e_e', GetAppPath + '\' + GetSvrFName + '.exe');
      RestartReplace(GetAppPath + '\Win2K\srvany.e_e', GetAppPath + '\Win2K\srvany.exe');
      RestartReplace(GetAppPath + '\WinNT\srvany.e_e', GetAppPath + '\WinNT\srvany.exe');

      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvProdName', GetProdName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvVer', GetVer, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvProjID', GetProjID, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvExeFName', GetExeFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvProdFName', GetProdFName, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvProdGroup', ExpandConstant('{group}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvProdDir', GetAppPath, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvLaunch', GetLaunch, 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteStringValue('TEV\' + GetProdVer, 'SrvUninst', ExpandConstant('{uninstallexe}'), 'Diegimui reikalingos administratoriaus teisës');
      if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'SrvInstalled', GetUpdNum, 'Diegimui reikalingos administratoriaus teisës');
   end;
end;


function InitializeUninstall: Boolean;
var retv: Integer;
var retw: Boolean;
begin

   retw := True;

   if(retw) then retw := KpRegSoftWriteDWordValue('TEV\' + GetProdVer, 'SrvInstalled', 0, 'Panaikinimui reikalingos administratoriaus teisës');

   if(retw) then
      if(not Exec(GetAppPath + '\kpstlsvu.exe', '', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then
         MsgBox('Nepavyko paleisti failo kpstlsvu.exe', mbError, MB_OK);

   RestartReplace(GetAppPath + '\' + GetSvrFName + '.exe', '');
   RestartReplace(GetAppPath + '\' + GetSvrFName + '.url', '');
   RestartReplace(GetAppPath + '\Win2K\srvany.exe', '');
   RestartReplace(GetAppPath + '\WinNT\srvany.exe', '');
   RestartReplace(GetAppPath + '\Win2K', '');
   RestartReplace(GetAppPath + '\WinNT', '');
   RestartReplace(GetAppPath, '');

Result := retw;
end;
