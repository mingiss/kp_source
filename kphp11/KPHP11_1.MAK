# Microsoft Visual C++ generated build script - Do not modify

PROJ = KPHP11_1
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\KP\SOURCE\KPHP11\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = KPIT3.C     
FIRSTCPP = KPHP11.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AH /Od /D "_DEBUG" /I "c:\msvc\include" /I "c:\kp\source\kpx" /I "c:\kp\source\kphp11" /FR /GA /Fd"KPHP11.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = 
RESFLAGS = 
RUNFLAGS = 
DEFFILE = KPHP11.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = KPIV1.SBR \
		KPIV2.SBR \
		KPIVW.SBR \
		KPIT3.SBR \
		KPXT3.SBR \
		KPHP11D.SBR \
		KPHP11Y.SBR \
		KPHP11M.SBR \
		KPHP11P.SBR \
		KPHP11TT.SBR \
		KPHP11MZ.SBR \
		KPHP1152.SBR \
		KPHP11.SBR \
		KPHP11E1.SBR


KPIV1_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h


KPIV2_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h


KPIVW_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h


KPIT3_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h


KPXT3_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h


KPHP11D_DEP = c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11p.h \
	c:\kp\source\kphp11\kphp11tt.h \
	c:\kp\source\kphp11\kphp11mz.h \
	c:\kp\source\kphp11\kphp1152.h


KPHP11Y_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kphp11\kphp11p.h


KPHP11M_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11m.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kphp11\kphp11p.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11d.h


KPHP11P_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11m.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kphp11\kphp11p.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11d.h


KPHP11TT_DEP = c:\kp\source\kphp11\kphp11tt.h \
	c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11p.h \
	c:\kp\source\kphp11\kphp1152.h


KPHP11MZ_DEP = c:\kp\source\kphp11\kphp11mz.h \
	c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11p.h


KPHP1152_DEP = c:\kp\source\kphp11\kphp1152.h \
	c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kphp11\kphp11.h \
	c:\kp\source\kphp11\kphp11y.h


KPHP11_DEP = c:\kp\source\kphp11\kphp11.h


KPHP11_DEP = c:\kp\source\kphp11\kphp11y.h \
	c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11e.h \
	c:\kp\source\kphp11\kphp11m.h \
	c:\kp\source\kphp11\kphp11p.h \
	c:\kp\source\kphp11\kphp11d.h \
	c:\kp\source\kphp11\kphp1152.h


KPHP11E1_DEP = c:\kp\source\kpx\kpxe.h \
	c:\kp\source\kphp11\kpxeg.h \
	c:\kp\source\kpx\kpx.h \
	c:\kp\source\kpx\kpxs.h \
	c:\kp\source\kpx\kpjt0.h \
	c:\kp\source\kpx\kpxm.h \
	c:\kp\source\kpx\kpxi.h \
	c:\kp\source\kpx\kpxc.h \
	c:\kp\source\kpx\kpxg.h \
	c:\kp\source\kpx\kpxd.h \
	c:\kp\source\kpx\kpxt.h \
	c:\kp\source\kpx\kpxo.h \
	c:\kp\source\kpx\kpxr.h \
	c:\kp\source\kpx/kpxs.h \
	c:\kp\source\kpx/\kpxe.h \
	c:\kp\source\kpx/\kpx.h \
	c:\kp\source\kpx/\kpxs.h \
	c:\kp\source\kpx/\kpjt0.h \
	c:\kp\source\kpx/\kpxm.h \
	c:\kp\source\kpx/\kpxi.h \
	c:\kp\source\kpx/\kpxc.h \
	c:\kp\source\kpx/\kpxg.h \
	c:\kp\source\kpx/\kpxd.h \
	c:\kp\source\kpx/\kpxt.h \
	c:\kp\source\kpx/\kpxo.h \
	c:\kp\source\kpx/\kpxr.h \
	c:\kp\source\kpx/kpjt0.h \
	c:\kp\source\kpx/kpxm.h \
	c:\kp\source\kpx/kpxi.h \
	c:\kp\source\kpx/kpxc.h \
	c:\kp\source\kpx/kpxg.h \
	c:\kp\source\kpx/kpxd.h \
	c:\kp\source\kpx/kpxt.h \
	c:\kp\source\kpx/kpxo.h \
	c:\kp\source\kpx/kpxr.h \
	c:\kp\source\kpx\kpxw.h \
	c:\kp\source\kpx\kpxv.h \
	c:\kp\source\kpx\kpxn.h \
	c:\kp\source\kpx/\kpxn.h \
	c:\kp\source\kpx/\kpxf.h \
	c:\kp\source\kpx\kpxf.h \
	c:\kp\source\kphp11\kphp11e.h


all:	$(PROJ).EXE $(PROJ).BSC

KPIV1.OBJ:	..\KPX\KPIV1.CPP $(KPIV1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\KPX\KPIV1.CPP

KPIV2.OBJ:	..\KPX\KPIV2.CPP $(KPIV2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\KPX\KPIV2.CPP

KPIVW.OBJ:	..\KPX\KPIVW.CPP $(KPIVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\KPX\KPIVW.CPP

KPIT3.OBJ:	..\KPX\KPIT3.C $(KPIT3_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c ..\KPX\KPIT3.C

KPXT3.OBJ:	..\KPX\KPXT3.C $(KPXT3_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\KPX\KPXT3.C

KPHP11D.OBJ:	KPHP11D.CPP $(KPHP11D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11D.CPP

KPHP11Y.OBJ:	KPHP11Y.CPP $(KPHP11Y_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11Y.CPP

KPHP11M.OBJ:	KPHP11M.CPP $(KPHP11M_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11M.CPP

KPHP11P.OBJ:	KPHP11P.CPP $(KPHP11P_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11P.CPP

KPHP11TT.OBJ:	KPHP11TT.CPP $(KPHP11TT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11TT.CPP

KPHP11MZ.OBJ:	KPHP11MZ.CPP $(KPHP11MZ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11MZ.CPP

KPHP1152.OBJ:	KPHP1152.CPP $(KPHP1152_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP1152.CPP

KPHP11_1.RES:	KPHP11_1.RC $(KPHP11_1_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r KPHP11_1.RC

KPHP11.OBJ:	KPHP11.CPP $(KPHP11_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c KPHP11.CPP

KPHP11E1.OBJ:	KPHP11E1.CPP $(KPHP11E1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c KPHP11E1.CPP


$(PROJ).EXE::	KPHP11_1.RES

$(PROJ).EXE::	KPIV1.OBJ KPIV2.OBJ KPIVW.OBJ KPIT3.OBJ KPXT3.OBJ KPHP11D.OBJ KPHP11Y.OBJ \
	KPHP11M.OBJ KPHP11P.OBJ KPHP11TT.OBJ KPHP11MZ.OBJ KPHP1152.OBJ KPHP11.OBJ KPHP11E1.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
KPIV1.OBJ +
KPIV2.OBJ +
KPIVW.OBJ +
KPIT3.OBJ +
KPXT3.OBJ +
KPHP11D.OBJ +
KPHP11Y.OBJ +
KPHP11M.OBJ +
KPHP11P.OBJ +
KPHP11TT.OBJ +
KPHP11MZ.OBJ +
KPHP1152.OBJ +
KPHP11.OBJ +
KPHP11E1.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
h:\MSVC\LIB\+
h:\MSVC\MFC\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) KPHP11_1.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	KPHP11_1.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) KPHP11_1.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
