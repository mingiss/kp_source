;------------------------
; gen_chkvol.iss
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


DefaultGroupName = {code:GetProdGroupStr}

OutputDir = MTP5E_v1.01.1_atmintuko_prieziura

UsePreviousLanguage = no


[Files]


[Icons]
Name: "{group}\{code:GetProdFNameStr}"; Filename: "{code:GetLaunchStr}"; IconFilename:"{code:GetAppPathStr}\{code:GetIconFNameStr}"; WorkingDir: "{code:GetAppPathStr}";

Name: "{commondesktop}\{code:GetProdFNameStr}"; Filename: "{code:GetLaunchStr}"; IconFilename:"{code:GetAppPathStr}\{code:GetIconFNameStr}"; WorkingDir: "{code:GetAppPathStr}";


[Code]

var
   bFinishedInstall: Boolean;
   FlashIdPage: TInputQueryWizardPage;


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


function GetProdNameRaw: String;
begin
Result := 'Matematika Tau plius - 5E uþdaviniø sprendyklë';
end;


function GetProdName: String;
begin
Result := GetProdNameRaw + ' ' + GetVer + ' atmintuke';
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
Result := FlashIdPage.Values[0] + ' ' + GetProdFNameRaw(False) + ' atmintuko tikrinimas';
end;


function GetProdFNameStr(Param: String): String;
begin
Result := GetProdFName;
end;


function GetProdDir: String;
var retv: String;
begin

   retv := ExpandConstant('{pf}\TEV\');
   retv := retv + GetProdFNameRaw(False);

Result := retv + ' ' + GetVer + ' atmintuke';
end;


function GetProdDirStr(Param: String): String;
begin
Result := GetProdDir;
end;


function GetProdGroup: String;
var retv: String;
begin

   retv := 'TEV\';
   retv := retv + GetProdFNameRaw(False);

Result := retv + ' ' + GetVer + ' atmintuke';
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
Result := 'chkvol';
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


procedure InitializeWizard;
begin
   FlashIdPage := CreateInputQueryPage(wpInfoBefore,
      'Atmintuko licencijos kodas', '',
      'Áveskite atmintuko licencijos kodà.');
   FlashIdPage.Add('Atmintuko licencijos kodas:', False);
end;
