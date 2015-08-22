Proj = kpsttrg_pl

BaseDisk = F:
CommonDir = $(BaseDisk)/source
BaseDir = $(BaseDisk)/kp/source
TevDir = $(BaseDir)/Tev
ProdDir = $(BaseDir)/kpstart
ObjDir = $(ProdDir)/$(Proj)_Obj

#ProgFiles = C:/Program Files (x86)
#ProgFiles = $(ProgramFiles)
ProgFiles = C:/PROGRA~1
#ProgFiles = C:/PROGRA~2

CPP = "$(ProgFiles)/CodeBlocks/MinGW/bin/mingw32-g++.exe"
CC = "$(ProgFiles)/CodeBlocks/MinGW/bin/mingw32-gcc.exe"
AR = "$(ProgFiles)/CodeBlocks/MinGW/bin/ar.exe"

CXXINCS = \
   -I$(CommonDir)/common \
   -I$(CommonDir)/kpt \
   -I$(CommonDir)/xml \
   -I$(BaseDir)/common \
   -I$(BaseDir)/kpt \
   -I$(BaseDir)/kps \
   -I$(BaseDir)/kphp11 \
   -I$(TevDir)/xml \
   -I$(TevDir)/rtf \
   -I$(TevDir)/tex \
   -I$(TevDir)/xml \
   -I$(TevDir)/xml/tux_gecko/include \
   -I$(TevDir)/iBook \
   -I$(TevDir)/lzdsh \
   -I$(ProdDir)

CXXFLAGS = $(CXXINCS) -DEnvir=15 -DKPSTEDI_MODE=6 -DMsgLang=98 -DBUFFERSIZE=4096 -DKpstregSilent
CPPFLAGS = $(CXXFLAGS) 
CCFLAGS = $(CXXFLAGS) 

