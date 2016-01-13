;------------------------
; gen_grp.iss
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

Uninstallable = no

;OutputDir = .

;OutputBaseFilename = MTP5E_v1.01.1_diegimas
OutputBaseFilename = MTP5E_diegimas
;OutputBaseFilename = MTP5E

UsePreviousLanguage = no


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
begin
   Result := True;
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
var retv: String;
begin
   retv := ExpandConstant('{tmp}');
   retv := retv + '\' + GetProdDir;
Result := retv;
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

   retw := True; // False; // atsakymas neigiamas, kad nerodytø jokiø tolesniø dialogø, iðkart pasibaigtø

Result := retw;
end;


procedure DeinitializeSetup;
var retv: Integer;
begin
   if(bFinishedInstall) then
   begin
      if(not Exec(GetAppPath + '\setup.exe', '', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then
      begin
         MsgBox('Nepavyko paleisti failo setup.exe', mbError, MB_OK);
      end;
   end;
end;
