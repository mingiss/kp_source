// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#ifndef envir_included
// #error envir.h not included
#endif

#if Envir==17 // MSWin32Mfc

#if !defined(AFX_STDAFX_H__A9F41AE7_551D_11D9_9EAB_004095201DED__INCLUDED_)
#define AFX_STDAFX_H__A9F41AE7_551D_11D9_9EAB_004095201DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r g�ngige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fugt unmittelbar vor der vorhergehenden Zeile zusatzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__A9F41AE7_551D_11D9_9EAB_004095201DED__INCLUDED_)

#endif // #if Envir==