OBJ = \
   $(ObjDir)/Tvrtf.o \
   $(ObjDir)/Tvrtfo.o \
   $(ObjDir)/Tvrtft.o \
   $(ObjDir)/Tvmain.o \
   $(ObjDir)/gen.o \
   $(ObjDir)/Htmt.o \
   $(ObjDir)/Tvxmlc.o \
   $(ObjDir)/Tvxmlcm.o \
   $(ObjDir)/XMLB.o \
   $(ObjDir)/Xml8.o \
   $(ObjDir)/Xmlf.o \
   $(ObjDir)/Xmlh.o \
   $(ObjDir)/Xmli.o \
   $(ObjDir)/Xmln.o \
   $(ObjDir)/Xmlnl.o \
   $(ObjDir)/Xmlnr.o \
   $(ObjDir)/Xmlnh.o \
   $(ObjDir)/Xmlp.o \
   $(ObjDir)/Xmlt.o \
   $(ObjDir)/Xmlg.o \
   $(ObjDir)/Xmlu.o \
   $(ObjDir)/tvxml.o \
   $(ObjDir)/tvxmle.o \
   $(ObjDir)/tvxmlel0.o \
   $(ObjDir)/tvxmlelc.o \
   $(ObjDir)/tvxmlevc.o \
   $(ObjDir)/tvxmls.o \
   $(ObjDir)/Tvxmltt.o \
   $(ObjDir)/xmlis.o \
   $(ObjDir)/xmlo1.o \
   $(ObjDir)/xmlt0.o \
   $(ObjDir)/xmlsty.o \
   $(ObjDir)/xmlsty0.o \
   $(ObjDir)/xmlsty2.o \
   $(ObjDir)/iBsh0.o \
   $(ObjDir)/iBshl0.o \
   $(ObjDir)/iBsht0.o \
   $(ObjDir)/KpGecko0.o \
   $(ObjDir)/Diskid32.o \
   $(ObjDir)/KPSOCK.o \
   $(ObjDir)/KpPubDlg.o \
   $(ObjDir)/Kpcapp.o \
   $(ObjDir)/Kpcons.o \
   $(ObjDir)/Kpctype.o \
   $(ObjDir)/Kperr.o \
   $(ObjDir)/Kperrl_XFS.o \
   $(ObjDir)/Kpsort.o \
   $(ObjDir)/Kpstdio.o \
   $(ObjDir)/Kpstdlib.o \
   $(ObjDir)/Kpstring.o \
   $(ObjDir)/KpFileSys.o \
   $(ObjDir)/Kpwindow.o \
   $(ObjDir)/kpcurdat.o \
   $(ObjDir)/kptree.o \
   $(ObjDir)/Kphp1152.o \
   $(ObjDir)/Kphp11d.o \
   $(ObjDir)/Kphp11m.o \
   $(ObjDir)/Kphp11mz.o \
   $(ObjDir)/Kphp11p.o \
   $(ObjDir)/Kphp11rc.o \
   $(ObjDir)/Kphp11ry.o \
   $(ObjDir)/Kphp11s.o \
   $(ObjDir)/Kphp11t.o \
   $(ObjDir)/Kphp11tt.o \
   $(ObjDir)/Kphp11w.o \
   $(ObjDir)/Kphp11y.o \
   $(ObjDir)/Kphp11yd.o \
   $(ObjDir)/Kpstap.o \
   $(ObjDir)/Kpstapa.o \
   $(ObjDir)/Kpstapd.o \
   $(ObjDir)/Kpstapl.o \
   $(ObjDir)/Kpstapr.o \
   $(ObjDir)/Kpstapu.o \
   $(ObjDir)/Kpstapg.o \
   $(ObjDir)/kpstapg0.o \
   $(ObjDir)/Kpstaps.o \
   $(ObjDir)/kpstaf.o \
   $(ObjDir)/kpstape.o \
   $(ObjDir)/kpstart_ini.o \
   $(ObjDir)/kpsttrg.o \
   $(ObjDir)/KPTHP1.o \
   $(ObjDir)/Kptt2.o \
   $(ObjDir)/Kpttuc.o \
   $(ObjDir)/Kpttucc.o \
   $(ObjDir)/Kpttucf.o \
   $(ObjDir)/Kpttul.o \
   $(ObjDir)/KPFONTS.o \
   $(ObjDir)/kpcolors.o \
   $(ObjDir)/cdecode.o \
   $(ObjDir)/cencode.o

LIB = $(ProdDir)/lib$(Proj).a


# .SUFFIXES: .cpp

# default: dep $(OUT)


# $(LIB): $(OBJ)
#	$(AR) q $(LIB) $(OBJ)

$(LIB): $(OBJ)
	$(AR) rcs $(LIB) $(OBJ)


$(ObjDir)/Tvrtf.o: $(TevDir)/RTF/Tvrtf.cpp
	$(CPP) -c $(TevDir)/RTF/Tvrtf.cpp -o $(ObjDir)/Tvrtf.o $(CPPFLAGS)

$(ObjDir)/Tvrtfo.o: $(TevDir)/RTF/Tvrtfo.cpp
	$(CPP) -c $(TevDir)/RTF/Tvrtfo.cpp -o $(ObjDir)/Tvrtfo.o $(CPPFLAGS)

$(ObjDir)/Tvrtft.o: $(TevDir)/RTF/Tvrtft.cpp
	$(CPP) -c $(TevDir)/RTF/Tvrtft.cpp -o $(ObjDir)/Tvrtft.o $(CPPFLAGS)

$(ObjDir)/Tvmain.o: $(TevDir)/Tvmain.cpp
	$(CPP) -c $(TevDir)/Tvmain.cpp -o $(ObjDir)/Tvmain.o $(CPPFLAGS)

$(ObjDir)/gen.o: $(TevDir)/prodreg/gen.cpp
	$(CPP) -c $(TevDir)/prodreg/gen.cpp -o $(ObjDir)/gen.o $(CPPFLAGS)

$(ObjDir)/Htmt.o: $(TevDir)/xml/Htmt.cpp
	$(CPP) -c $(TevDir)/xml/Htmt.cpp -o $(ObjDir)/Htmt.o $(CPPFLAGS)

