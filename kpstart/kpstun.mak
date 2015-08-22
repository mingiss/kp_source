Proj = kpstun

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
WINDRES = "$(ProgFiles)/CodeBlocks/MinGW/bin/windres.exe"

CXXINCS = \
   -I$(CommonDir)/common \
   -I$(CommonDir)/kpt \
   -I$(CommonDir)/xml \
   -I$(BaseDir)/common \
   -I$(BaseDir)/kpt \
   -I$(BaseDir)/kps \
   -I$(BaseDir)/kphp11 \
   -I$(TevDir)/rtf \
   -I$(TevDir)/tex \
   -I$(TevDir)/xml \
   -I$(TevDir)/xml/tux_gecko/include \
   -I$(TevDir)/iBook \
   -I$(TevDir)/lzdsh \
   -I$(ProdDir)

CXXFLAGS = $(CXXINCS) -DEnvir=15 -DKPSTEDI_MODE=6 -DMsgLang=1
CPPFLAGS = $(CXXFLAGS) 
CCFLAGS = $(CXXFLAGS) 

RCINC = -I$(BaseDir)/common
#RCFLAGS = $(RCINC) -Jrc -Ocoff
#RCFLAGS = $(RCINC) -Jrc -Ores
RCFLAGS = $(RCINC)

LDFLAGS =  -mwindows -Wl,-Map,kpstun_mingw.map
# LDFLAGS = -Wl,-subsystem,windows

OBJ = \
   $(ObjDir)/kpcurdat.o \
   $(ObjDir)/Kphp11yd.o \
   $(ObjDir)/xmlt0.o \
   $(ObjDir)/xmlsty0.o \
   $(ObjDir)/xmlsty2.o \
   $(ObjDir)/Tvxmltt.o \
   $(ObjDir)/iBsh0.o \
   $(ObjDir)/iBshl0.o \
   $(ObjDir)/iBsht0.o \
   $(ObjDir)/KpGecko0.o \
   $(ObjDir)/kpstapg0.o \
   $(ObjDir)/kpstreg_ini.o \
   $(ObjDir)/kpstun.o

# RES  = $(ObjDir)/kpstun.res
RES  = $(ObjDir)/kpstun_res.o

# -L"$(ProgFiles)/CodeBlocks/MinGW/lib" - neveikia kažkodėl, perkėliau į $(BaseDir)/common/MinGW/lib    

LIBS = \
   -L$(BaseDir)/common \
   -L$(BaseDir)/common/MinGW/lib \
   -lkplibwr \
   -lgdi32 \
   -luser32 \
   -lkernel32 \
   -lcomctl32 \
   -lcomdlg32 \
   -lwinmm \
   -ladvapi32 \
   -lsetupapi \
   -lwsock32 \
   -luuid \
   -lntdll \
   -lole32

BIN = $(ProdDir)/$(Proj).exe

$(BIN): $(OBJ) $(RES)
	$(CPP) -o $(BIN) $(OBJ) $(RES) $(LIBS) $(LDFLAGS)

$(ObjDir)/kpcurdat.o: $(BaseDir)/common/kpcurdat.cpp
	$(CPP) -c $(BaseDir)/common/kpcurdat.cpp -o $(ObjDir)/kpcurdat.o $(CPPFLAGS)

$(ObjDir)/Kphp11yd.o: $(BaseDir)/kphp11/Kphp11yd.cpp
	$(CPP) -c $(BaseDir)/kphp11/Kphp11yd.cpp -o $(ObjDir)/Kphp11yd.o $(CPPFLAGS)

$(ObjDir)/xmlt0.o: $(TevDir)/xml/xmlt0.cpp
	$(CPP) -c $(TevDir)/xml/xmlt0.cpp -o $(ObjDir)/xmlt0.o $(CPPFLAGS)
 
$(ObjDir)/xmlsty0.o: $(TevDir)/xml/xmlsty0.cpp
	$(CPP) -c $(TevDir)/xml/xmlsty0.cpp -o $(ObjDir)/xmlsty0.o $(CPPFLAGS)
 
$(ObjDir)/xmlsty2.o: $(TevDir)/xml/xmlsty2.cpp
	$(CPP) -c $(TevDir)/xml/xmlsty2.cpp -o $(ObjDir)/xmlsty2.o $(CPPFLAGS)

$(ObjDir)/Tvxmltt.o: $(CommonDir)/xml/Tvxmltt.cpp
	$(CPP) -c $(CommonDir)/xml/Tvxmltt.cpp -o $(ObjDir)/Tvxmltt.o $(CPPFLAGS)

$(ObjDir)/iBsh0.o: $(TevDir)/iBook/iBsh0.cpp
	$(CPP) -c $(TevDir)/iBook/iBsh0.cpp -o $(ObjDir)/iBsh0.o $(CPPFLAGS)

$(ObjDir)/iBshl0.o: $(TevDir)/iBook/iBshl0.cpp
	$(CPP) -c $(TevDir)/iBook/iBshl0.cpp -o $(ObjDir)/iBshl0.o $(CPPFLAGS)

$(ObjDir)/iBsht0.o: $(TevDir)/iBook/iBsht0.cpp
	$(CPP) -c $(TevDir)/iBook/iBsht0.cpp -o $(ObjDir)/iBsht0.o $(CPPFLAGS)

$(ObjDir)/KpGecko0.o: $(TevDir)/xml/KpGecko0.cpp
	$(CPP) -c $(TevDir)/xml/KpGecko0.cpp -o $(ObjDir)/KpGecko0.o $(CPPFLAGS)

$(ObjDir)/Kpstapg0.o: $(BaseDir)/kps/Kpstapg0.cpp
	$(CPP) -c $(BaseDir)/kps/Kpstapg0.cpp -o $(ObjDir)/Kpstapg0.o $(CPPFLAGS)

$(ObjDir)/kpstreg_ini.o: $(ProdDir)/kpstreg_ini.cpp
	$(CPP) -c $(ProdDir)/kpstreg_ini.cpp -o $(ObjDir)/kpstreg_ini.o $(CPPFLAGS)
 
$(ObjDir)/kpstun.o: $(ProdDir)/kpstun.cpp
	$(CPP) -c  $(ProdDir)/kpstun.cpp -o $(ObjDir)/kpstun.o $(CPPFLAGS) 

# $(ObjDir)/kpstun.res: $(ProdDir)/kpstun.rc 
#	$(WINDRES) -i $(ProdDir)/kpstun.rc -o $(ObjDir)/kpstun.res $(RCFLAGS) 

$(ObjDir)/kpstun_res.o: $(ProdDir)/kpstun.rc 
	$(WINDRES) -i $(ProdDir)/kpstun.rc -o $(ObjDir)/kpstun_res.o $(RCFLAGS) 
