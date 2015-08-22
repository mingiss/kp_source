echo [Project]> %1.dev
echo FileName=%1.dev>> %1.dev
echo Name=%1>> %1.dev
echo UnitCount=123>> %1.dev
echo Type=2 >> %1.dev
echo Ver=1 >> %1.dev
echo ObjFiles=>> %1.dev
echo Includes=.;..\kpt;..\kps;..\kphp11;..\tev;..\tev\xml;..\tev\rtf>> %1.dev
echo Libs=>> %1.dev
echo PrivateResource=%1_private.rc>> %1.dev
echo ResourceIncludes=..\..\include;..\..>> %1.dev
echo MakeIncludes=>> %1.dev
echo Compiler=>> %1.dev
echo CppCompiler=>> %1.dev
echo Linker=>> %1.dev
echo IsCpp=1 >> %1.dev
echo Icon=>> %1.dev
echo ExeOutput=>> %1.dev
echo ObjectOutput=>> %1.dev
echo OverrideOutput=0 >> %1.dev
echo OverrideOutputName=%1.a>> %1.dev
echo HostApplication=>> %1.dev
echo Folders=>> %1.dev
echo CommandLine=>> %1.dev
echo UseCustomMakefile=0 >> %1.dev
echo CustomMakefile=>> %1.dev
echo IncludeVersionInfo=0 >> %1.dev
echo SupportXPThemes=0 >> %1.dev
echo CompilerSet=0 >> %1.dev
echo CompilerSettings=0000000000000000000000 >> %1.dev

copy tgt2dev.top tgt2dev.pl

echo {                                                 >> tgt2dev.pl
echo    @src=split /.cpp/, $_;                         >> tgt2dev.pl
echo    @allsrc=split /\*.cpp/, $_;                    >> tgt2dev.pl
echo    if(defined($src[1]) and not defined($allsrc[1]))  >> tgt2dev.pl
echo    {                                              >> tgt2dev.pl
echo       print "[Unit",$ii,"]\n";                    >> tgt2dev.pl
echo       $ii=$ii+1;                                  >> tgt2dev.pl
echo       print "FileName=";                          >> tgt2dev.pl
echo       print $_;                                   >> tgt2dev.pl
echo       print "CompileCpp=1\n";                     >> tgt2dev.pl
echo       print "Folder=%1\n";                        >> tgt2dev.pl
echo       print "Compile=1\n";                        >> tgt2dev.pl
echo       print "Link=";                              >> tgt2dev.pl
echo       if(defined($rc[1])){ print "0"; }           >> tgt2dev.pl
echo       else{ print "1"; }                          >> tgt2dev.pl
echo       print "\n";                                 >> tgt2dev.pl
echo       print "Priority=1000\n";                    >> tgt2dev.pl
echo       print "OverrideBuildCmd=0\n";               >> tgt2dev.pl
echo       print "BuildCmd=\n\n";                      >> tgt2dev.pl
echo    }                                              >> tgt2dev.pl
echo }                                                 >> tgt2dev.pl


perl tgt2dev.pl < %1.tgt >> %1.dev


echo [VersionInfo]>> %1.dev
echo Major=0 >> %1.dev
echo Minor=1 >> %1.dev
echo Release=1 >> %1.dev
echo Build=1 >> %1.dev
echo LanguageID=1033 >> %1.dev
echo CharsetID=1252 >> %1.dev
echo CompanyName=>> %1.dev
echo FileVersion=>> %1.dev
echo FileDescription=Developed using the Dev-C++ IDE>> %1.dev
echo InternalName=>> %1.dev
echo LegalCopyright=>> %1.dev
echo LegalTrademarks=>> %1.dev
echo OriginalFilename=>> %1.dev
echo ProductName=>> %1.dev
echo ProductVersion=>> %1.dev
echo AutoIncBuildNr=0 >> %1.dev