$(ObjDir)/Tvxmlc.o: $(TevDir)/xml/Tvxmlc.cpp
	$(CPP) -c $(TevDir)/xml/Tvxmlc.cpp -o $(ObjDir)/Tvxmlc.o $(CPPFLAGS)

$(ObjDir)/Tvxmlcm.o: $(TevDir)/xml/Tvxmlcm.cpp
	$(CPP) -c $(TevDir)/xml/Tvxmlcm.cpp -o $(ObjDir)/Tvxmlcm.o $(CPPFLAGS)

$(ObjDir)/XMLB.o: $(TevDir)/xml/XMLB.cpp
	$(CPP) -c $(TevDir)/xml/XMLB.cpp -o $(ObjDir)/XMLB.o $(CPPFLAGS)

$(ObjDir)/Xml8.o: $(TevDir)/xml/Xml8.cpp
	$(CPP) -c $(TevDir)/xml/Xml8.cpp -o $(ObjDir)/Xml8.o $(CPPFLAGS)

$(ObjDir)/Xmlf.o: $(TevDir)/xml/Xmlf.cpp
	$(CPP) -c $(TevDir)/xml/Xmlf.cpp -o $(ObjDir)/Xmlf.o $(CPPFLAGS)

$(ObjDir)/Xmlh.o: $(TevDir)/xml/Xmlh.cpp
	$(CPP) -c $(TevDir)/xml/Xmlh.cpp -o $(ObjDir)/Xmlh.o $(CPPFLAGS)

$(ObjDir)/Xmli.o: $(TevDir)/xml/Xmli.cpp
	$(CPP) -c $(TevDir)/xml/Xmli.cpp -o $(ObjDir)/Xmli.o $(CPPFLAGS)

$(ObjDir)/Xmln.o: $(TevDir)/xml/Xmln.cpp
	$(CPP) -c $(TevDir)/xml/Xmln.cpp -o $(ObjDir)/Xmln.o $(CPPFLAGS)

$(ObjDir)/Xmlnl.o: $(TevDir)/xml/Xmlnl.cpp
	$(CPP) -c $(TevDir)/xml/Xmlnl.cpp -o $(ObjDir)/Xmlnl.o $(CPPFLAGS)

$(ObjDir)/Xmlnr.o: $(TevDir)/xml/Xmlnr.cpp
	$(CPP) -c $(TevDir)/xml/Xmlnr.cpp -o $(ObjDir)/Xmlnr.o $(CPPFLAGS)

$(ObjDir)/Xmlnh.o: $(TevDir)/xml/Xmlnh.cpp
	$(CPP) -c $(TevDir)/xml/Xmlnh.cpp -o $(ObjDir)/Xmlnh.o $(CPPFLAGS)

$(ObjDir)/Xmlp.o: $(TevDir)/xml/Xmlp.cpp
	$(CPP) -c $(TevDir)/xml/Xmlp.cpp -o $(ObjDir)/Xmlp.o $(CPPFLAGS)

$(ObjDir)/Xmlt.o: $(TevDir)/xml/Xmlt.cpp
	$(CPP) -c $(TevDir)/xml/Xmlt.cpp -o $(ObjDir)/Xmlt.o $(CPPFLAGS)

$(ObjDir)/Xmlg.o: $(TevDir)/xml/Xmlg.cpp
	$(CPP) -c $(TevDir)/xml/Xmlg.cpp -o $(ObjDir)/Xmlg.o $(CPPFLAGS)

$(ObjDir)/Xmlu.o: $(TevDir)/xml/Xmlu.cpp
	$(CPP) -c $(TevDir)/xml/Xmlu.cpp -o $(ObjDir)/Xmlu.o $(CPPFLAGS)

$(ObjDir)/tvxml.o: $(TevDir)/xml/tvxml.cpp
	$(CPP) -c $(TevDir)/xml/tvxml.cpp -o $(ObjDir)/tvxml.o $(CPPFLAGS)

