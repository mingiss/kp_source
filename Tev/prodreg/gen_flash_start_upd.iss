;------------------------
; gen_flash_start_upd.iss
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

DefaultDirName = {code:GetAppPathStr}

DirExistsWarning = no

UsePreviousAppDir = no
Uninstallable = no

;OutputDir = Output_flash
;OutputDir = Output_flash_iso
;OutputDir = MTP5E_v1.01.1_atmintukas\Output_flash
OutputDir = Output_flash_iso\Matematika Tau plius-5E

OutputBaseFilename = Pradzia_MTP5E

UsePreviousLanguage = no

PrivilegesRequired = none


[Files]


[Code]

var
   bFinishedInstall: Boolean;


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


function ShouldSkipPage(PageID: Integer): Boolean;
var retw: Boolean;
begin
   retw := True;
   if(PageID = 100) then retw := False;
   Result := retw;
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
begin

   retv := 'Matematika Tau plius-5E';

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
begin

   retv := '';
   retv := retv + GetProdFNameRaw(False);

Result := retv;
end;


function GetProdDirStr(Param: String): String;
begin
Result := GetProdDir;
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
// Result := ExpandConstant('{src}\' + GetProdDir);
   Result := ExpandConstant('{src}');
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


procedure RunExe;
var retv: Integer;
begin
   if(not Exec(GetAppPath + '\' + GetExeFName + '.exe', '', GetAppPath, SW_SHOW, ewNoWait, retv)) then
   begin
      MsgBox('Nepavyko paleisti failo ' + GetExeFName + '.exe', mbError, MB_OK);
   end;
end;


function InitializeSetup: Boolean;
var retv: Integer;
var retw: Boolean;
begin

   bFinishedInstall := False;

      RunExe;

      retw := False; // atsakymas neigiamas, kad nerodytø jokiø tolesniø dialogø, iðkart pasibaigtø

Result := retw;
end;