$(ObjDir)/tvxmle.o: $(TevDir)/xml/tvxmle.cpp
	$(CPP) -c $(TevDir)/xml/tvxmle.cpp -o $(ObjDir)/tvxmle.o $(CPPFLAGS)

$(ObjDir)/tvxmlel0.o: $(TevDir)/xml/tvxmlel0.cpp
	$(CPP) -c $(TevDir)/xml/tvxmlel0.cpp -o $(ObjDir)/tvxmlel0.o $(CPPFLAGS)

$(ObjDir)/tvxmlelc.o: $(TevDir)/xml/tvxmlelc.cpp
	$(CPP) -c $(TevDir)/xml/tvxmlelc.cpp -o $(ObjDir)/tvxmlelc.o $(CPPFLAGS)

$(ObjDir)/tvxmlevc.o: $(TevDir)/xml/tvxmlevc.cpp
	$(CPP) -c $(TevDir)/xml/tvxmlevc.cpp -o $(ObjDir)/tvxmlevc.o $(CPPFLAGS)

$(ObjDir)/tvxmls.o: $(TevDir)/xml/tvxmls.cpp
	$(CPP) -c $(TevDir)/xml/tvxmls.cpp -o $(ObjDir)/tvxmls.o $(CPPFLAGS)

$(ObjDir)/Tvxmltt.o: $(CommonDir)/xml/Tvxmltt.cpp
	$(CPP) -c $(CommonDir)/xml/Tvxmltt.cpp -o $(ObjDir)/Tvxmltt.o $(CPPFLAGS)

$(ObjDir)/xmlis.o: $(TevDir)/xml/xmlis.cpp
	$(CPP) -c $(TevDir)/xml/xmlis.cpp -o $(ObjDir)/xmlis.o $(CPPFLAGS)

$(ObjDir)/xmlo1.o: $(TevDir)/xml/xmlo1.cpp
	$(CPP) -c $(TevDir)/xml/xmlo1.cpp -o $(ObjDir)/xmlo1.o $(CPPFLAGS)

$(ObjDir)/xmlt0.o: $(TevDir)/xml/xmlt0.cpp
	$(CPP) -c $(TevDir)/xml/xmlt0.cpp -o $(ObjDir)/xmlt0.o $(CPPFLAGS)
 
$(ObjDir)/xmlsty.o: $(TevDir)/xml/xmlsty.cpp
	$(CPP) -c $(TevDir)/xml/xmlsty.cpp -o $(ObjDir)/xmlsty.o $(CPPFLAGS)

$(ObjDir)/xmlsty0.o: $(TevDir)/xml/xmlsty0.cpp
	$(CPP) -c $(TevDir)/xml/xmlsty0.cpp -o $(ObjDir)/xmlsty0.o $(CPPFLAGS)

$(ObjDir)/xmlsty2.o: $(TevDir)/xml/xmlsty2.cpp
	$(CPP) -c $(TevDir)/xml/xmlsty2.cpp -o $(ObjDir)/xmlsty2.o $(CPPFLAGS)

$(ObjDir)/iBsh0.o: $(TevDir)/iBook/iBsh0.cpp
	$(CPP) -c $(TevDir)/iBook/iBsh0.cpp -o $(ObjDir)/iBsh0.o $(CPPFLAGS)

$(ObjDir)/iBshl0.o: $(TevDir)/iBook/iBshl0.cpp
	$(CPP) -c $(TevDir)/iBook/iBshl0.cpp -o $(ObjDir)/iBshl0.o $(CPPFLAGS)

$(ObjDir)/iBsht0.o: $(TevDir)/iBook/iBsht0.cpp
	$(CPP) -c $(TevDir)/iBook/iBsht0.cpp -o $(ObjDir)/iBsht0.o $(CPPFLAGS)

$(ObjDir)/KpGecko0.o: $(TevDir)/xml/KpGecko0.cpp
	$(CPP) -c $(TevDir)/xml/KpGecko0.cpp -o $(ObjDir)/KpGecko0.o $(CPPFLAGS)

$(ObjDir)/Diskid32.o: $(BaseDir)/common/Diskid32.cpp
	$(CPP) -c $(BaseDir)/common/Diskid32.cpp -o $(ObjDir)/Diskid32.o $(CPPFLAGS)

$(ObjDir)/KPSOCK.o: $(BaseDir)/common/KPSOCK.cpp
	$(CPP) -c $(BaseDir)/common/KPSOCK.cpp -o $(ObjDir)/KPSOCK.o $(CPPFLAGS)

$(ObjDir)/KpPubDlg.o: $(BaseDir)/common/KpPubDlg.cpp
	$(CPP) -c $(BaseDir)/common/KpPubDlg.cpp -o $(ObjDir)/KpPubDlg.o $(CPPFLAGS)

$(ObjDir)/Kpcapp.o: $(BaseDir)/common/Kpcapp.cpp
	$(CPP) -c $(BaseDir)/common/Kpcapp.cpp -o $(ObjDir)/Kpcapp.o $(CPPFLAGS)

$(ObjDir)/Kpcons.o: $(BaseDir)/common/Kpcons.cpp
	$(CPP) -c $(BaseDir)/common/Kpcons.cpp -o $(ObjDir)/Kpcons.o $(CPPFLAGS)

$(ObjDir)/Kpctype.o: $(BaseDir)/common/Kpctype.cpp
	$(CPP) -c $(BaseDir)/common/Kpctype.cpp -o $(ObjDir)/Kpctype.o $(CPPFLAGS)

$(ObjDir)/Kperr.o: $(BaseDir)/common/Kperr.cpp
	$(CPP) -c $(BaseDir)/common/Kperr.cpp -o $(ObjDir)/Kperr.o $(CPPFLAGS)

$(ObjDir)/Kperrl_XFS.o: $(BaseDir)/common/Kperrl_XFS.cpp
	$(CPP) -c $(BaseDir)/common/Kperrl_XFS.cpp -o $(ObjDir)/Kperrl_XFS.o $(CPPFLAGS)

$(ObjDir)/Kpsort.o: $(BaseDir)/common/Kpsort.cpp
	$(CPP) -c $(BaseDir)/common/Kpsort.cpp -o $(ObjDir)/Kpsort.o $(CPPFLAGS)

$(ObjDir)/Kpstdio.o: $(BaseDir)/common/Kpstdio.cpp
	$(CPP) -c $(BaseDir)/common/Kpstdio.cpp -o $(ObjDir)/Kpstdio.o $(CPPFLAGS)

$(ObjDir)/Kpstdlib.o: $(BaseDir)/common/Kpstdlib.cpp
	$(CPP) -c $(BaseDir)/common/Kpstdlib.cpp -o $(ObjDir)/Kpstdlib.o $(CPPFLAGS)

$(ObjDir)/Kpstring.o: $(BaseDir)/common/Kpstring.cpp
	$(CPP) -c $(BaseDir)/common/Kpstring.cpp -o $(ObjDir)/Kpstring.o $(CPPFLAGS)

$(ObjDir)/KpFileSys.o: $(BaseDir)/common/KpFileSys.cpp
	$(CPP) -c $(BaseDir)/common/KpFileSys.cpp -o $(ObjDir)/KpFileSys.o $(CPPFLAGS)

$(ObjDir)/Kpwindow.o: $(BaseDir)/common/Kpwindow.cpp
	$(CPP) -c $(BaseDir)/common/Kpwindow.cpp -o $(ObjDir)/Kpwindow.o $(CPPFLAGS)

$(ObjDir)/kpcurdat.o: $(BaseDir)/common/kpcurdat.cpp
	$(CPP) -c $(BaseDir)/common/kpcurdat.cpp -o $(ObjDir)/kpcurdat.o $(CPPFLAGS)

$(ObjDir)/kptree.o: $(BaseDir)/common/kptree.cpp
	$(CPP) -c $(BaseDir)/common/kptree.cpp -o $(ObjDir)/kptree.o $(CPPFLAGS)

$(ObjDir)/Kphp1152.o: $(BaseDir)/kphp11/Kphp1152.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp1152.cpp -o $(ObjDir)/Kphp1152.o $(CPPFLAGS)

$(ObjDir)/Kphp11d.o: $(BaseDir)/kphp11/Kphp11d.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11d.cpp -o $(ObjDir)/Kphp11d.o $(CPPFLAGS)

$(ObjDir)/Kphp11m.o: $(BaseDir)/kphp11/Kphp11m.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11m.cpp -o $(ObjDir)/Kphp11m.o $(CPPFLAGS)

$(ObjDir)/Kphp11mz.o: $(BaseDir)/kphp11/Kphp11mz.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11mz.cpp -o $(ObjDir)/Kphp11mz.o $(CPPFLAGS)

$(ObjDir)/Kphp11p.o: $(BaseDir)/kphp11/Kphp11p.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11p.cpp -o $(ObjDir)/Kphp11p.o $(CPPFLAGS)

$(ObjDir)/Kphp11rc.o: $(BaseDir)/kphp11/Kphp11rc.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11rc.cpp -o $(ObjDir)/Kphp11rc.o $(CPPFLAGS)

$(ObjDir)/Kphp11ry.o: $(BaseDir)/kphp11/Kphp11ry.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11ry.cpp -o $(ObjDir)/Kphp11ry.o $(CPPFLAGS)

$(ObjDir)/Kphp11s.o: $(BaseDir)/kphp11/Kphp11s.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11s.cpp -o $(ObjDir)/Kphp11s.o $(CPPFLAGS)

$(ObjDir)/Kphp11t.o: $(BaseDir)/kphp11/Kphp11t.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11t.cpp -o $(ObjDir)/Kphp11t.o $(CPPFLAGS)

$(ObjDir)/Kphp11tt.o: $(BaseDir)/kphp11/Kphp11tt.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11tt.cpp -o $(ObjDir)/Kphp11tt.o $(CPPFLAGS)

$(ObjDir)/Kphp11w.o: $(BaseDir)/kphp11/Kphp11w.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11w.cpp -o $(ObjDir)/Kphp11w.o $(CPPFLAGS)

$(ObjDir)/Kphp11y.o: $(BaseDir)/kphp11/Kphp11y.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11y.cpp -o $(ObjDir)/Kphp11y.o $(CPPFLAGS)

$(ObjDir)/Kphp11yd.o: $(BaseDir)/kphp11/Kphp11yd.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11yd.cpp -o $(ObjDir)/Kphp11yd.o $(CPPFLAGS)

$(ObjDir)/Kpstap.o: $(BaseDir)/kps/Kpstap.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstap.cpp -o $(ObjDir)/Kpstap.o $(CPPFLAGS)

$(ObjDir)/Kpstapa.o: $(BaseDir)/kps/Kpstapa.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapa.cpp -o $(ObjDir)/Kpstapa.o $(CPPFLAGS)

$(ObjDir)/Kpstapd.o: $(BaseDir)/kps/Kpstapd.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapd.cpp -o $(ObjDir)/Kpstapd.o $(CPPFLAGS)

$(ObjDir)/Kpstapl.o: $(BaseDir)/kps/Kpstapl.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapl.cpp -o $(ObjDir)/Kpstapl.o $(CPPFLAGS)

$(ObjDir)/Kpstapr.o: $(BaseDir)/kps/Kpstapr.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapr.cpp -o $(ObjDir)/Kpstapr.o $(CPPFLAGS)

$(ObjDir)/Kpstapu.o: $(BaseDir)/kps/Kpstapu.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapu.cpp -o $(ObjDir)/Kpstapu.o $(CPPFLAGS)

$(ObjDir)/Kpstapg.o: $(BaseDir)/kps/Kpstapg.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapg.cpp -o $(ObjDir)/Kpstapg.o $(CPPFLAGS)

$(ObjDir)/Kpstapg0.o: $(BaseDir)/kps/Kpstapg0.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapg0.cpp -o $(ObjDir)/Kpstapg0.o $(CPPFLAGS)

$(ObjDir)/Kpstaps.o: $(BaseDir)/kps/Kpstaps.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstaps.cpp -o $(ObjDir)/Kpstaps.o $(CPPFLAGS)

$(ObjDir)/Kpstaf.o: $(BaseDir)/kps/Kpstaf.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstaf.cpp -o $(ObjDir)/Kpstaf.o $(CPPFLAGS)

$(ObjDir)/Kpstape.o: $(BaseDir)/kps/Kpstape.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstape.cpp -o $(ObjDir)/Kpstape.o $(CPPFLAGS)

$(ObjDir)/kpstart_ini.o: $(ProdDir)/kpstart_ini.cpp
	$(CPP) -c $(ProdDir)/kpstart_ini.cpp -o $(ObjDir)/kpstart_ini.o $(CPPFLAGS)

$(ObjDir)/kpsttrg.o: $(ProdDir)/kpsttrg.cpp
	$(CPP) -c $(ProdDir)/kpsttrg.cpp -o $(ObjDir)/kpsttrg.o $(CPPFLAGS)

$(ObjDir)/KPTHP1.o: $(BaseDir)/kpt/KPTHP1.cpp
	$(CPP) -c $(BaseDir)/kpt/KPTHP1.cpp -o $(ObjDir)/KPTHP1.o $(CPPFLAGS)

$(ObjDir)/Kptt2.o: $(BaseDir)/kpt/Kptt2.cpp
	$(CPP) -c $(BaseDir)/kpt/Kptt2.cpp -o $(ObjDir)/Kptt2.o $(CPPFLAGS)

$(ObjDir)/Kpttuc.o: $(BaseDir)/kpt/Kpttuc.cpp
	$(CPP) -c $(BaseDir)/kpt/Kpttuc.cpp -o $(ObjDir)/Kpttuc.o $(CPPFLAGS)

$(ObjDir)/Kpttucc.o: $(BaseDir)/kpt/Kpttucc.cpp
	$(CPP) -c $(BaseDir)/kpt/Kpttucc.cpp -o $(ObjDir)/Kpttucc.o $(CPPFLAGS)

$(ObjDir)/Kpttucf.o: $(BaseDir)/kpt/Kpttucf.cpp
	$(CPP) -c $(BaseDir)/kpt/Kpttucf.cpp -o $(ObjDir)/Kpttucf.o $(CPPFLAGS)

$(ObjDir)/Kpttul.o: $(BaseDir)/kpt/Kpttul.cpp
	$(CPP) -c $(BaseDir)/kpt/Kpttul.cpp -o $(ObjDir)/Kpttul.o $(CPPFLAGS)

$(ObjDir)/kpt71tou.o: $(BaseDir)/kpt/kpt71tou.cpp
	$(CPP) -c $(BaseDir)/kpt/kpt71tou.cpp -o $(ObjDir)/kpt71tou.o $(CPPFLAGS)

$(ObjDir)/KPFONTS.o: $(CommonDir)/common/KPFONTS.cpp
	$(CPP) -c $(CommonDir)/common/KPFONTS.cpp -o $(ObjDir)/KPFONTS.o $(CPPFLAGS)

$(ObjDir)/kpcolors.o: $(CommonDir)/common/kpcolors.cpp
	$(CPP) -c $(CommonDir)/common/kpcolors.cpp -o $(ObjDir)/kpcolors.o $(CPPFLAGS)

$(ObjDir)/cdecode.o: $(BaseDir)/common/cdecode.c
	$(CC) -c $(BaseDir)/common/cdecode.c -o $(ObjDir)/cdecode.o $(CCFLAGS)

$(ObjDir)/cencode.o: $(BaseDir)/common/cencode.c
	$(CC) -c $(BaseDir)/common/cencode.c -o $(ObjDir)/cencode.o $(CCFLAGS)


# depend: dep

# dep:
#	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)

# clean: 
#	rm -f $(OBJ) $(OUT) Makefile.bak 
