// ---------------------------
// kpstapg.cpp
// grupinių leidinių / prenumeratų / update tvarkymas
//
// 2012-10-23  mp    GetGrpInstPath(): Inno registre diegimo katalogo neieškom – dabar reikia rast tik lentyninius, senų reikia nerodyt
// 2012-10-30  mp    Logino forma su nuoroda į klientų sistemą naujų klientų registravimuisi
// 2012-10-31  mp    grįžimas iš išorinio naršymo į loginą
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#if Compiler != Watcom
#include <sstream>
#endif
#include <fstream>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <winuser.h> // buvo kažkodėl užkomentuotas, reikalingas Watcom 1.8
#include <windowsx.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <richedit.h>
#include <Richole.h>
#include <psapi.h>

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#include "md5.h"

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpstdlib.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpttucf.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlg.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpMsHtml.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstlsvr.h"
#include "kpstmsg.h"
#include "kpstmsg_en.h"
#include "kpstmsg_lt.h"
#include "kpstmsg_pl_1250.h"
#include "kpstmsg_pl_1257.h"
#include "kpstmsg_ru.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"
#include "kpstedi.h"
#include "kpsttre.h"
#include "kpsttrg.h"
#include "kpstapa.h"
#include "kpstaps.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// -----------------------------------------
#ifdef KPST_PRODGRP_STATIC_CFG
unsigned char lpszStartGrpCfgDef[] =
{

#if TRUE // FALSE // mano pagrindinis pavyzdys

   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
   "<pr>\r\n"
   "   <resp>KpReg-Ok</resp>\r\n"

#if TRUE // FALSE
// "   <background size=\"1238654\" date=\"2012.08.20\" caption=\"24\">http://siuntiniai.tev.lt/updates/temp/fonas.bmp</background>\r\n"
   "   <background size=\"1238654\" date=\"2012.08.20\" caption=\"24\">http://siuntiniai.tev.lt/updates/temp/fonas_1.bmp</background>\r\n"
   "   <button id=\"exit\">\r\n"
   "      <butimg size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_exit.bmp</butimg>\r\n"
   "      <butpressed size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_exit_sel.bmp</butpressed>\r\n"
   "      <buthover size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_exit_light.bmp</buthover>\r\n"
   "   </button>\r\n"
   "   <button id=\"minimize\">\r\n"
   "      <butimg size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_min.bmp</butimg>\r\n"
   "      <butpressed size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_min_sel.bmp</butpressed>\r\n"
   "      <buthover size=\"1256\" date=\"2006.02.08\">http://siuntiniai.tev.lt/updates/temp/mahd_min_light.bmp</buthover>\r\n"
   "   </button>\r\n"
#endif

// "   <file size=\"297995\">http://siuntiniai.tev.lt/updates/temp/PD-mt910-fonas_1.png</file>\r\n"
// "   <file size=\"1909718\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/PD-mt910-fonas_1.bmp</file>\r\n"
// "   <file size=\"205356\" date=\"2011.10.05\">http://updates.tev.lt/lentyna/fonas.gif</file>\r\n"
// "   <file size=\"1125150\" date=\"2011.10.05\">http://siuntiniai.tev.lt/updates/temp/lentos.bmp</file>\r\n"
   "   <file size=\"252090\" date=\"2011.10.05\">http://siuntiniai.tev.lt/updates/temp/lentos.png</file>\r\n"
   "\r\n"
#     if FALSE
   "   <item>\r\n"
   "      <appname>Puikusis produktas</appname>\r\n"
   "      <lic>L9A6-J3E7-R55G</lic>\r\n"
   "   </item>\r\n"
#     endif
   "   <item>\r\n"
// "      <appname>Matematika Tau. 9 klasė</appname>\r\n"
   "      <appname>Literatūra 11 klasei. Chrestomatija 2 dalis</appname>\r\n"
   "      <status>Free</status>\r\n"
// "      <lic>9RG1-547L-G732</lic>\r\n"
   "      <lic>637R-A929-G465</lic>\r\n"
// "      <setup size=\"30225094\">http://siuntiniai.tev.lt/updates/temp/MaTau-9v_prenumeruojamas_diegimas.exe</setup>\r\n"
// "      <setup size=\"5639146\">http://siuntiniai.tev.lt/updates/temp/MaTau-9v_prenumeruojamas_diegimas.exe</setup>\r\n"
   "      <setup size=\"5639146\">http://siuntiniai.tev.lt/updates/temp/Ch112_diegimas_lentynoje.exe</setup>\r\n"
// "      <launch>tux:///KpStart:StartAndClose:{app}\\MaTau9v.exe</launch>\r\n"
   "      <launch>tux:///KpStart:Start:{app}\\MaTau9v.exe</launch>\r\n"
   "      <file size=\"4792\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-9955-879-62-6.gif</file>\r\n"
   "      <file size=\"4792\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-9955-879-62-6_bw.gif</file>\r\n"
   "      <file size=\"1455\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/spinner.gif</file>\r\n"
   "      <file size=\"2606\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/exit_s.bmp</file>\r\n"
   "      <file size=\"31607\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/diag_msg_but.gif</file>\r\n"
// "      <mpar>{file}</mpar>\r\n" // "      <mpar>tux:///{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{appname}</mpar>\r\n"
   "   </item>\r\n"
   "   <item>\r\n"
   "      <appname>Matematika tau 11. Bendrasis kursas</appname>\r\n"
   "      <status>Available</status>\r\n"
   "      <lic>G5RL-97J8-4L1L</lic>\r\n"
// "      <setup size=\"44410047\">http://siuntiniai.tev.lt/updates/temp/TAU11BK_prenumeruojamas_diegimas.exe</setup>\r\n"
   "      <setup size=\"44410047\">http://siuntiniai.tev.lt/updates/temp/TAU11BK_diegimas_lentynoje.exe</setup>\r\n"
// "      <launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>\r\n"
   "      <launch>tux:///KpStart:Start:{app}\\XFS.exe</launch>\r\n"
   "      <file size=\"3952\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-609-433-039-1.gif</file>\r\n"
   "      <file size=\"3952\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-609-433-039-1_bw.gif</file>\r\n"
   "      <file size=\"1455\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/spinner.gif</file>\r\n"
   "      <file size=\"2606\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/exit_s.bmp</file>\r\n"
   "      <file size=\"31607\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/diag_msg_but.gif</file>\r\n"
// "      <mpar>{file}</mpar>\r\n" // "      <mpar>tux:///{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{appname}</mpar>\r\n"
   "   </item>\r\n"
   "   <item>\r\n"
   "      <appname>Matematika Tau. 10 klasė</appname>\r\n"
   "      <status>Available</status>\r\n"
   "      <lic>U4U1-R47A-38G3</lic>\r\n"
   "      <setup size=\"23878439\">http://siuntiniai.tev.lt/updates/temp/MaTau-10v_prenumeruojamas_diegimas.exe</setup>\r\n"
// "      <launch>tux:///KpStart:StartAndClose:{app}\\MaTau10v.exe</launch>\r\n"
   "      <launch>tux:///KpStart:Start:{app}\\MaTau10v.exe</launch>\r\n"
   "      <file size=\"5487\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-609-433-012-4.gif</file>\r\n"
   "      <file size=\"5487\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/978-609-433-012-4_bw.gif</file>\r\n"
   "      <file size=\"1455\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/spinner.gif</file>\r\n"
   "      <file size=\"2606\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/exit_s.bmp</file>\r\n"
   "      <file size=\"31607\" date=\"2011.10.01\">http://siuntiniai.tev.lt/updates/temp/diag_msg_but.gif</file>\r\n"
// "      <mpar>{file}</mpar>\r\n" // "      <mpar>tux:///{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{file}</mpar>\r\n"
// "      <mpar>{appname}</mpar>\r\n"
   "   </item>\r\n"
   "\r\n"
   "   <mhead>\r\n"
   "      &lt;?xml version=\"1.0\" encoding=&quot;UTF-8\"?&gt;\r\n" // "U duoda umlautą
   "      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;\r\n"
   "      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;\r\n"
   "         &lt;head&gt;\r\n"
   "            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;\r\n"
   "            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;\r\n"
   "            &lt;style&gt;\r\n"
   "               img#background\r\n"
   "               &#123;\r\n"
   "                  z-index: -1;\r\n"
   "                  position: absolute;\r\n"
   "                  color: white;\r\n"
   "                  margin-left: -8px;\r\n"
   "                  margin-top: -8px;\r\n"
   "               &#125;\r\n"
   "               img.hidden\r\n"
   "               &#123;\r\n"
   "                  display: none;\r\n"
   "               &#125;\r\n"
   "               a\r\n"
   "               &#123;\r\n"
   "                  font-size: 24px;\r\n"
   "                  font-weight: bold;\r\n"
   "                  text-decoration: none;\r\n"
   "                  color: navy;\r\n"
   "                  font-family: sans-serif;\r\n"
   "               &#125;\r\n"
   "               .inactive\r\n"
   "               &#123;\r\n"
   "                  font-size: 24px;\r\n"
   "                  font-weight: bold;\r\n"
   "                  text-decoration: none;\r\n"
   "                  color: grey;\r\n"
   "                  font-family: sans-serif;\r\n"
   "               &#125;\r\n"
   "            &lt;/style&gt;\r\n"
   "         &lt;/head&gt;\r\n"
   "         &lt;body&gt;\r\n"
// "            &lt;img id=\"background\" src=\"{file}\" width=\"800\" height=\"600\"/&gt;\r\n"
// "            &lt;img id=\"background\" src=\"{file}\" width=\"958\" height=\"664\"/&gt;\r\n"
   "            &lt;img id=\"background\" src=\"{file}\" width=\"724\" height=\"518\"/&gt;\r\n"
// "            &lt;img id=\"background\" src=\"{file}\"/&gt;\r\n"
   "            &lt;table border=\"0\"&gt;\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td height=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&lt;a href=\"tux:///KpStart:Browse:http://siuntiniai.tev.lt/updates/temp/StartGrp_grizimas.htm\"&gt;Brausinti&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
// "                  &lt;td&gt;&lt;a href=\"tux:///StartGrp_grizimas.htm\"&gt;Brausinti&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
// "                  &lt;td&gt;&lt;a href=\"tux:///KpStart:Browse:tux:///http://siuntiniai.tev.lt/updates/temp/StartGrp_grizimas.htm\"&gt;Brausinti&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
// "                  &lt;td&gt;&lt;a href=\"http://siuntiniai.tev.lt/updates/temp/StartGrp_grizimas.htm\"&gt;Brausinti&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
// "                  &lt;td&gt;&lt;a href=\"tux:///http://siuntiniai.tev.lt/updates/temp/StartGrp_grizimas.htm\"&gt;Brausinti&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&lt;a href=\"tux:///KpStart:Options:\"&gt;Parinktys&amp;nbsp;&lt;/a&gt;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&lt;a href=\"tux:///KpStart:Login:\"&gt;&amp;nbsp;Keisti vartotoją&lt;/a&gt;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&lt;a href=\"tux:///KpStart:Logoff:\"&gt;&amp;nbsp;Atsijungti&lt;/a&gt;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </mhead>\r\n"
   "   <mitem>\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td width=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a href=\"{launch}\"&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                     &lt;/a&gt;\r\n"
   "                     &lt;a href=\"tux:///KpStart:Uninst:{appname}\"&gt;&lt;img src=\"{file}\"/&gt;&lt;/a&gt;\r\n" // "                        &lt;a href=\"tux:///KpStart:Uninst:{appname}\"&gt;&lt;img src=\"{mpar}\"/&gt;&lt;/a&gt;\r\n"
   "                     &lt;a href=\"tux:///KpStart:DiagMsg:{temp}\\XFS.log; {temp}\\xipa.log; {temp}\\registr.log; {app}\\data.dat\"&gt;&lt;img src=\"{file}\"/&gt;&lt;/a&gt;\r\n" // "                        &lt;a href=\"tux:///KpStart:Uninst:{appname}\"&gt;&lt;img src=\"{mpar}\"/&gt;&lt;/a&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a href=\"{launch}\"&gt;{appname}&lt;/a&gt;\r\n" // "                     &lt;a href=\"{launch}\"&gt;{mpar}&lt;/a&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </mitem>\r\n"
   "   <mwait>\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td width=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Refresh:\"&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
   "                     &lt;/a&gt;\r\n"
// "                     &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Refresh:\"&gt;{appname}&lt;/a&gt;\r\n" // "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Refresh:\"&gt;{mpar}&lt;/a&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </mwait>\r\n"
   "   <mfree>\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td width=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Download:{appname}\"&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
// "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                     &lt;/a&gt;\r\n"
// "                     &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Download:{appname}\"&gt;{appname}&lt;/a&gt;\r\n" // "                     &lt;a class=\"inactive\" href=\"tux:///KpStart:Download:{appname}\"&gt;{mpar}&lt;/a&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </mfree>\r\n"
   "   <mpend>\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td width=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;span class=\"inactive\"&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
   "                        {prc}%\r\n" // "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt; {prc}%\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt; {prc}%\r\n"
   "                     &lt;/span&gt;\r\n"
// "                     &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;span class=\"inactive\"&gt;{appname}&lt;/span&gt;\r\n" // "                     &lt;span class=\"inactive\"&gt;{mpar}&lt;/span&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </mpend>\r\n"
   "   <munavail>\r\n"
   "               &lt;tr&gt;\r\n"
   "                  &lt;td width=\"200\"&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;span class=\"inactive\"&gt;\r\n"
   "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                        &lt;img src=\"{file}\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\"/&gt;\r\n"
// "                        &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                     &lt;/span&gt;\r\n"
// "                     &lt;img src=\"{file}\" class=\"hidden\"/&gt;\r\n" // "                        &lt;img src=\"{mpar}\" class=\"hidden\"/&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;\r\n"
   "                     &lt;span class=\"inactive\"&gt;{appname}&lt;/span&gt;\r\n" // "                     &lt;span class=\"inactive\"&gt;{mpar}&lt;/span&gt;\r\n"
   "                  &lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "                  &lt;td&gt;&amp;nbsp;&lt;/td&gt;\r\n"
   "               &lt;/tr&gt;\r\n"
   "   </munavail>\r\n"
   "   <mtail>\r\n"
   "            &lt;/table&gt;\r\n"
   "         &lt;/body&gt;\r\n"
   "      &lt;/html&gt;\r\n"
   "   </mtail>\r\n"
   "</pr>\r\n"

#endif


#if FALSE // neigiamas atsakymas

   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
   "<pr>\r\n"
// "   <resp>KpReg-Error: Leidinys neprenumeruojamas</resp>\r\n"
// "   <resp>KpReg-Error: ĄČĘĖĮŠŲŪŽąčęėįšųūž Not implemented</resp>\r\n"
// "   <resp>KpReg-Error: Neteisingas vardas/slaptažodis</resp>\r\n"
   "   <resp>KpReg-Error: Testavimo klaida</resp>\r\n"
   "</pr>\r\n"

#endif


#if FALSE // Gintaro PHP klaida, reikia kažkaip žmoniškiau diagnozuoti, dabar lūžta, <b> atpažinęs kaip <background>

   "<br />\r\n"
   "<b>Warning</b>:  mysql_num_rows(): supplied argument is not a valid MySQL result resource in <b>/home/tevukas/domains/tev.lt/public_html/prodgrp.php</b> on line <b>86</b><br />\r\n"

#endif


#if FALSE // Gintaro 2012.05.03

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Unavailable</status>"
"<appname>Ekonomika ir verslumas IX–X klasėms. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<file size=\"2625\" date=\"2010.12.08\">http://images.tevukas.lt/small/ekov910_lt_dwnl.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 10. Lenkų kalba</appname>"
"<lic>9EJG-L83R-27L1</lic>"
"<setup size=\"50522277\">http://siuntiniai.tev.lt/file.php?file=lentyna_plus10_pl_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2229\" date=\"2011.09.02\">http://images.tevukas.lt/small/plus10_pl_dwnl.gif</file>"
"<file size=\"1556\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/plus10_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 10 класс</appname>"
"<lic>672A-4164-27LJ</lic>"
"<setup size=\"51864445\">http://siuntiniai.tev.lt/file.php?file=lentyna_plus10_ru_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2278\" date=\"2011.09.02\">http://images.tevukas.lt/small/plus10_ru_dwnl.gif</file>"
"<file size=\"1585\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/plus10_ru_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. C  . 11-12</appname>"
"<lic>71G1-344L-4622</lic>"
"<setup size=\"30210503\">http://siuntiniai.tev.lt/file.php?file=lentyna_pp1112_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2704\" date=\"2011.09.21\">http://images.tevukas.lt/small/pp1112_lt_dwnl.gif</file>"
"<file size=\"1775\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/pp1112_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. C  . 11-12</appname>"
"<lic>5AL3-E6J8-LG43</lic>"
"<setup size=\"30210503\">http://siuntiniai.tev.lt/file.php?file=lentyna_pp1112_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2704\" date=\"2011.09.21\">http://images.tevukas.lt/small/pp1112_lt_dwnl.gif</file>"
"<file size=\"1775\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/pp1112_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>92AA-R33R-59E8</lic>"
"<setup size=\"94312209\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2252\" date=\"2011.01.06\">http://images.tevukas.lt/small/szikl_lt_dwnl.gif</file>"
"<file size=\"1506\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/szikl_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 11. Bendrasis kursas</appname>"
"<lic>2869-62R9-52LR</lic>"
"<setup size=\"44556780\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11bk_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2770\" date=\"2011.08.18\">http://images.tevukas.lt/small/tau11bk_lt_dwnl.gif</file>"
"<file size=\"1710\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau11bk_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 11. Išplėstinis kursas</appname>"
"<lic>24AA-LU28-A3GR</lic>"
"<setup size=\"39157405\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11ik_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2735\" date=\"2011.08.18\">http://images.tevukas.lt/small/tau11ik_lt_dwnl.gif</file>"
"<file size=\"1745\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau11ik_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 11. Bendrasis kursas</appname>"
"<lic>GG87-1RJ6-R9GG</lic>"
"<setup size=\"44556780\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11bk_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2770\" date=\"2011.08.18\">http://images.tevukas.lt/small/tau11bk_lt_dwnl.gif</file>"
"<file size=\"1710\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau11bk_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 11. Išplėstinis kursas</appname>"
"<lic>7L86-6967-1AUG</lic>"
"<setup size=\"39157405\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11ik_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2735\" date=\"2011.08.18\">http://images.tevukas.lt/small/tau11ik_lt_dwnl.gif</file>"
"<file size=\"1745\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau11ik_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika tau 11. Bendrasis kursas</appname>"
"<lic>U6L9-RE47-4JUE</lic>"
"<setup size=\"44556780\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11bk_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2770\" date=\"2011.08.18\">http://images.tevukas.lt/small/tau11bk_lt_dwnl.gif</file>"
"<file size=\"1710\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau11bk_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. C  . 11-12</appname>"
"<lic>LA91-91R9-3464</lic>"
"<setup size=\"30210503\">http://siuntiniai.tev.lt/file.php?file=lentyna_pp1112_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2704\" date=\"2011.09.21\">http://images.tevukas.lt/small/pp1112_lt_dwnl.gif</file>"
"<file size=\"1775\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/pp1112_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie plus. Klasa 5. Część I.</appname>"
"<lic>RAE5-ERRR-27R9</lic>"
"<setup size=\"37109255\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius51_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"1774\" date=\"2012.01.03\">http://images.tevukas.lt/small/plius51_pl_dwnl.gif</file>"
"<file size=\"1212\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/plius51_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Tavo bičiulis kompiuteris. Informacinės technologijos V–VI klasėms. I dalis</appname>"
"<lic>U83G-J24J-J47G</lic>"
"<setup size=\"79343127\">http://siuntiniai.tev.lt/file.php?file=lentyna_tbk561_lt_diegimas.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2620\" date=\"2012.01.16\">http://images.tevukas.lt/small/tbk561_lt_dwnl.gif</file>"
"<file size=\"1719\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tbk561_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Tavo bičiulis kompiuteris. Informacinės technologijos V–VI klasėms. II dalis</appname>"
"<lic>811R-7L6J-J47E</lic>"
"<setup size=\"61873045\">http://siuntiniai.tev.lt/file.php?file=lentyna_tbk562_lt_diegimas.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2733\" date=\"2012.01.16\">http://images.tevukas.lt/small/tbk562_lt_dwnl.gif</file>"
"<file size=\"1821\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tbk562_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie . Klasa 5. Część I.</appname>"
"<lic>9G76-LL6R-27GR</lic>"
"<setup size=\"35151005\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau51_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"909\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau51_pl_dwnl.gif</file>"
"<file size=\"984\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau51_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie . Klasa 5. Część II.</appname>"
"<lic>1459-3244-27GG</lic>"
"<setup size=\"35431330\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau52_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"914\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau52_pl_dwnl.gif</file>"
"<file size=\"990\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau52_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie . Klasa 7. Część I.</appname>"
"<lic>LEUA-98E4-27EJ</lic>"
"<setup size=\"37034541\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau71_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"864\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau71_pl_dwnl.gif</file>"
"<file size=\"1099\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau71_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie. Klasa 7. Część II.</appname>"
"<lic>31GG-17GR-27E1</lic>"
"<setup size=\"36572110\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau72_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"880\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau72_pl_dwnl.gif</file>"
"<file size=\"1141\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau72_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Available</status>"
"<appname>Matematika Tau. 5 klasė. II dalis</appname>"
"<lic>9U4E-8AA2-1612</lic>"
"<setup size=\"35216517\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau52_lt_diegimas.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"719\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau52_lt_dwnl.gif</file>"
"<file size=\"785\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau52_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau. 6 klasė. I dalis</appname>"
"<lic>6G8R-785E-1614</lic>"
"<setup size=\"34317774\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau61_lt_diegimas.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"869\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau61_lt_dwnl.gif</file>"
"<file size=\"840\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau61_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematyka dla Ciebie plus. Klasa 10. Część II.</appname>"
"<lic>UUJ3-G9J4-27E7</lic>"
"<setup size=\"34991020\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau102_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2057\" date=\"2012.01.03\">http://images.tevukas.lt/small/tau102_pl_dwnl.gif</file>"
"<file size=\"1559\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tau102_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Twój przyjaciel komputer. Technologia informacyjna dla klas VII–VIII. Część II</appname>"
"<lic>A2GA-8524-28JJ</lic>"
"<setup size=\"57496491\">http://siuntiniai.tev.lt/file.php?file=lentyna_tbk782_pl_instalacja.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2748\" date=\"2012.01.16\">http://images.tevukas.lt/small/tbk782_pl_dwnl.gif</file>"
"<file size=\"1971\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/tbk782_pl_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>8A5A-2JJ1-L2A3</lic>"
"<setup size=\"94312209\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_lt_setup.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:{app}\\XFS.exe</launch>"
"<file size=\"2252\" date=\"2011.01.06\">http://images.tevukas.lt/small/szikl_lt_dwnl.gif</file>"
"<file size=\"1506\" date=\"2012.05.03\">http://images.tevukas.lt/small_bw/szikl_lt_dwnl_bw.gif</file>"
"<file size=\"1455\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"2606\" date=\"2012.05.03\">http://tev.lt/lentyna_inc/exit_s.bmp</file>"
"</item>"
"  <mhead>"
"            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
""
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px;&#125;"
"    img &#123;border:0;&#125; a &#123; text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0;&#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px;&#125;"
"    #c&#123; position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px;&#125;"
"    #bla &#123; position: absolute; bottom: -5px;&#125;"
"    .hidden &#123; display:none;&#125;"
"            &lt;/style&gt;"
""
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;{prc}&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </munavail>"
"<mtail>"
"     &lt;/div&gt;"
"  &lt;div style=\"width: 100%; border: 1px solid black\" id=\"footer\"&gt;&lt;a href=\"http://www.tev.lt\"&gt;Parinktys2&lt;/a&gt;&lt;/div&gt;"
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif


#if FALSE // prodgrp(tado).xml 2012.06.08

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Unavailable</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<file size=\"2977\" date=\"2012.06.08\">http://images.tevukas.lt/small_un/978-609-433-026-1_un.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Buhalterinės apskaitos pagrindai</appname>"
"<file size=\"4453\" date=\"2012.06.08\">http://images.tevukas.lt/small_un/9955-680-38-5_un.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<lic>71G1-344L-4622</lic>"
"<setup size=\"32380133\">http://siuntiniai.tev.lt/file.php?file=lentyna_pp11-12_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3184\" date=\"2011.08.10\">http://images.tevukas.lt/small/978-609-433-040-7.gif</file>"
"<file size=\"2346\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/978-609-433-040-7_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Available</status>"
"<appname>Matematika Tau plius. 7 klasė. I dalis</appname>"
"<lic>9789-2ER9-R25R</lic>"
"<setup size=\"37051908\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius71_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4336\" date=\"2009.07.01\">http://images.tevukas.lt/small/978-9955-879-65-7.gif</file>"
"<file size=\"2724\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/978-9955-879-65-7_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>"
"<lic>73RE-9AAE-U28E</lic>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS52_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3867\" date=\"2005.09.05\">http://images.tevukas.lt/small/9955-491-99-X.gif</file>"
"<file size=\"2139\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>"
"<lic>945G-5URL-G426</lic>"
"<setup size=\"37366147\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius61_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4274\" date=\"2006.07.13\">http://images.tevukas.lt/small/9955-680-33-4.gif</file>"
"<file size=\"2826\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/9955-680-33-4_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Available</status>"
"<appname>Matematika Tau plius. 7 klasė. II dalis</appname>"
"<lic>1J5L-A9J9-R26A</lic>"
"<setup size=\"37452660\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius72_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4354\" date=\"2009.07.01\">http://images.tevukas.lt/small/978-9955-879-66-4.gif</file>"
"<file size=\"2850\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/978-9955-879-66-4_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 8 класс. 2 часть</appname>"
"<lic>3G28-1L24-27EE</lic>"
"<setup size=\"35814074\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau82_ru_setup_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3869\" date=\"2009.05.05\">http://images.tevukas.lt/small/978-9955-879-56-5.gif</file>"
"<file size=\"2947\" date=\"2012.06.08\">http://images.tevukas.lt/small_bw/978-9955-879-56-5_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"  <mhead>"
"            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
""
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px;&#125;"
"    img &#123;border:0;&#125; a &#123; text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0;&#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px;&#125;"
"    #c&#123; position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px;&#125;"
"    #bla &#123; position: absolute; bottom: -5px;&#125;"
"    .hidden &#123; display:none;&#125;"
"            &lt;/style&gt;"
""
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: relative; left: 40px; top: -110px;\" /&gt;&lt;/a&gt;&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </munavail>"
"<mtail>"
"     &lt;/div&gt;"
""
"&lt;div style=\'position:absolute; top: 0px; left:0px;\'&gt;&lt;a href=\'tux:///KpStart:Browse:http://lentyna.vadoveliai.lt\'&gt;Parduotuvė&lt;/a&gt;&lt;/div&gt;"
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif


#if FALSE // TRUE // Gintaro 2012.06.13 su kryžiukais

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Available</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>92AA-R33R-59E8</lic>"
// "<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_diegimas_lentynoje.exe</setup>"
"<setup size=\"95813345\">http://siuntiniai.tev.lt/updates/temp/SZIKL_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4779\" date=\"2010.02.17\">http://images.tevukas.lt/small/978-609-433-026-1.gif</file>"
"<file size=\"2681\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<file size=\"3368\" date=\"2012.06.13\">http://images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>"
"<lic>73RE-9AAE-U28E</lic>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS52_lt_diegimas_lentynoje.exe</setup>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/Plius52_lt_su_varztu_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3867\" date=\"2005.09.05\">http://images.tevukas.lt/small/9955-491-99-X.gif</file>"
"<file size=\"2139\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>"
"<lic>945G-5URL-G426</lic>"
// "<setup size=\"37369207\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius61_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS61_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4274\" date=\"2006.07.13\">http://images.tevukas.lt/small/9955-680-33-4.gif</file>"
"<file size=\"2826\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-680-33-4_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 8 класс. 2 часть. Konfig</appname>"
"<lic>3G28-1L24-27EE</lic>"
// "<setup size=\"35814074\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau82_ru_setup_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/TAU82_RU_setup_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3869\" date=\"2009.05.05\">http://images.tevukas.lt/small/978-9955-879-56-5.gif</file>"
"<file size=\"2947\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-9955-879-56-5_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"  <mhead>"
"            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
""
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px;&#125;"
"    img &#123;border:0;&#125; a &#123; text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0;&#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px;&#125;"
"    #c&#123; position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px;&#125;"
"    #bla &#123; position: absolute; bottom: -5px;&#125;"
"    .hidden &#123; display:none;&#125;"
"    a.menu &#123;color: black;&#125;"
"            &lt;/style&gt;"
""
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: relative; left: 40px; top: -110px;\" /&gt;&lt;/a&gt;&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </munavail>"
"<mtail>"
"   &lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve' class='menu'&gt;Parduotuvė&lt;/a&gt;&lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:Logoff:' class='menu'&gt;Logout&lt;/a&gt;&lt;/div&gt;"
""
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif


#if FALSE // TRUE // Gintaras 2012.06.22

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Free</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>92AA-R33R-59E8</lic>"
"<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4779\" date=\"2010.02.17\">http://images.tevukas.lt/small/978-609-433-026-1.gif</file>"
"<file size=\"2681\" date=\"2012.06.22\">http://images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<file size=\"3368\" date=\"2012.06.22\">http://images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>"
"<file size=\"2142\" date=\"2012.06.22\">http://images.tevukas.lt/small_un/9955-491-99-X_un.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>"
"<file size=\"3904\" date=\"2012.06.22\">http://images.tevukas.lt/small_un/9955-680-33-4_un.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 8 класс. 2 часть</appname>"
"<lic>3G28-1L24-27EE</lic>"
// "<setup size=\"35814074\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau82_ru_setup_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/TAU82_RU_setup_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3869\" date=\"2009.05.05\">http://images.tevukas.lt/small/978-9955-879-56-5.gif</file>"
"<file size=\"2947\" date=\"2012.06.22\">http://images.tevukas.lt/small_bw/978-9955-879-56-5_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"  <mhead>"
"            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
""
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px;&#125;"
"    img &#123;border:0;&#125; a &#123; text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0;&#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px;&#125;"
"    #c&#123; position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px;&#125;"
"    #bla &#123; position: absolute; bottom: -5px;&#125;"
"    .hidden &#123; display:none;&#125;"
"    a.menu &#123;color: black;&#125;"
"            &lt;/style&gt;"
""
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </munavail>"
"<mtail>"
"   &lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve' class='menu'&gt;Parduotuvė&lt;/a&gt;&lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:Logoff:' class='menu'&gt;logout&lt;/a&gt;&lt;/div&gt;"
""
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif



#if FALSE // TRUE // Gintaro JS 2012.07.24

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Available</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>92AA-R33R-59E8</lic>"
// "<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_diegimas_lentynoje.exe</setup>"
"<setup size=\"95813345\">http://siuntiniai.tev.lt/updates/temp/SZIKL_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4779\" date=\"2010.02.17\">http://images.tevukas.lt/small/978-609-433-026-1.gif</file>"
"<file size=\"2681\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<file size=\"3368\" date=\"2012.06.13\">http://images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>"
"<lic>73RE-9AAE-U28E</lic>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS52_lt_diegimas_lentynoje.exe</setup>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/Plius52_lt_su_varztu_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3867\" date=\"2005.09.05\">http://images.tevukas.lt/small/9955-491-99-X.gif</file>"
"<file size=\"2139\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>"
"<lic>945G-5URL-G426</lic>"
// "<setup size=\"37369207\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius61_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS61_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4274\" date=\"2006.07.13\">http://images.tevukas.lt/small/9955-680-33-4.gif</file>"
"<file size=\"2826\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-680-33-4_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 8 класс. 2 часть. Konfig</appname>"
"<lic>3G28-1L24-27EE</lic>"
// "<setup size=\"35814074\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau82_ru_setup_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/TAU82_RU_setup_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3869\" date=\"2009.05.05\">http://images.tevukas.lt/small/978-9955-879-56-5.gif</file>"
"<file size=\"2947\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-9955-879-56-5_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"  <mhead>"
// "            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px; &#125;"
"    img &#123; border:0;} a { text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0; &#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px; &#125;"
"    #c &#123; position: relative; margin: 0px 0px 15px 0px; width: 85px; height: 120px; &#125;"
"    #bla &#123; position: absolute; bottom: -5px; &#125;"
"    .hidden &#123; display:none; &#125;"
"    a.menu &#123; color: black; &#125;"
"            &lt;/style&gt;"
""
"         &lt;script language=\"JavaScript\"&gt;"
"            &amp;lt; &amp;gt; &amp;amp; + &amp;amp;&amp;amp; ++ i++"
"            function rodyti() &#123; var dyvai = document.getElementsByName(\"admin\"); for (i = 0; dyvai.length > i; i = i + 1) &#123; dyvai[i].style.display = \"block\"; &#125; return; &#125;"
"            function test(arg) &#123; var as = document.getElementById(arg); as.style.color='red'; return; &#125;"
"            function moo() &#123; alert('aa'); return; &#125;"
"         &lt;/script&gt;"
""
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: relative; left: 40px; top: -110px;\" /&gt;&lt;/a&gt;&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </munavail>"
"<mtail>"
"   &lt;/div&gt;"
""
"&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve' class='menu'&gt;Parduotuvė&lt;/a&gt;&lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:Logoff:' class='menu'&gt;Logout&lt;/a&gt;&lt;/div&gt;"
"&lt;div style=\"position:absolute; top: 2px; left:170px; cursor: pointer; color: yellow;\" onclick=\"this.style.color='blue'; test('asdf');\" id=\"asdf\"&gt;asdad a asd a kva &lt;a href=\"tux:///KpStart:Browse:http://tev.lt/akcija/stuff.htm\"&gt;testinis&lt;/a&gt;&lt;/div&gt;"
"&lt;div style=\"position:absolute; top: 2px; left:370px; cursor: pointer; color: green;\" onclick=\"moo();\" &gt;kva &lt;a href=\"JavaScript:moo();\"&gt;moo&lt;/a&gt;"
"&lt;a href=\"JavaScript:alert('gugu');\"&gt;gugu&lt;/a&gt; &lt;a href=\"tux:///KpStart:Browse:http://tev.lt/akcija/StartGrp.htm\"&gt;i┼Īor─Ś&lt;/a&gt;&lt;/div&gt;"
""
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif


#if FALSE // TRUE // kintamųjų seivinimo bandymas 2012.07.25 // Start/StopRefresh bandymas 2012.07.31

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
"<pr>"
"<resp>KpReg-Ok</resp>"
"<file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
"<item>"
"<status>Available</status>"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>"
"<lic>92AA-R33R-59E8</lic>"
// "<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_diegimas_lentynoje.exe</setup>"
"<setup size=\"95813345\">http://siuntiniai.tev.lt/updates/temp/SZIKL_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4779\" date=\"2010.02.17\">http://images.tevukas.lt/small/978-609-433-026-1.gif</file>"
"<file size=\"2681\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Unavailable</status>"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>"
"<file size=\"3368\" date=\"2012.06.13\">http://images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>"
"<lic>73RE-9AAE-U28E</lic>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS52_lt_diegimas_lentynoje.exe</setup>"
// "<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/Plius52_lt_su_varztu_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3867\" date=\"2005.09.05\">http://images.tevukas.lt/small/9955-491-99-X.gif</file>"
"<file size=\"2139\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>"
"<lic>945G-5URL-G426</lic>"
// "<setup size=\"37369207\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius61_lt_diegimas_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/PLIUS61_lt_diegimas_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"4274\" date=\"2006.07.13\">http://images.tevukas.lt/small/9955-680-33-4.gif</file>"
"<file size=\"2826\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/9955-680-33-4_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"<item>"
"<status>Free</status>"
"<appname>Математика Тебе. 8 класс. 2 часть. Konfig</appname>"
"<lic>3G28-1L24-27EE</lic>"
// "<setup size=\"35814074\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau82_ru_setup_lentynoje.exe</setup>"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/updates/temp/TAU82_RU_setup_lentynoje.exe</setup>"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>"
"<file size=\"3869\" date=\"2009.05.05\">http://images.tevukas.lt/small/978-9955-879-56-5.gif</file>"
"<file size=\"2947\" date=\"2012.06.13\">http://images.tevukas.lt/small_bw/978-9955-879-56-5_bw.gif</file>"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>"
"<file size=\"201\" date=\"2012.06.06\">http://tev.lt/lentyna_inc/uninstall.gif</file>"
"</item>"
"  <mhead>"
// "            &lt;?xml version=\"1.0\" encoding=\"UTF-8\" ?&gt;"
"      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;"
"      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;"
"         &lt;head&gt;"
"            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;"
"            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;"
"            &lt;style&gt;"
"    body &#123; font-family: Georgia; &#125;"
"    img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;"
"    #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px; &#125;"
"    img &#123; border:0;} a { text-decoration: none; &#125;"
"    #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0; &#125;"
"    #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px; &#125;"
"    #c &#123; position: relative; margin: 0px 0px 15px 0px; width: 85px; height: 120px; &#125;"
"    #bla &#123; position: absolute; bottom: -5px; &#125;"
"    .hidden &#123; display:none; &#125;"
"    a.menu &#123; color: black; &#125;"
"            &lt;/style&gt;"
"         &lt;/head&gt;"
"         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
"            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
"            &lt;div id=\"container\"&gt;"
"            </mhead>"
"   <mitem>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: relative; left: 40px; top: -110px;\" /&gt;&lt;/a&gt;&lt;/div&gt;   </mitem>"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mwait>"
"   <mfree>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </mfree>"
"   <mpend>&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/a&gt;&lt;/div&gt;   </mpend>"
"   <munavail>&lt;div id=\"item\"&gt;"
"&lt;div id=\"c\"&gt;"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;"
"&lt;/div&gt;   </munavail>"
"<mtail>"
"   &lt;/div&gt;"
""
// "&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve' class='menu'&gt;Parduotuvė&lt;/a&gt;&lt;/div&gt;"
// "&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:SetVar:ManoKintamasis=reikšmė' class='menu'&gt;Išsaugoti&lt;/a&gt;&lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;a href='tux:///KpStart:StopRefresh:' class='menu'&gt;Stop&lt;/a&gt;&lt;/div&gt;"
// "&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:Logoff:' class='menu'&gt;Logout&lt;/a&gt;&lt;/div&gt;"
// "&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:GetVar:ManoKintamasis' class='menu'&gt;Atstatyti&lt;/a&gt;&lt;/div&gt;"
"&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:GetVar:user' class='menu'&gt;user&lt;/a&gt;&lt;/div&gt;"
// "&lt;div style='position:absolute; top: 2px; left:120px;'&gt;&lt;a href='tux:///KpStart:StartRefresh:' class='menu'&gt;Start&lt;/a&gt;&lt;/div&gt;"
""
"&lt;/body&gt;"
"&lt;/html&gt;</mtail>"
"</pr>"

#endif



#if FALSE // TRUE // failų kodavimo bandymas

"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
"<pr>\n"
"<resp>KpReg-Ok</resp>\n"
"<file size=\"1662\" date=\"2012.08.02\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/stilius.css</file>\n"
"<file size=\"236202\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/jquery-1.6.2.js</file>\n"
"<file size=\"8247\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/jquery.ui.core.js</file>\n"
"<file size=\"7014\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/jquery.ui.widget.js</file>\n"
"<file size=\"4294\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/jquery.ui.mouse.js</file>\n"
"<file size=\"39946\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/jquery.ui.sortable.js</file>\n"
"<file size=\"5277\" date=\"2012.08.03\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/lentyna.js</file>\n"
"<file size=\"246426\" date=\"2012.07.26\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/fonas722.gif</file>\n"
"<file size=\"1626\" date=\"2012.08.02\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/parduotuve.gif</file>\n"
"<file size=\"1693\" date=\"2012.08.02\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/tvarkyti.gif</file>\n"
"<file size=\"1584\" date=\"2012.08.02\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/atsijungti.gif</file><item>\n"
"<status>Unavailable</status>\n"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>\n"
"<file size=\"3368\" date=\"2012.08.07\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>\n"
"<lic>92AA-R33R-59E8</lic>\n"
"<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_lt_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"4779\" date=\"2010.02.17\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small/978-609-433-026-1.gif</file>\n"
"<file size=\"2681\" date=\"2012.08.07\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>\n"
"<lic>73RE-9AAE-U28E</lic>\n"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"3867\" date=\"2005.09.05\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small/9955-491-99-X.gif</file>\n"
"<file size=\"2139\" date=\"2012.08.07\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://serveri5.ll/lentyna/get_file.php?file=tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Unavailable</status>\n"
"<appname>Математика Тебе. 8 класс. 2 часть</appname>\n"
"<file size=\"3759\" date=\"2012.08.07\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small_un/978-9955-879-56-5_un.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Unavailable</status>\n"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>\n"
"<file size=\"3904\" date=\"2012.08.07\">http://serveri5.ll/lentyna/get_file.php?file=images.tevukas.lt/small_un/9955-680-33-4_un.gif</file>\n"
"</item>\n"
"  <mhead>\n"
"   &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;\n"
"&lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;\n"
"&lt;head&gt;\n"
"  &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;\n"
"  &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;\n"
"  &lt;link rel=\"stylesheet\" href=\"&#123;file&#125;\" type=\"text/css\" /&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"&lt;/head&gt;\n"
"&lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\" onload=\"init();\"&gt;\n"
"&lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"722\" height=\"722\"/&gt;\n"
"&lt;input type=\"hidden\" name=\"check_admin\" id=\"check_admin\"&gt;\n"
"&lt;input type=\"hidden\" name=\"order_list\" id=\"order_list\"&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:15px;\"&gt;&lt;a href=\"tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve\" class=\"menu\"&gt;&lt;img src=\"&#123;file&#125;\" title = \"Parduotuvė\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:101px; cursor: pointer;\" &gt;&lt;a href='JavaScript:administruoti();'&gt;&lt;img src=\"&#123;file&#125;\" title = \"Tvarkyti\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:640px;\"&gt;&lt;a href=\"tux:///KpStart:Logoff:\" class=\"menu\"&gt;&lt;img src=\"&#123;file&#125;\" title = \"Atsijungti\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:260px; font-size: 8px\" id=\"output\" &gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"container\"&gt;\n"
"&lt;ul id=\"sortable\"&gt;            </mhead>\n"
"   <mitem>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;\n"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\"&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\" onclick=\"end_admin();\"&gt;&lt;img src=\"&#123;file&#125;\" style=\"position:absolute; bottom: -15px; width: 70px; display:none; z-index:6\" name=\"admin\"&gt;&lt;/a&gt;\n"
"&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/div&gt;\n"
"&lt;/li&gt;   </mitem>\n"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/a&gt;&lt;/div&gt;   </mwait>\n"
"   <mfree>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\" onclick='var elementas=document.getElementById(\"&#123;appname&#125;\"); elementas.style.visible=\"\";'&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;\n"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" class='hidden' id='&#123;appname&#125;'/&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/div&gt;\n"
"&lt;/li&gt;   </mfree>\n"
"   <mpend>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/a&gt;&lt;/div&gt;&lt;/li&gt;   </mpend>\n"
"   <munavail>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;\n"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;div class='kill'&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/li&gt;   </munavail>\n"
"<mtail>\n"
"   &lt;/ul&gt;\n"
"&lt;/div&gt;\n"
"&lt;/body&gt;\n"
"&lt;/html&gt;</mtail>\n"
"</pr>\n"


#endif



#if FALSE // TRUE // terminuotų licencijų bandymas


"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
"<pr>\n"
"<resp>KpReg-Ok</resp>\n"
"<file size=\"1662\" date=\"2012.08.02\">http://tev.lt/lentyna_inc/stilius.css</file>\n"
"<file size=\"236202\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/jquery-1.6.2.js</file>\n"
"<file size=\"8247\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/jquery.ui.core.js</file>\n"
"<file size=\"7014\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/jquery.ui.widget.js</file>\n"
"<file size=\"4294\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/jquery.ui.mouse.js</file>\n"
"<file size=\"39946\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/jquery.ui.sortable.js</file>\n"
"<file size=\"5592\" date=\"2012.08.10\">http://tev.lt/lentyna_inc/lentyna.js</file>\n"
"<file size=\"246426\" date=\"2012.07.26\">http://tev.lt/lentyna_inc/fonas722.gif</file>\n"
"<file size=\"1626\" date=\"2012.08.02\">http://tev.lt/lentyna_inc/parduotuve.gif</file>\n"
"<file size=\"1693\" date=\"2012.08.02\">http://tev.lt/lentyna_inc/tvarkyti.gif</file>\n"
"<file size=\"1584\" date=\"2012.08.02\">http://tev.lt/lentyna_inc/atsijungti.gif</file><item>\n"
"<status>Unavailable</status>\n"
"<appname>Šiuolaikiškas žvilgsnis į programavimą. Pasirenkamasis informacinių technologijų kursas XI–XII klasėms. C&#43;&#43;. Parsisiųsdinama skaitmeninė vadovėlio versija</appname>\n"
"<file size=\"3368\" date=\"2012.08.14\">http://images.tevukas.lt/small_un/978-609-433-040-7_un.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Šiuolaikiškas žvilgsnis į kompiuterinę leidybą</appname>\n"
"<lic>92AA-R33R-59E8</lic>\n"
"<setup size=\"95757427\">http://siuntiniai.tev.lt/file.php?file=lentyna_szikl_lt_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"4779\" date=\"2010.02.17\">http://images.tevukas.lt/small/978-609-433-026-1.gif</file>\n"
"<file size=\"2681\" date=\"2012.08.14\">http://images.tevukas.lt/small_bw/978-609-433-026-1_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Matematika tau 11. Bendrasis kursas</appname>\n"
"<lic>2869-62R9-52LR</lic>\n"
"<setup size=\"46779996\">http://siuntiniai.tev.lt/file.php?file=lentyna_tau11bk_lt_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"3952\" date=\"2011.04.21\">http://images.tevukas.lt/small/978-609-433-039-1.gif</file>\n"
"<file size=\"2449\" date=\"2012.08.14\">http://images.tevukas.lt/small_bw/978-609-433-039-1_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Matematika Tau plius. 5 klasė. II dalis</appname>\n"
"<lic>73RE-9AAE-U28E</lic>\n"
"<setup size=\"37216497\">http://siuntiniai.tev.lt/file.php?file=lentyna_plius52_lt_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"3867\" date=\"2005.09.05\">http://images.tevukas.lt/small/9955-491-99-X.gif</file>\n"
"<file size=\"2139\" date=\"2012.08.14\">http://images.tevukas.lt/small_bw/9955-491-99-X_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Unavailable</status>\n"
"<appname>Математика Тебе. 8 класс. 2 часть</appname>\n"
"<file size=\"3759\" date=\"2012.08.14\">http://images.tevukas.lt/small_un/978-9955-879-56-5_un.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Unavailable</status>\n"
"<appname>Matematika Tau plius. 6 klasė. I dalis</appname>\n"
"<file size=\"3904\" date=\"2012.08.14\">http://images.tevukas.lt/small_un/9955-680-33-4_un.gif</file>\n"
"</item>\n"
"<item>\n"
"<status>Free</status>\n"
"<appname>Literatūra 11 klasei. Chrestomatija 2 dalis</appname>\n"
"<lic>9AR4-8EEE-164R</lic>\n"
// "<setup size=\"24031572\">http://siuntiniai.tev.lt/file.php?file=lentyna_ch112_lt_diegimas_lentynoje.exe</setup>\n"
"<setup size=\"24031572\">http://siuntiniai.tev.lt/updates/temp/Ch112_diegimas_lentynoje.exe</setup>\n"
"<launch>tux:///KpStart:StartAndClose:&#123;app&#125;\\XFS.exe</launch>\n"
"<file size=\"5152\" date=\"2012.06.13\">http://images.tevukas.lt/small/978-609-425-057-6.gif</file>\n"
"<file size=\"2992\" date=\"2012.08.14\">http://images.tevukas.lt/small_bw/978-609-425-057-6_bw.gif</file>\n"
"<file size=\"1557\" date=\"2012.05.09\">http://tev.lt/lentyna_inc/spinner.gif</file>\n"
"<file size=\"554\" date=\"2012.07.27\">http://tev.lt/lentyna_inc/delete.gif</file>\n"
"</item>\n"
"  <mhead>\n"
"   &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;\n"
"&lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;\n"
"&lt;head&gt;\n"
"  &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;\n"
"  &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;\n"
"  &lt;link rel=\"stylesheet\" href=\"&#123;file&#125;\" type=\"text/css\" /&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"  &lt;script src=\"&#123;file&#125;\"&gt;&lt;/script&gt;\n"
"&lt;/head&gt;\n"
"&lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\" onload=\"init();\"&gt;\n"
"&lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"722\" height=\"722\"/&gt;\n"
"&lt;input type=\"hidden\" name=\"check_admin\" id=\"check_admin\"&gt;\n"
"&lt;input type=\"hidden\" name=\"order_list\" id=\"order_list\"&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:15px;\"&gt;&lt;a href=\"tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve\" class=\"menu\"&gt;&lt;img src=\"&#123;file&#125;\" title = \"Parduotuvė\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:101px; cursor: pointer;\" &gt;&lt;a href='JavaScript:administruoti();'&gt;&lt;img src=\"&#123;file&#125;\" title = \"Tvarkyti\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:640px;\"&gt;&lt;a href=\"tux:///KpStart:Logoff:\" class=\"menu\"&gt;&lt;img src=\"&#123;file&#125;\" title = \"Atsijungti\" border=\"0\" /&gt;&lt;/a&gt;&lt;/div&gt;\n"
"&lt;div style=\"position:absolute; top: 5px; left:260px; font-size: 8px\" id=\"output\" &gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"container\"&gt;\n"
"&lt;ul id=\"sortable\"&gt;            </mhead>\n"
"   <mitem>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;a href=\"&#123;launch&#125;\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/a&gt;\n"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\"&gt;&lt;a href=\"tux:///KpStart:Uninst:&#123;appname&#125;\" onclick=\"end_admin();\"&gt;&lt;img src=\"&#123;file&#125;\" style=\"position:absolute; bottom: -15px; width: 70px; display:none; z-index:6\" name=\"admin\"&gt;&lt;/a&gt;\n"
"&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/div&gt;\n"
"&lt;/li&gt;   </mitem>\n"
"   <mwait>&lt;div id=\"item\"&gt;&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/a&gt;&lt;/div&gt;   </mwait>\n"
"   <mfree>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;a href=\"tux:///KpStart:Download:&#123;appname&#125;\" onclick='var elementas=document.getElementById(\"&#123;appname&#125;\"); elementas.style.visible=\"\";'&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" /&gt;&lt;/a&gt;\n"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" class='hidden' id='&#123;appname&#125;'/&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/div&gt;\n"
"&lt;/li&gt;   </mfree>\n"
"   <mpend>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;&lt;div name=\"uzdanga\" style=\"width: 85px; height: 120px; background-color: black; position: absolute; top: 0px; z-index:5; opacity:0;\" title=\"&#123;appname&#125;\"&gt;&amp;nbsp;&lt;/div&gt;\n"
"&lt;div id=\"item\"&gt;&lt;a href=\"#\"&gt;\n"
"&lt;div id=\"c\"&gt;&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" class=\"hidden\" /&gt;\n"
"&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"  /&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\" style=\"position: absolute; left: 20px; top: 19px;\" /&gt;&lt;div style=\"background: red; width: 56px; height: 3px; position: absolute; margin-top: 1px;\"&gt;&lt;div style=\"background: green; width: &#123;prc&#125;%; height: 3px;\"&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/a&gt;&lt;/div&gt;&lt;/li&gt;   </mpend>\n"
"   <munavail>&lt;li class=\"ui-state-default\" name=\"itemas\"&gt;\n"
"&lt;div id=\"item\"&gt;\n"
"&lt;div id=\"c\"&gt;\n"
"&lt;div id=\"bla\"&gt;&lt;img src=\"&#123;file&#125;\" title=\"&#123;appname&#125;\"/&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;div class='kill'&gt;&lt;/div&gt;&lt;/div&gt;\n"
"&lt;/li&gt;   </munavail>\n"
"<mtail>\n"
"   &lt;/ul&gt;\n"
"&lt;/div&gt;\n"
"&lt;/body&gt;\n"
"&lt;/html&gt;</mtail>\n"
"</pr>\n"


#endif


};

#endif


#ifdef KPST_PRODGRP_STATIC_CFG
#if FALSE
unsigned char lpszUpdCfgDefLzdshp[] =
{
   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
   "<pr>\r\n"
   "   <resp>KpReg-Ok</resp>\r\n"
   "   <item>\r\n"
   "      <appname>WinLED v5.0</appname>\r\n"
   "      <updname>pilnas atnaujinimas v5.05e.21</updname>\r\n"
   "      <setup size=\"58630829\">http://siuntiniai.tev.lt/updates/WinLED_v5.0_visas_atnaujinimas.exe</setup>\r\n"
   "   </item>\r\n"
   "</pr>\r\n"
};
unsigned char lpszUpdCfgDefGGG11_12[] =
{
   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
   "<pr>\r\n"
   "   <resp>KpReg-Ok</resp>\r\n"
   "   <item>\r\n"
   "      <appname>Šaltinių knyga „GAUBLYS. GAMTINĖ GEOGRAFIJA 11-12 kl.“</appname>\r\n"
   "      <updname>pilnas atnaujinimas 11.2.3</updname>\r\n"
// "      <setup size=\"470280903\">http://siuntiniai.tev.lt/updates/GGG11-12_pilnas_atnaujinimas.exe</setup>\r\n"
   "      <setup size=\"2049781\">http://siuntiniai.tev.lt/updates/DS5_11.1.3_atmintuko_atnaujinimas.exe</setup>\r\n"
   "   </item>\r\n"
   "</pr>\r\n"
};
#endif
#endif


unsigned char lpszStartGrpCfgEmpty[] =
{
   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
   "<pr>\r\n"
   "   <resp>KpReg-Ok</resp>\r\n"
   "\r\n"
   "   <file size=\"205356\" date=\"2011.10.05\">http://tev.lt/lentyna_inc/fonas.gif</file>"
   "\r\n"
   "   <mhead>\r\n"
   "      &lt;?xml version=\"1.0\" encoding=&quot;UTF-8\"?&gt;\r\n" // "U duoda umlautą
   "      &lt;!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\"&gt;\r\n"
   "      &lt;html xmlns=\"http://www.w3.org/1999/xhtml\"&gt;\r\n"
   "         &lt;head&gt;\r\n"
   "            &lt;meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/&gt;\r\n"
   "            &lt;title&gt;Vadovėlių komplektas&lt;/title&gt;\r\n"
   "            &lt;style&gt;\r\n"
   "              body &#123; font-family: Georgia; &#125;\r\n"
   "              #container &#123; z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px; &#125;\r\n"
   "              #footer &#123; position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0; &#125;\r\n"
   "              #item &#123; float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px; &#125;\r\n"
   "              img#background &#123; z-index: -1; position: absolute; left:0; top:0; color: white; &#125;\r\n"
   "              img &#123;border:0; &#125;\r\n"
   "              a &#123; text-decoration: none; &#125;\r\n"
   "              a.menu &#123;color: black; &#125;\r\n"
   "              #c&#123; position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px; &#125;\r\n"
   "              #bla &#123; position: absolute; bottom: -5px; &#125;\r\n"
   "              .hidden &#123; display:none; &#125;\r\n"
   "            &lt;/style&gt;\r\n"
   "         &lt;/head&gt;\r\n"
   "         &lt;body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\"&gt;"
   "            &lt;img id=\"background\" src=\"&#123;file&#125;\" width=\"750\" height=\"570\"/&gt;"
   "            &lt;div style='position:absolute; top: 2px; left:20px;'&gt;&lt;span class='menu'&gt;Palaukite...&lt;/span&gt;&lt;/div&gt;"
   "            &lt;div style='position:absolute; top: 2px; left:400px;'&gt;&lt;a href='tux:///KpStart:Login:' class='menu'&gt;[ Keisti vartotoją ]&lt;/a&gt;&lt;/div&gt;"
   "            &lt;div style='position:absolute; top: 2px; left:540px;'&gt;&lt;a href='tux:///KpStart:Logoff:' class='menu'&gt;[ Atsijungti ]&lt;/a&gt;&lt;/div&gt;"
   "   </mhead>\r\n"
   "   <mitem>\r\n"
   "   </mitem>\r\n"
   "   <mtail>\r\n"
   "         &lt;/body&gt;\r\n"
   "      &lt;/html&gt;\r\n"
   "   </mtail>\r\n"
   "</pr>\r\n"
};


unsigned char lpszStartGrpLoginHtml[] =
{
#if FALSE
   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n" // "<?xml version=\"1.0\" encoding=&quot;UTF-8\"?>\r\n" // "U duoda umlautą
   "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\r\n"
   "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
   "   <head>\r\n"
   "      <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>\r\n"
   "      <title>Prisijungimas</title>\r\n"
   "      <style>\r\n"
   "        body { font-family: Georgia; }\r\n"
   "        #container { z-index: -1; position: absolute; left:20px; top:20px; width: 700px; height: 530px; }\r\n"
   "        #footer { position: fixed; width: 100%; height: 100px; top: auto; right: 0; bottom: 0; left: 0; }\r\n"
   "        #item { float:left; margin: 0px 5px 15px 5px; width: 85px; height: 120px; }\r\n"
   "        img#background { z-index: -1; position: absolute; left:0; top:0; color: white; }\r\n"
   "        img {border:0; }\r\n"
   "        a { text-decoration: none; }\r\n"
   "        a.menu {color: black;}\r\n"
   "        #c{ position: relative;  margin: 0px 0px 15px 0px; width: 85px; height: 120px;}\r\n"
   "        #bla { position: absolute; bottom: -5px;}\r\n"
   "        .hidden { display:none;}\r\n"
   "        td.w { width: 70px }\r\n"
   "      </style>\r\n"
   "      <script language=\"JavaScript\">\r\n"
   "         function procbut(arg)\r\n"
   "         {\r\n"
   "            document.Loginas.cmd.value = arg;\r\n"
   "            document.Loginas.submit();\r\n"
   "         }\r\n"
   "         function GoCliSys()\r\n"
   "         {\r\n"
// "            window.navigate(\"http://lentyna.vadoveliai.lt/demo_parduotuve\");\r\n"
// "            window.open(\"tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve\");\r\n"
   "            window.location.href = \"tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve\";\r\n"
   "         }\r\n"
   "      </script>\r\n"
   "   </head>\r\n"
   "   <body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\">\r\n"
   "      <img id=\"background\" src=\"tux:///DAT0/StartGrp_fonas.gif\" width=\"750\" height=\"570\"/>\r\n"
   "      <div style=\"position: absolute; left: 220; top: 190;\">\r\n"
   "         <form action=\"tux:///KpStart:DoLogin:\" name=\"Loginas\" method=\"get\" enctype=\"multipart/form-data\">\r\n"
   "            <input name=\"cmd\" type=\"hidden\" value=\"\"/>\r\n"
   "            <table><tbody>\r\n"
   "               <tr>\r\n"
   "                  <td><span>Vardas:</span></td>\r\n"
   "                  <td colspan=\"2\" align=\"center\"><input name=\"user\" type=\"text\" value=\"\"/></td>\r\n"
   "                  <td class=\"w\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td><span>Slaptažodis:</span></td>\r\n"
   "                  <td colspan=\"2\" align=\"center\"><input name=\"pwd\" type=\"password\" value=\"\"/></td>\r\n"
   "                  <td>&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td>&nbsp;</td>\r\n"
   "                  <td align=\"right\"><input type=\"button\" value=\"Prisijungti\" class=\"button\" onclick=\"procbut(1)\"/></td>\r\n"
   "                  <td align=\"left\"><input type=\"button\" value=\"Atšaukti\" class=\"button\" onclick=\"procbut(2)\"/></td>\r\n"
   "                  <td>&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td colspan=\"4\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td colspan=\"4\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td colspan=\"4\" align=\"center\"><input type=\"button\" value=\"Dar nesu klientų sistemos vartotojas\" class=\"button\" onclick=\"GoCliSys()\"/></td>\r\n"
   "               </tr>\r\n"
   "            </tbody></table>\r\n"
   "         </form>\r\n"
   "      </div>\r\n"
   "   </body>\r\n"
   "</html>\r\n"
#else
// Gintaro 2012.10.30
   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
   "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"DTD/xhtml1-strict.dtd\">\r\n"
   "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
   "   <head>\r\n"
   "      <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>\r\n"
   "      <title>Prisijungimas</title>\r\n"
   "      <link rel=\"stylesheet\" href=\"http://tev.lt/lentyna_inc/stilius.css\" type=\"text/css\" />\r\n"
   "      <style>\r\n"
   "        td.w { width: 70px }\r\n"
   "      </style>\r\n"
   "      <script language=\"JavaScript\">\r\n"
   "         function procbut(arg)\r\n"
   "         {\r\n"
   "            document.Loginas.cmd.value = arg;\r\n"
   "            document.Loginas.submit();\r\n"
   "         }\r\n"
   "         function keyapdorojimas1(event) {\r\n"
   "           if (event.keyCode == 13)\r\n"
   "           if (document.Loginas.pwd.value.length) procbut(1);\r\n"
   "           else document.Loginas.pwd.focus();\r\n"
   "         }\r\n"
   "         function keyapdorojimas2(event) {\r\n"
   "           if (event.keyCode == 13)\r\n"
   "           if (document.Loginas.user.value.length) procbut(1);\r\n"
   "           else document.Loginas.user.focus();\r\n"
   "           return;\r\n"
   "         }\r\n"
   "         function klientu_sistema()\r\n"
   "         {\r\n"
   "            window.location.href = \"tux:///KpStart:Browse:http://lentyna.vadoveliai.lt/demo_parduotuve\";\r\n"
   "         }\r\n"
   "      </script>\r\n"
   "   </head>\r\n"
   "   <body bottommargin=\"0\" leftmargin=\"0\" marginheight=\"0\" marginwidth=\"0\" rightmargin=\"0\" topmargin=\"0\" onload=\"document.Loginas.user.focus();\">\r\n"
   "      <img id=\"background\" src=\"http://tev.lt/lentyna_inc/fonas.gif\" width=\"722\" height=\"722\"/>\r\n"
   "      <div style=\"position: absolute; left: 225; top: 240;\">\r\n"
   "         <form action=\"tux:///KpStart:DoLogin:\" name=\"Loginas\" method=\"get\" enctype=\"multipart/form-data\">\r\n"
   "            <input name=\"cmd\" type=\"hidden\" value=\"\"/>\r\n"
   "            <table><tbody>\r\n"
   "               <tr>\r\n"
   "                  <td><span>Vardas:</span></td>\r\n"
   "                  <td colspan=\"2\" align=\"center\"><input name=\"user\" type=\"text\" value=\"\" onkeydown=\"keyapdorojimas1(event);\" /></td>\r\n"
   "                  <td class=\"w\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td><span>Slaptažodis:</span></td>\r\n"
   "                  <td colspan=\"2\" align=\"center\"><input name=\"pwd\" type=\"password\" value=\"\" onkeydown=\"keyapdorojimas2(event);\" /></td>\r\n"
   "                  <td class=\"w\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td>&nbsp;</td>\r\n"
   "                  <td align=\"right\"><input type=\"button\" value=\"Prisijungti\" class=\"button\" onclick=\"procbut(1)\"/></td>\r\n"
   "                  <td align=\"left\"><input type=\"button\" value=\"Atšaukti\" class=\"button\" onclick=\"procbut(2)\"/></td>\r\n"
   "                  <td class=\"w\">&nbsp;</td>\r\n"
   "               </tr>\r\n"
   "               <tr>\r\n"
   "                  <td colspan=\"4\" align=\"center\"><input type=\"button\" value=\"Dar nesu klientų sistemos vartotojas\" class=\"button\" onclick=\"klientu_sistema()\"/></td>\r\n"
   "               </tr>\r\n"
   "            </tbody></table>\r\n"
   "         </form>\r\n"
   "      </div>\r\n"
   "   </body>\r\n"
   "</html>\r\n"
#endif
};


// -----------------------------------------
const KpChar KpstGrpMacroApp[] = {'{', 'a', 'p', 'p', '}', C_Nul};
const KpChar KpstGrpMacroAppname[] = {'{', 'a', 'p', 'p', 'n', 'a', 'm', 'e', '}', C_Nul};
const KpChar KpstGrpMacroLaunch[] = {'{', 'l', 'a', 'u', 'n', 'c', 'h', '}', C_Nul};
const KpChar KpstGrpMacroFile[] = {'{', 'f', 'i', 'l', 'e', '}', C_Nul};
const KpChar KpstGrpMacroMpar[] = {'{', 'm', 'p', 'a', 'r', '}', C_Nul};
const KpChar KpstGrpMacroSetup[] = {'{', 's', 'e', 't', 'u', 'p', '}', C_Nul};
const KpChar KpstGrpMacroSetupSize[] = {'{', 's', 'e', 't', 'u', 'p', 's', 'i', 'z', 'e', '}', C_Nul};
const KpChar KpstGrpMacroLic[] = {'{', 'l', 'i', 'c', '}', C_Nul};
const KpChar KpstGrpMacroPrc[] = {'{', 'p', 'r', 'c', '}', C_Nul};
const KpChar KpstGrpMacroTemp[] = {'{', 't', 'e', 'm', 'p', '}', C_Nul};

const KpChar KpstGrpPathPrefix[] = {'t', 'u', 'x', ':', '/', '/', '/', 'K', 'p', 'S', 't', 'a', 'r', 't', ':', C_Nul};

// -----------------------------------------
const unsigned char *lpszaStartSelKwds[NumOfStartSelKwdIxs_16 + 1] =
{
   (const unsigned char *)"MainBackground",
   (const unsigned char *)"Palette",
   (const unsigned char *)"ButtonImage",
   (const unsigned char *)"ButtonHighlight",
   (const unsigned char *)"ButtonSelected",
   (const unsigned char *)"ButtonText",
   (const unsigned char *)"StopRefresh",
   (const unsigned char *)"StartRefresh",
   (const unsigned char *)"StartAndClose",
   (const unsigned char *)"StartAdmin",
   (const unsigned char *)"Start",
   (const unsigned char *)"Open",
   (const unsigned char *)"EditUserData",
   (const unsigned char *)"SaveCopy",
   (const unsigned char *)"RestoreCopy",
   (const unsigned char *)"Restore",
   (const unsigned char *)"HorMargin",
   (const unsigned char *)"VertMargin",
   (const unsigned char *)"ButMargin",
   (const unsigned char *)"DiagMsg",
   (const unsigned char *)"Options",
   (const unsigned char *)"Logoff",
   (const unsigned char *)"Refresh",
   (const unsigned char *)"DownLoad",
   (const unsigned char *)"Uninst",
   (const unsigned char *)"Browse",
   (const unsigned char *)"Return",
   (const unsigned char *)"Login",
   (const unsigned char *)"DoLogin",
   (const unsigned char *)"SetVar",
   (const unsigned char *)"GetVar",

   NULL
};


// -----------------------------------------
HRESULT KpStApp::ProcessGrp(bool bMainThread)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_pGrpKpPubDlg != NULL, E_POINTER, null, True);

// asinchroniškai nespėja, nedarom, nes po to ir taip bus kitaip
   if(SUCCEEDED(retc)) retc = GrpSvrRequest(bMainThread, False); // http://www.tev.lt/prodgrp.php --> m_lpszGrpCfgBuf[]
// if(SUCCEEDED(retc)) retc = GrpSvrRequestAsyn(True); // http://www.tev.lt/prodgrp.php --> m_lpszGrpCfgBuf[]

   if(SUCCEEDED(retc)) retc = ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode

   if(SUCCEEDED(retc)) retc = CheckGrpResponce(); //analizuojam, ar KpReg-Ok
// PutLogMessage_("KpStApp::ProcessGrp() %x %x", retc, KP_E_CANCEL);
// if(FAILED(retc)) if(m_lpszGrpCfgBuf) m_lpszGrpCfgBuf[0] = Nul;

bool logoff = False;
   if(/* SUCCEEDED(retc) */ m_pGrpKpPubDlg != NULL) logoff = m_pGrpKpPubDlg->m_bLogoff;

   if(SUCCEEDED(retc))
   {
      retc = SaveGrpCfg(); // rašom m_lpszGrpCfgBuf[] į failą StartGrp.cfg

// išsaugojam slaptažodį būsimam galimam off-line loginui
int prod_ver = 0;
      if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
unsigned char pwd_enc[2 * TV_TAG_LEN + 1];
      if(SUCCEEDED(retc)) retc = GetIniUserPwdEnc(KPST_GRP_PWD_CRYPT_CODE, pwd_enc);
      if(SUCCEEDED(retc)) /* retc = */ SetProdVerRegVariableStr(pwd_enc, prod_ver, KPST_PRODVER_REG_KEY_LastUser);
   }
   else switch(retc)
   {
   case KP_E_CANCEL:  // atsakymas KpReg-NoNews – atstatom buvusį meniu iš failo, retc kol kas paliekam
   /* retc = */ LoadGrpCfg(); // skaitom failą StartGrp.cfg į m_lpszGrpCfgBuf[]
   /* if(SUCCEEDED(retc)) retc = */ ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode
//    retc = KP_E_CANCEL;
      break;
   case KP_E_ACCESS_DENIED: // registracija atmesta
      logoff = True; // – išloginam
   /* retc = */ GrpLogoff();
      if(bMainThread) break; // pagrindiniam threade iškviesta po logino – reikia tiesiog grįžti atgal į logino langą
   case KP_E_REFUSED:
   case KP_E_NO_CONN:
   case KP_E_TRANS_ERR:
   case KP_E_TIMEOUT:
   default: // gesinam bet kokią klaidą
      retc = LoadGrpCfg(); // skaitom failą StartGrp.cfg į m_lpszGrpCfgBuf[]
      if(SUCCEEDED(retc)) retc = ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode
      break;
   }

   if(SUCCEEDED(retc)) m_pGrpKpPubDlg->m_bLogoff = logoff;

// -------------------
// if(SUCCEEDED(retc)) m_pGrpCfgNode->TraceContents((const unsigned char *)"");

// ------------------- ar reikia klausinėti apie parsisiuntimą?
   KP_DELETE(m_aGrpDownLoads);

#if FALSE // dabar siunčiam po pilkos ikonėlės paspaudimo
bool chk_updates = True;
bool lic_flash = False;
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetTestUpdates(&chk_updates);
   if(SUCCEEDED(retc)) retc = GetIniLicFlash(&lic_flash);
   if((chk_updates || lic_flash) && SUCCEEDED(retc))
   {

// ------------------- selektinam parsisiunčiamų setup failų sąrašą; ExtractGrpDownLoads() – viduj
      if(SUCCEEDED(retc))
      {
         retc = SelectSetupDownload();
         if(retc == KP_E_CANCEL)
         {
// papildomus failus (paveiksliukus) vis tiek siųsim
            retc = S_OK;
// tik reikia nuimti visus varniukių pažymėjimus nuo setupų
            if(m_aGrpDownLoads != NULL) retc = m_aGrpDownLoads->Deselect();
         }
      }
#else
   {
#endif

// ------------------- pridedam paprastus failus prie parsisiuntimo sąrašo
      if(SUCCEEDED(retc)) retc = AppendGrpDownLoads(m_pGrpCfgNode);
// TraceGrpDownLoads();

// ------------------- ar yra ką siųsti?
      if((m_aGrpDownLoads != NULL) && SUCCEEDED(retc))
      {

// ------------------- siunčiam/diegiam pažymėtus failus
         if(SUCCEEDED(retc)) retc = GrpDownLoad(bMainThread);

      } // if((m_aGrpDownLoads != NULL) && SUCCEEDED(retc))

   } // if(chk_updates && SUCCEEDED(retc))

   KP_DELETE(m_aGrpDownLoads);

// ------------------
   if(retc == KP_E_CANCEL) retc = S_OK;

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::RefreshGrpMenu(bool bReload)
{
HRESULT retc = S_OK;

   if((m_pGrpKpPubDlg != NULL) && // jei m_pGrpKpPubDlg == NULL – čia kpstisvr.bin, meniu nėra
      m_bGrpRefreshFlg)
   {
      if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
         m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();

// --------------------
      if(bReload && SUCCEEDED(retc)) retc = ProcessGrp(False);

// ------------------------------- iš cfg generuojam meniu
      if(SUCCEEDED(retc)) retc = GenStartMenu(True);

// --------------------
      if(SUCCEEDED(retc))
      {
// nustatyti galimai pasikeitusį m_pGrpKpPubDlg->m_pKpFileSys->m_lpszCurSearchKwd

//       if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL) m_pGrpKpPubDlg->m_pKpFileSys->m_lCurEntryId = (-1L);
//       if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL) // if(m_pGrpKpPubDlg->m_pKpFileSys->m_lThreadId == 0)
//          if(SUCCEEDED(retc)) retc = m_pGrpKpPubDlg->m_pKpFileSys->SearchForEntry(theKpStAppPtr->m_pGrpKpPubDlg, KPST_GRP_MENU_FNAME);

         if(SUCCEEDED(retc)) if(m_pGrpKpPubDlg != NULL) m_pGrpKpPubDlg->m_bRefresh = True;
      }

// --------------------------
      if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
         m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

   } // if(m_pGrpKpPubDlg != NULL)

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SwitchGrpMenuRefreshing(bool bRefreshFlg)
{
HRESULT retc = S_OK;

   if(!bRefreshFlg)
   {
// laukiam, kol pasibaigs dabar vykstantis ekrano atnaujinimas
      if(SUCCEEDED(retc)) if(m_pGrpKpPubDlg != NULL)
      {
         m_pGrpKpPubDlg->m_bRefresh = False;
         while(m_pGrpKpPubDlg->m_bRefreshing) retc = KpSleep(100);
      }
   }

   m_bGrpRefreshGlobalFlg = m_bGrpRefreshFlg = bRefreshFlg;

return(retc);
}


// -----------------------------------------
// static int refresh_cnt = 0;
DWORD WINAPI ProcessGrpThreadProc(LPVOID /* lpParameter */)
{
HRESULT retc = S_OK;

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_NO_FILE, null, True);
   KP_ASSERT(theKpStAppPtr->m_pGrpKpPubDlg != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(theKpStAppPtr->m_pGrpKpPubDlg->m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) theKpStAppPtr->m_lGrpRefreshThreadId = GetCurrentThreadId();

   if(SUCCEEDED(retc)) retc = KpSleep(5000); // laukiam, kol atsidarys visi langai

   while(SUCCEEDED(retc)) // periodiškai atnaujinam meniu
   {
      if(SUCCEEDED(retc)) if(theKpStAppPtr == NULL) retc = E_POINTER;
      if(SUCCEEDED(retc)) if(theKpStAppPtr->m_pGrpKpPubDlg == NULL) retc = E_POINTER;
      if(SUCCEEDED(retc)) if(theKpStAppPtr->m_pGrpKpPubDlg->m_pKpFileSys == NULL) retc = E_POINTER;

      if(SUCCEEDED(retc)) if(theKpStAppPtr->m_GrpDownLoadThreadList == NULL) // jei šiuo metu downloadinama – neatnaujinti
         /* retc = */ theKpStAppPtr->RefreshGrpMenu(True);

// ----------------------------------------
#if FALSE
unsigned char *pnts = null;
KP_NEWA(pnts, unsigned char, 100);
PutLogMessage_("ProcessGrpThreadProc() %d %lx", refresh_cnt++, pnts);
KP_DELETEA(pnts);
#endif
      if(SUCCEEDED(retc)) retc = KpSleep(KPSTGR_REFRESH_TIMEOUT); // laukiam iki kito periodinio foninio meniu siuntimo
   }

   if(/* SUCCEEDED(retc) */ theKpStAppPtr != NULL) theKpStAppPtr->m_lGrpRefreshThreadId = 0L;

// PutLogMessage_("ProcessGrpThreadProc() thread: %d fin", GetCurrentThreadId());

return(RET_CODE_WIN(retc));
}


HRESULT KpStApp::StartProcessGrpThread(void)
{
HRESULT retc = S_OK;

// ---------------------- paleidžiam ProcessGrpThreadProc() (ProcessGrp() naujam threade)
   if(SUCCEEDED(retc))
   {
HANDLE thread = NULL;
      thread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         ProcessGrpThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         NULL           // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      KP_ASSERT(thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

return(retc);
}


HRESULT KpStApp::StopProcessGrpThread(void)
{
HRESULT retc = S_OK;

// PutLogMessage_("StopProcessGrpThread() thread: %d stabdom", m_lGrpRefreshThreadId);

// bool sent = False;
   for(int ii = 0; (ii < KP_TIMEOUT_TIMEOUT/KPST_STOP_PROCESS_POLLING_TIMER) && SUCCEEDED(retc); ii++)
   {
      if(m_lGrpRefreshThreadId != 0L)
      {
//       if(!sent) sent =
            PostThreadMessage(m_lGrpRefreshThreadId, WM_QUIT, IDCANCEL, 0);

// PutLogMessage_("StopProcessGrpThread() thread: %d stabdom m_lGrpRefreshThreadId", m_lGrpRefreshThreadId);
      }

// ------------
// laukiam, kol atsilaisvins m_GrpDownLoadThreadList
      while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
      m_bGrpDownloadListProcessing = True;

KpTreeEntry *cur_node = (KpTreeEntry *)m_GrpDownLoadThreadList;
      while((cur_node != NULL) && SUCCEEDED(retc))
      {
DWORD *cur_thread_ptr = (DWORD *)cur_node->GetValue();
         KP_ASSERT(cur_thread_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

         if(SUCCEEDED(retc))
         {
            PostThreadMessage(*cur_thread_ptr, WM_QUIT, IDCANCEL, 0);
#if FALSE
unsigned char str_buf[KP_MAX_FILE_LIN_LEN + 1];
DumpGrpDownloadThreadList(str_buf, False);
PutLogMessage_("StopProcessGrpThread() thread: %d stabdom m_GrpDownLoadThreadList [%s]", *cur_thread_ptr, str_buf);
#endif
         }

         if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother(&cur_node);
      }

      m_bGrpDownloadListProcessing = False;

      Sleep(KPST_STOP_PROCESS_POLLING_TIMER);

      if((m_lGrpRefreshThreadId == 0L) && (m_GrpDownLoadThreadList == NULL)) break;
   }

#if FALSE
unsigned char str_buf[KP_MAX_FILE_LIN_LEN + 1];
DumpGrpDownloadThreadList(str_buf, True);
PutLogMessage_("StopProcessGrpThread() thread: visus sustabdėm [%s]", str_buf);
#endif

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetIniUserPwdEnc(long lCryptCode, unsigned char *lpszCryptPwdOutBuf)
{
HRESULT retc = S_OK;

// -------------------------
   KP_ASSERT(lpszCryptPwdOutBuf != null, E_INVALIDARG, null, True);

// ------------------------- CryptCode
CryptPwd crypt_pwd;
   if(SUCCEEDED(retc)) crypt_pwd.m_lCryptCode = ~lCryptCode; // invertuojam

// PutLogMessage_("GrpSvrRequest() 4: %02x %02x %02x %02x", crypt_pwd.m_lpszCryptPwd[0], crypt_pwd.m_lpszCryptPwd[1], crypt_pwd.m_lpszCryptPwd[2], crypt_pwd.m_lpszCryptPwd[3]);

// ------------------------------ užkoduojam slaptažodį
// ---- įvestas slaptažodis
unsigned char pwd[TV_TAG_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetIniUserPwd(pwd);
   KP_ASSERT(strlen(pwd) <= TV_TAG_LEN, KP_E_BUFFER_OVERFLOW, null, True);
// PutLogMessage_("GrpSvrRequest() 4: %s", pwd);

   if(SUCCEEDED(retc)) strcpy(&crypt_pwd.m_lpszCryptPwd[4], pwd);   // kopijuojam kliento įvestą slaptažodį nuo ketvirto masyvo baito, priekyje palikdami invertuotą CryptCode
int pwd_len = 0;
   if(SUCCEEDED(retc)) pwd_len = strlen(&crypt_pwd.m_lpszCryptPwd[4]);       // atsimenam slaptažodžio ilgį

#if FALSE
   if(SUCCEEDED(retc)) for(int ii = 0; ii < pwd_len; ii++) // koduojam su 4-ų baitų poslinkiu – nuliniu baitu koduojam 4-ą (pirmą slaptažodžio baitą), 1-u – 5-ą ir t. t.
      crypt_pwd.m_lpszCryptPwd[ii + 4] = crypt_pwd.m_lpszCryptPwd[ii + 4] ^ crypt_pwd.m_lpszCryptPwd[ii];
#else
   if(SUCCEEDED(retc))
   {
static KpRcPars rc_pars;
      rc_pars.iOpCode = KP_RC_ENCODE_PWD;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iDataLen = sizeof(crypt_pwd);
      rc_pars.enc.pData = &crypt_pwd;

      retc = EmuTv.ExecRemoteCall(&rc_pars);
   }
#endif

   if(SUCCEEDED(retc)) for(int ii = 0; ii < pwd_len; ii++) // formatuojam slaptažodį
      sprintf((char *)&lpszCryptPwdOutBuf[2 * ii], "%02x", crypt_pwd.m_lpszCryptPwd[ii + 4]);
   if(SUCCEEDED(retc)) lpszCryptPwdOutBuf[2 * pwd_len] = 0; // užbaigiam hex eilutę
// PutLogMessage_("GrpSvrRequest() 5: %s %s", crypt_pwd_out_buf, crypt_pwd.m_lpszCryptPwd + 4);

return(retc);
}


// -----------------------------------------
#define KPST_PRODGRP_CFG_BUF_SIZE KP_MAX_FILE_LIN_LEN

HRESULT KpStApp::GrpSvrRequest(bool bMainThread, bool bOutMsg)
{
HRESULT retc = S_OK;

// PutLogMessage_("GrpSvrRequest() 1");

// ----------------------------- priėmimo buferis
unsigned char *rcv_buf = null;
long read = KPST_PRODGRP_CFG_BUF_SIZE;

   KP_NEWA(rcv_buf, unsigned char, KPST_PRODGRP_CFG_BUF_SIZE + 100);
   if(SUCCEEDED(retc)) rcv_buf[0] = Nul;

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ----------------------------- socketo kūrimas
KpSocket *sock_ptr = NULL;
   KP_NEWO(sock_ptr, KpSocket);
#endif

#ifdef KPST_PRODGRP_OLD_INTERFACE
// ----------------------------- ištraukiam LicKod
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT + 1];
   if(SUCCEEDED(retc)) retc = FormatLicCodeFull(lic_buf);
if(SUCCEEDED(retc)) strcpy(lic_buf, "L9A6-J3E7-R55G");

// ----------------------------- ištraukiam m_ProdVar
int prod_var = -1;
   if(SUCCEEDED(retc)) retc = GetProdVarReg();
   if(SUCCEEDED(retc)) prod_var = m_ProdVar;

#else
// ----------------------------- generuojam SesId
SYSTEMTIME sys_time;
   if(SUCCEEDED(retc)) GetSystemTime(&sys_time);
FILETIME file_time;
   if(SUCCEEDED(retc)) SystemTimeToFileTime(&sys_time, &file_time);
int ses_id = (((KpstRand((file_time.dwLowDateTime >> 16) & 0xFFFF) & 0x7FFF) << 16) | (KpstRand(file_time.dwLowDateTime & 0xFFFF) & 0xFFFF));
#endif

// ----------------------------- URL
unsigned char reg_url[KP_MAX_FNAME_LEN + 1];
   reg_url[0] = Nul;
   KP_ASSERT(strlen(KPST_PRODGRP_FILE)
#ifdef KPST_PRODGRP_OLD_INTERFACE
             + strlen(KPST_PRODGRP_FORMAT) + KPST_NUM_OF_LIC_CHARS
#else
             + strlen(KPST_PRODGRP_FORMAT_1)
#endif
             + MAX_LONG_DIGITS + 10 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(reg_url, KPST_PRODGRP_FILE);
#ifdef KPST_PRODGRP_OLD_INTERFACE
      sprintf((char *)reg_url + strlen(reg_url), KPST_PRODGRP_FORMAT, lic_buf, prod_var);
#else
      sprintf((char *)reg_url + strlen(reg_url), KPST_PRODGRP_FORMAT_1, ses_id);
#endif
PutLogMessage_("GrpSvrRequest() 2: [%s]", reg_url);
   }

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ------------------------------ jungiamės
   if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_PRODGRP_URL, bOutMsg);
   if(SUCCEEDED(retc)) retc = sock_ptr->Connect(bOutMsg);

// ------------------------------ siunčiam užklausą
   if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, reg_url, bOutMsg);
#endif

#ifndef KPST_PRODGRP_OLD_INTERFACE

// ------------------------------ priimam CryptCode slaptažodžio užkodavimui
   read = KPST_PRODGRP_CFG_BUF_SIZE;
   if(SUCCEEDED(retc))
   {
#  ifndef KPST_PRODGRP_NO_SVR_REQUEST
      retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, bOutMsg);
#  else // #  ifndef KPST_PRODGRP_NO_SVR_REQUEST
      strcpy(rcv_buf, "1699317834");
      read = strlen(rcv_buf);
#  endif // #  ifndef KPST_PRODGRP_NO_SVR_REQUEST
   }

   KP_ASSERTE(read < KPST_PRODGRP_CFG_BUF_SIZE, KP_E_BUFFER_OVERFLOW, null, bOutMsg);
   if(SUCCEEDED(retc)) rcv_buf[read] = Nul;

   KP_ASSERTE(read > 0, KP_E_FILE_FORMAT, null, bOutMsg);
#if TRUE // #ifdef Debug //
PutLogMessage_("GrpSvrRequest() 3: [%s]", rcv_buf);
#endif

// ------------------------- skanuojam priimtą CryptCode
long crypt_code = 0L;
   if(SUCCEEDED(retc)) sscanf((const char *)rcv_buf, "%ld", &crypt_code);

// ------------------------------ užkoduotas slaptažodis
unsigned char crypt_pwd_out_buf[2 * TV_TAG_LEN + 1];   // buferis šešioliktainiam užkoduoto slaptažodžio formatavimui
   if(SUCCEEDED(retc)) GetIniUserPwdEnc(crypt_code, crypt_pwd_out_buf);

// -------- formuojam antrą užklausą su užkoduotu slap.
unsigned char user[KP_MAX_FILE_LIN_WDT + 1];
   if(SUCCEEDED(retc)) retc = GetIniUserData(user);

int comp_id = 0;
long fiz_id = 0L;
#if TRUE // #if FALSE // šita paprogramė iškviečiama nepagrindiniam threade – iškelta į InitStApp()
   if(SUCCEEDED(retc)) retc = GetPhysCompId(&fiz_id);
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
#else
   if(SUCCEEDED(retc)) comp_id = m_iCompId;
#endif

long bolt = 0L;
   if(SUCCEEDED(retc)) retc = GetBolt(&bolt, fiz_id);

   KP_ASSERT(strlen(KPST_PRODGRP_FILE)
             + strlen(KPST_PRODGRP_FORMAT_2)
             + MAX_LONG_DIGITS + strlen(user) + strlen(crypt_pwd_out_buf) + MAX_INT_DIGITS + MAX_LONG_DIGITS + 10 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(reg_url, KPST_PRODGRP_FILE);
      sprintf((char *)reg_url + strlen(reg_url), KPST_PRODGRP_FORMAT_2, ses_id, user, crypt_pwd_out_buf, comp_id, (bMainThread || m_bForceGrpCfg)?1:0, bolt, fiz_id);
   }
PutLogMessage_("GrpSvrRequest() 8: [%s]", reg_url);

#  ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ------------------------------ siunčiam antrą užklausą
   if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, reg_url, bOutMsg);
#  endif

#  if FALSE // #  if TRUE // algoritmo tikrinimas
unsigned char enc_pwd[] = "c61bd7eab27aad85d613de"; // iš kliento gautas užkoduotas slaptažodis
   pwd_len = strlen(enc_pwd) / 2; // slaptažodžio ilgis – pusė hex eilutės ilgio

   for(int ii = 0; ii < pwd_len; ii++) // skanuojam užkoduotą slaptažodį
   {
unsigned char hex_buf[3];
int ch;
      hex_buf[0] = enc_pwd[2 * ii];
      hex_buf[1] = enc_pwd[2 * ii + 1];
      hex_buf[2] = 0;
      sscanf((const char *)hex_buf, "%x", &ch);
      crypt_pwd.m_lpszCryptPwd[4 + ii] = ch;
   }
PutLogMessage_("GrpSvrRequest() 9: [%s]", &crypt_pwd.m_lpszCryptPwd[4]);

   for(int ii = pwd_len - 1; ii >= 0; --ii) // atkoduojam slaptažodį
      crypt_pwd.m_lpszCryptPwd[4 + ii] = crypt_pwd.m_lpszCryptPwd[4 + ii] ^ crypt_pwd.m_lpszCryptPwd[ii];
   crypt_pwd.m_lpszCryptPwd[4 + pwd_len] = 0; // užbaigiam atkoduoto slaptažodžio eilutę
PutLogMessage_("GrpSvrRequest() 10: [%s]", &crypt_pwd.m_lpszCryptPwd[4]);
#  endif

#endif // #  ifndef KPST_PRODGRP_OLD_INTERFACE

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ------------------------------ priimam atsakymą
   KP_DELETEA(rcv_buf);
   if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpMsg(&rcv_buf, &read, bOutMsg); // True); // StartGrp.exe klaida_20120720_Darius_WSAECONNABORTED lenda pranešimas
   if(SUCCEEDED(retc)) rcv_buf[read] = Nul;

   KP_ASSERTE(read > 0, KP_E_FILE_FORMAT, null, bOutMsg);

// ------------------------------ naikinam socketą
   KP_DELETE(sock_ptr);
#endif

// --------------------------
#ifdef KPST_PRODGRP_STATIC_CFG
// if(FAILED(retc))
   {
      retc = S_OK;
      KP_DELETEA(rcv_buf);
      KP_NEWA(rcv_buf, unsigned char, strlen(lpszStartGrpCfgDef) + 100);
//    KP_ASSERT(strlen(lpszStartGrpCfgDef) < KPST_PRODGRP_CFG_BUF_SIZE, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)){ strcpy(rcv_buf, lpszStartGrpCfgDef); read = strlen(rcv_buf); }
   }
// -----------
#else // #ifdef KPST_PRODGRP_STATIC_CFG
#  ifdef KPST_PRODGRP_NO_SVR_REQUEST
   retc = KP_E_REFUSED;
#  endif
#endif

// išsisaugojam testavimui
#if FALSE
FILE *tmp_file = fopen("StartGrp.xml", "wb");
fputs((const char *)rcv_buf, tmp_file);
fclose(tmp_file);
#endif

// ----------------------------- atnaujinam XML parametrų failo tekstą
   if(SUCCEEDED(retc))
   {
      KP_DELETEA(m_lpszGrpCfgBuf);

      m_lpszGrpCfgBuf = rcv_buf;
      rcv_buf = null;
   }
   else KP_DELETEA(rcv_buf);

// -----------
   m_bForceGrpCfg = FAILED(retc);

return(retc);
}


// -----------------------------------------
#if FALSE
DWORD WINAPI GrpSvrRequestThreadProc(LPVOID lpParameter)
{
HRESULT retc = S_OK;

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_NO_FILE, null, True);
   if(SUCCEEDED(retc))
   {
      KP_ASSERT(lpParameter != NULL, E_INVALIDARG, null, True);
bool msg_fl = True;
      if(SUCCEEDED(retc)) msg_fl = *((bool *)lpParameter);

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GrpSvrRequest(msg_fl);

      theKpStAppPtr->m_iGrpSvrRequestRetCode = retc; // grįžimo kodas pagrindiniam threadui GrpSvrRequestAsyn()
   }

return(RET_CODE_WIN(retc));
}
#endif


// -----------------------------------------
#if FALSE
HRESULT KpStApp::GrpSvrRequestAsyn(bool bOutMsg)
{
HRESULT retc = S_OK;
static bool msg_fl = bOutMsg;

   m_iGrpSvrRequestRetCode = KP_E_SYSTEM_ERROR; // inicializuojam GrpSvrRequestThreadProc() grįžimo kodą

// ---------------------- paleidžiam GrpSvrRequestThreadProc() (GrpSvrRequest() naujam threade)
DWORD thread_id = 0L;
HANDLE thread = NULL;
   if(SUCCEEDED(retc))
   {
      thread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         GrpSvrRequestThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         &msg_fl,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         &thread_id           // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      KP_ASSERT(thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

// --------------------- laukiam kol pasibaigs
int ii = 0;
   if(SUCCEEDED(retc)) for(ii = 0; (ii < KPST_PRODGRP_SVR_REQUEST_ASYN_TIMEOUT / KPST_PRODGRP_SVR_REQUEST_ASYN_SLEEP) && SUCCEEDED(retc); ii++)
   {
DWORD exit_code = ~STILL_ACTIVE;
      KP_ASSERT(GetExitCodeThread(thread, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), bOutMsg);
      if(SUCCEEDED(retc)) if(exit_code != STILL_ACTIVE) break;

      if(SUCCEEDED(retc)) retc = KpSleep(KPST_PRODGRP_SVR_REQUEST_ASYN_SLEEP);
   }

   if(SUCCEEDED(retc))
   {
      if(ii < KPST_PRODGRP_SVR_REQUEST_ASYN_TIMEOUT / KPST_PRODGRP_SVR_REQUEST_ASYN_SLEEP) retc = m_iGrpSvrRequestRetCode;
      else retc = KP_E_TIMEOUT;
   }

return(retc);
}
#endif


// -----------------------------------------
HRESULT KpStApp::ParseGrpCfgBuf()
// Pranešimas gali būti toks:
//
// <br />
// <b>Warning</b>:  mysql_num_rows(): supplied argument is not a valid MySQL result resource in <b>/home/tevukas/domains/tev.lt/public_html/prodgrp.php</b> on line <b>86</b><br />
// <?xml version="1.0" encoding="UTF-8" ?>
// <pr>
//    <resp>KpReg-Error: Neteisingas vardas/spalta┼Šodis</resp>
// </pr>
//
{
HRESULT retc = S_OK;

   KP_ASSERT(m_lpszGrpCfgBuf != null, KP_E_NO_FILE, null, True);

// ---------------- buferinio failo vardas
unsigned char file_name[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) sprintf((char *)file_name, "%x %x", m_lpszGrpCfgBuf, strlen(m_lpszGrpCfgBuf));

// ---------------- atidarom input failą
XmlO1 *in_file = NULL;
   KP_NEWO(in_file, XmlO1(file_name,
                     (const unsigned char *)"rb",
                     CreateNewUniBFile,
                     plpszaXmlSpecCharTagsMain,
                     alpszIndexNames, aiIndexWidths,
                     (KpChar)XG_FirstGrpTag, plpszaGrpTags, False,
                     XM_VERS_XML10, iaXmlDictNulCodeTables, True, False));

// --------------- skaitom iki <?xml ?>
KpChar in_ch = C_Nul;
XmlTagPars *tag_pars = NULL;
   if(SUCCEEDED(retc)) do
   {
      retc = in_file->GetCharProc(&in_ch, &tag_pars, XL_IX_DefDataFile, True, True);

// TODO: panagrinėt <?xml ?> parametrus – ar gera koduotė (UTF-8)

      KP_DELETE(tag_pars);

   } while((in_ch == C_Spc) && SUCCEEDED(retc));
   KP_ASSERT(in_ch == XL_Version, KP_E_FILE_FORMAT, null, True);

// --------------- skaitom iki <pr>
   if(SUCCEEDED(retc)) do
   {
      retc = in_file->GetCharProc(&in_ch, &tag_pars, XL_IX_DefDataFile, True, True);

      if(in_ch != XG_GrPars) KP_DELETE(tag_pars);

   } while((in_ch == C_Spc) && SUCCEEDED(retc));
   KP_ASSERT(in_ch == XG_GrPars, KP_E_FILE_FORMAT, null, True);

// --------------- <pr> atstatom atgal
   if(SUCCEEDED(retc)) in_file->UnGetCharProc(in_ch, tag_pars, XL_IX_DefDataFile);
   KP_DELETE(tag_pars);

// --------------- naikinam seną m_pGrpCfgNode reikšmę
   if(SUCCEEDED(retc)) KP_DELETE(m_pGrpCfgNode);

// --------------- parsinam buferį m_lpszGrpCfgBuf į lizdą m_pGrpCfgNode
   if(SUCCEEDED(retc)) retc = ReadEntry(&m_pGrpCfgNode, in_file, True, (KpChar)XG_FirstGrpTag, plpszaGrpTags);
   KP_ASSERT(m_pGrpCfgNode != NULL, KP_E_NO_FILE, null, True);

// ---------------- uždarom input failą
   KP_DELETE(in_file);

// ------------------
// if(SUCCEEDED(retc)) m_pGrpCfgNode->TraceContents((const unsigned char *)"");

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpCfgItem(XmlNode **pItemPtr, const unsigned char *lpszProdName, XmlNode *pPrpCfgSubNode, bool bInnoSetup)
{
HRESULT retc = S_OK;

   KP_ASSERT(pItemPtr != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszProdName != null, E_INVALIDARG, null, True);
   KP_ASSERT(pPrpCfgSubNode != NULL, E_INVALIDARG, null, True);

// --------------------- rekursijos nereikia: pPrpCfgSubNode – <pr> mazgas, visi <item> – jo pirmos kartos vaikai
KpChar cur_tag = C_Nul;
   if(SUCCEEDED(retc)) retc = pPrpCfgSubNode->GetNodeTag(&cur_tag);
   KP_ASSERT(cur_tag == XG_GrPars, KP_E_FILE_FORMAT, null, True);

// --------------------- ištraukiam pirmą vaiką
XmlNode *cur_node = NULL;
// if(SUCCEEDED(retc)) retc = pPrpCfgSubNode->GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)pPrpCfgSubNode->m_pFirstChild;

   if(SUCCEEDED(retc)) while((cur_node != NULL) && (*pItemPtr == NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);

// -------------------- <item>
      if((cur_tag == XG_Item) && SUCCEEDED(retc))
      {
// -------------------- ieškom <appname> reikšmės
unsigned char *val_str = null;
         if(SUCCEEDED(retc)) retc = GetGrpItemAppName(&val_str, NULL, cur_node, bInnoSetup);
         KP_ASSERT(val_str != NULL, KP_E_FILE_FORMAT, null, True);
// PutLogMessage_("KpStApp::GetGrpCfgItem() <appname>: [%s] [%s] %d", val_str, lpszProdName, strcmp(val_str, lpszProdName));

// ar sutampa prod. vardas?
         if(SUCCEEDED(retc)) if(strcmp(val_str, lpszProdName) == 0)
            *pItemPtr = cur_node; // radom

// trinam val_str
         KP_DELETEA(val_str);

      } // if((cur_tag == XG_Item) && SUCCEEDED(retc))

#if FALSE // visi <item> yra pirmam <pr> vaikų lygmeny
      else // rekursinam per vaikus
      {
//       if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_child);
         if(SUCCEEDED(retc)) cur_child = (XmlNode *)cur_node->m_pFirstChild;

         if(cur_child != NULL) retc = GetGrpCfgItem(pItemPtr, lpszProdName, cur_child, bInnoSetup);
      }
#endif

      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node); // ciklinam per brolius

   } // while((cur_node != NULL) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::CheckGrpResponce(void)
{
HRESULT retc = S_OK;

XmlNode *cur_node = m_pGrpCfgNode;
   KP_ASSERT(cur_node != NULL, KP_E_NO_FILE, null, True);

KpChar cur_tag = C_Nul;
   if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag); // tagas <pr>
   KP_ASSERT(cur_tag == XG_GrPars, KP_E_FILE_FORMAT, null, True);

// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_node); // <pr> vaikai
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)cur_node->m_pFirstChild;
   KP_ASSERT(cur_node != NULL, KP_E_FILE_FORMAT, null, True);

bool found = False;
   while((cur_node != NULL) && (!found) && SUCCEEDED(retc)) // ieškom <resp>
   {
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
      if(cur_tag == XG_Responce) found = True;
      else retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }
   KP_ASSERT(found, KP_E_FILE_FORMAT, null, True);

// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_node); // <resp> vaikas
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)cur_node->m_pFirstChild;
   KP_ASSERT(cur_node != NULL, KP_E_FILE_FORMAT, null, True);

   if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
   KP_ASSERT(cur_tag == XL_Text, KP_E_FILE_FORMAT, null, True);

KpChar *resp_cont_i = NULL;
   if(SUCCEEDED(retc)) retc = cur_node->GetContentsPtr(&resp_cont_i); // <resp> reikšmė KpChar[]
   KP_ASSERT(resp_cont_i != NULL, KP_E_FILE_FORMAT, null, True);

unsigned char *resp_cont = null;
   KP_NEWA(resp_cont, unsigned char, TvKpStrLen(resp_cont_i) + 1); // kuriam <resp> reikšmės ANSI buferį

// TODO: čia šiaip jau UTF-8, ne ISO-8859-13
   if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(resp_cont, resp_cont_i, TV_MAIN_CTBL); // <resp> ANSI reikšmė

const unsigned char *pnts = null;
   if(SUCCEEDED(retc))
   {
      if(strstr(resp_cont, KPST_REG_VOID_short) != null) retc = KP_E_CANCEL;
      else
      {
         pnts = strstr(resp_cont, KPST_REG_ERROR_short); // KPST_REG_REFUSED_short);
         if(pnts != null)
         {
            pnts += strlen(KPST_REG_ERROR_short); // KPST_REG_REFUSED_short);
            while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
            if(*pnts == ':') pnts++;

            KpMsgOut(pnts, IDI_ERROR, KP_MB_TESTI);
            retc = KP_E_ACCESS_DENIED;
         }
         else
         {
            pnts = strstr(resp_cont, KPST_REG_ERROR_short);
            if(pnts != null)
            {
               pnts += strlen(KPST_REG_ERROR_short);
               while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
               if(*pnts == ':') pnts++;

               KP_ERROR(KP_E_REFUSED, pnts);
            }
            else
            {
//             KP_ASSERTE(strstr(resp_cont, KPST_REG_OK_short) != null, KP_E_REFUSED, resp_cont, False); // tikrinam, ar "KpReg-Ok"
               KP_ASSERT(strstr(resp_cont, KPST_REG_OK_short) != null, KP_E_TRANS_ERR, resp_cont, True);   // jei leidinys vienetinis, turi duot "KpReg-Ok" ir sąrašą iš vienos licencijos
            }                                                                                         // tam, kad tikrinimą būtų galima dėt visur
         }                                                                                         // tam, kad tikrinimą būtų galima dėt visur
      }
   }

   KP_DELETEA(resp_cont);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::CalcGrpCfgFName(void)
{
HRESULT retc = S_OK;
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char name[KP_MAX_FNAME_LEN + 1];
static unsigned char type[KP_MAX_FTYPE_LEN + 1];
static unsigned char cfg_fname[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetAppName(cfg_fname);
   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, name, type, cfg_fname);
   if(SUCCEEDED(retc)) if(strlen(disk) + strlen(path) + 1 + strlen(STARTSEL_MNG_DIR) + 1 + strlen(name) + 1 + strlen(START_SEL_CFG_FTYPE) >= KP_MAX_FNAME_LEN)
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(cfg_fname, disk);
      strcat(cfg_fname, path);
      strcat(cfg_fname, "\\");
      strcat(cfg_fname, STARTSEL_MNG_DIR);
      strcat(cfg_fname, "\\");
      strcat(cfg_fname, name);
      strcat(cfg_fname, ".");
      strcat(cfg_fname, START_SEL_CFG_FTYPE);
   }

   if(SUCCEEDED(retc)) strcpy(m_lpszGrpCfgFName, cfg_fname);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::InitGrpCfg(void)
{
HRESULT retc = S_OK;

   KP_DELETEA(m_lpszGrpCfgBuf);

   KP_NEWA(m_lpszGrpCfgBuf, unsigned char, strlen(lpszStartGrpCfgEmpty) + 1);

   if(SUCCEEDED(retc)) strcpy(m_lpszGrpCfgBuf, lpszStartGrpCfgEmpty);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SaveGrpCfg(void)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_lpszGrpCfgBuf != null, KP_E_NO_FILE, null, True);

// užkoduojam
int file_len = 0;
   if(SUCCEEDED(retc)) file_len = strlen(m_lpszGrpCfgBuf);
#ifdef KPST_PRODGRP_CFG_ENCODED
int prod_ver = 0;
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

// if(SUCCEEDED(retc)) retc = EnctBufSimpl(m_lpszGrpCfgBuf, file_len);
   if(SUCCEEDED(retc)) retc = EnctBufInc(m_lpszGrpCfgBuf, file_len, prod_ver, 0L, True);
#endif

// failas
   if(SUCCEEDED(retc)) retc = CalcGrpCfgFName();

   if(SUCCEEDED(retc)) retc = CreatePath(m_lpszGrpCfgFName, True);

HANDLE cfg_file = INVALID_HANDLE_VALUE;
   if(SUCCEEDED(retc))
   {
      cfg_file = CreateFile((const char *)m_lpszGrpCfgFName, GENERIC_WRITE, FILE_SHARE_WRITE,
         0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
      KP_ASSERT(cfg_file != INVALID_HANDLE_VALUE, KP_E_DIR_ERROR, m_lpszGrpCfgFName, True);
   }

// rašom
DWORD written = 0;
   KP_ASSERT(WriteFile(cfg_file, (const char *)m_lpszGrpCfgBuf, file_len, &written, NULL), KP_E_FERROR, m_lpszGrpCfgFName, True);
   KP_ASSERT(written == file_len, KP_E_FERROR, m_lpszGrpCfgFName, False);

   if(cfg_file != INVALID_HANDLE_VALUE)
      KP_ASSERT(CloseHandle(cfg_file), KP_E_FERROR, m_lpszGrpCfgFName, True);

// atkoduojam atgal
#ifdef KPST_PRODGRP_CFG_ENCODED
// if(SUCCEEDED(retc)) retc = EnctBufSimpl(m_lpszGrpCfgBuf, file_len);
   if(SUCCEEDED(retc)) retc = EnctBufInc(m_lpszGrpCfgBuf, file_len, prod_ver, 0L, False);
#endif

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::LoadGrpCfg(void)
{
HRESULT retc = S_OK;

// trinam seną
   KP_DELETEA(m_lpszGrpCfgBuf);

// failas
   if(SUCCEEDED(retc)) retc = CalcGrpCfgFName();

long file_len = 0L;
   if(SUCCEEDED(retc))
   {
      retc = ReadFileContents(m_lpszGrpCfgFName, &m_lpszGrpCfgBuf, &file_len, False, True);
      if(SUCCEEDED(retc))
      {
// atkoduojam
#ifdef KPST_PRODGRP_CFG_ENCODED
int prod_ver = 0;
         if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

//       if(SUCCEEDED(retc)) retc = EnctBufSimpl(m_lpszGrpCfgBuf, file_len);
         if(SUCCEEDED(retc)) retc = EnctBufInc(m_lpszGrpCfgBuf, file_len, prod_ver, 0L, False);
#endif
         if(SUCCEEDED(retc)) m_lpszGrpCfgBuf[file_len] = Nul;
      }
      else // if(SUCCEEDED(retc)) // retc = ReadFileContents()
      {
// lokalaus failo pakraut nepavyko – generuojam nulinį
         retc = S_OK;

         if(SUCCEEDED(retc)) retc = InitGrpCfg();
         if(SUCCEEDED(retc)) retc = SaveGrpCfg();
      }
   }

return(retc);
}


// -----------------------------------------
KpGrpChk::KpGrpChk()
{
   m_lpszDownLoadFName[0] = Nul;
   m_lDownLoadFSize = 0L;
   m_bSetupFl = False; // paprastas failas – diegti nereikia
   m_bRegFl = False;
   m_lpszLicCode[0] = Nul;

/*
   m_time.wYear  = 2100;
   m_time.wMonth = 1;
   m_time.wDay   = 1;
   m_time.wDayOfWeek = 0;
   m_time.wHour   = 0;
   m_time.wMinute = 0;
   m_time.wSecond = 0;
   m_time.wMilliseconds = 0;
*/
}


// -----------------------------------------
HRESULT KpStApp::ExtractGrpDownLoads(/* const */ XmlNode *pPrpCfgSubNode)
{
HRESULT retc = S_OK;
XmlNode *cur_node = NULL; // pPrpCfgSubNode;
KpChar cur_tag = C_Nul;
int prod_ver = 0;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

// --------------------- rekursijos nereikia: pPrpCfgSubNode – <pr> mazgas, visi <item> – jo pirmos kartos vaikai
   KP_ASSERT(pPrpCfgSubNode != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = pPrpCfgSubNode->GetNodeTag(&cur_tag);
   KP_ASSERT(cur_tag == XG_GrPars, KP_E_FILE_FORMAT, null, True);

// --------------------- ištraukiam pirmą vaiką
// if(SUCCEEDED(retc)) retc = pPrpCfgSubNode->GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)pPrpCfgSubNode->m_pFirstChild;

   while((cur_node != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);

// -------------------- <item>
      if((cur_tag == XG_Item) && SUCCEEDED(retc))
      {
bool proceed = True;
KpGrpChk grp_item;

// ---------------------
         grp_item.m_bSetupFl = True; // grupinio leidinio komponento/atnaujinimo įrašas – diegti reikia

// -------------------- ieškom <lic>/ProdVer
unsigned char *lic_val_str = null;
int cur_prod_ver = 0;
         if(SUCCEEDED(retc)) retc = ExtractGrpLicProdVer(&lic_val_str, NULL, &cur_prod_ver, cur_node);
//       KP_ASSERT(lic_val_str != null, KP_E_FILE_FORMAT, null, True);
         if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK; // KP_ERROR(KP_E_FILE_FORMAT, null);

         if((cur_prod_ver == prod_ver) && SUCCEEDED(retc)) proceed = False;

// -------------------- pridedam <lic>
         if(proceed && (lic_val_str != null) && SUCCEEDED(retc))
         {
// licenciją radom – čia registruojamo grupinio komponento įrašas
            grp_item.m_bRegFl = True;
// PutLogMessage_(lic_val_str);

            KP_ASSERT(strlen(lic_val_str) == KPST_NUM_OF_LIC_CHARS, KP_E_FILE_FORMAT, null, True);
            if(SUCCEEDED(retc)) strcpy(grp_item.m_lpszLicCode, lic_val_str);
         }

// trinam licencijos <lic> val_str
         KP_DELETEA(lic_val_str);

         if(proceed && SUCCEEDED(retc))
         {
// -------------------- ieškom <appname> reikšmės Inno Setup kodavimu
unsigned char *app_name = null;
KpChar *app_name_i = NULL;
            if(SUCCEEDED(retc)) retc = GetGrpItemAppName(&app_name, &app_name_i, cur_node, True);
            KP_ASSERT(app_name != NULL, KP_E_FILE_FORMAT, null, True);

// išsaugojam į grp_item
            KP_ASSERT(strlen(app_name) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, app_name, True);
            if(SUCCEEDED(retc)) strcpy(grp_item.m_lpszText, app_name);
            KP_ASSERT(TvKpStrLen(app_name_i) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, app_name, True);
            if(SUCCEEDED(retc)) TvKpStrCpy(grp_item.m_iazText, app_name_i);

// trinam app_name
            KP_DELETEA(app_name);
            KP_DELETEA(app_name_i);

// -------------------- pridedam <updname> reikšmę, jei yra
unsigned char *upd_name = null;
            upd_name = null;
            if(SUCCEEDED(retc)) retc = cur_node->ExtractSubnodeContentsStr(XG_UpdName, &upd_name);
            if(upd_name != null)
            {
// išsaugojam į grp_item
               KP_ASSERT(strlen(grp_item.m_lpszText) + 1 + strlen(upd_name) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, upd_name, True);
               if(SUCCEEDED(retc)) strcat(grp_item.m_lpszText, " ");
               if(SUCCEEDED(retc)) strcat(grp_item.m_lpszText, upd_name);
            }

// trinam upd_name
            KP_DELETEA(upd_name);

// ---------------------- tikrinam, ar įdiegtas
#if FALSE // pagal HKCU/Software/TEV/<ProdVer>/Installed netinka, nes išmetinėja adminas ir šito rakto nepanaikina – po panaikinimo lokalus useris nepajaučia, kad komponento jau nėra
int prod_var = -2;
// išsitraukiam ProdVar
// TODO: patikrinti, ar suveiks lokaliam useryje diegiami produktai – Installed (ProdVar) jiems yra HKCU, o ne HKLM
            if(SUCCEEDED(retc)) retc = GetProdVarRegTmp(cur_prod_ver, &prod_var);
            if(SUCCEEDED(retc)) if(prod_var >= 0) proceed = False;
// PutLogMessage_("%s %d %d", val_str, cur_prod_ver, prod_var);

#else
// TODO: perdaryt į Unicode
// išsitraukiam diegimo katalogą
            if(SUCCEEDED(retc))
            {
// ištraukiam <launch> – pagal nuorodos failą tikrinsim diegimo buvimą
bool installed = False;
unsigned char launch_buf[KP_MAX_FNAME_LEN + 1];
               launch_buf[0] = Nul;
               retc = GetGrpLaunch(launch_buf, NULL, &installed, cur_node);
               if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
               else if(installed && SUCCEEDED(retc)) proceed = False;
            }
#endif
         } // if(proceed && SUCCEEDED(retc))

// ------------------- pridedam prie parsisiųstinų tik tuos, kurie neįdiegti, arba atnaujinimus (kuriems neradom licencijos kodo)
         if(proceed && SUCCEEDED(retc))
         {
// -------------------- ieškom <setup>
unsigned char *setup_str = null;
            if(SUCCEEDED(retc)) retc = cur_node->ExtractSubnodeContentsStr(XG_Setup, &setup_str);
            KP_ASSERT(setup_str != null, KP_E_FILE_FORMAT, null, True);

// išsaugojam į grp_item.m_lpszDownLoadFName
            KP_ASSERT(strlen(setup_str) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, setup_str, True);
            if(SUCCEEDED(retc)) strcpy(grp_item.m_lpszDownLoadFName, setup_str);

// trinam setup_str
            KP_DELETEA(setup_str);

// ieškom setup failo dydžio
XmlNode *cur_child = NULL;
            if(SUCCEEDED(retc)) retc = cur_node->SearchChildSubNode(XG_Setup, &cur_child);
            KP_ASSERT(cur_child != NULL, KP_E_FILE_FORMAT, null, True);

XmlTagPars *tag_pars = NULL;
            if(SUCCEEDED(retc)) retc = cur_child->GetTagParsPtr(&tag_pars);
            KP_ASSERT(tag_pars != NULL, KP_E_FILE_FORMAT, null, True);

            if(SUCCEEDED(retc))
            {
long num_val = 0L;
int par_num = 0;
               retc = tag_pars->SeekNumPar("size", &num_val, &par_num);
               if(FAILED(retc)) KP_ERROR(retc, null);
               if(SUCCEEDED(retc)) grp_item.m_lDownLoadFSize = num_val;
//             retc = S_OK;
            }

// failo datos nereikia – siunčiam bet kokiu atveju

// ------------------- pridedam sąrašo įrašą
            if(SUCCEEDED(retc))
            {
               if(m_aGrpDownLoads == NULL)
                  KP_NEW(m_aGrpDownLoads, KpTreeEntry(&grp_item, sizeof(grp_item), NULL, KpRecType_TextChk))
               else retc = m_aGrpDownLoads->PutToEnd(&grp_item, sizeof(grp_item), KpRecType_TextChk);
            }

// ------------------
         } // if(proceed && SUCCEEDED(retc))

      } // if((cur_tag == XG_Item) && SUCCEEDED(retc))

#if FALSE // visi <item> yra pirmam <pr> vaikų lygmeny
      else // rekursinam per vaikus
      {
//       if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_child);
         if(SUCCEEDED(retc)) cur_child = (XmlNode *)cur_node->m_pFirstChild;

         if(cur_child != NULL) retc = ExtractGrpDownLoads(cur_child);
      }
#endif

      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node); // ciklinam per brolius

   } // while((cur_node != NULL) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SelectSetupDownload(int iProdVer, const unsigned char *lpszProdName, bool bUpdFl)
{
HRESULT retc = S_OK;

KpStSelDownload dialog;

// ----------------- kuriam dialogo objektą
   if(SUCCEEDED(retc)) retc = dialog.GetOpenResult();
   KP_ASSERTE(KpStSelDownDialogPtr == NULL, KP_E_DOUBLE_CALL, null, False); // jau yra aktyvus KpStSelDownload, kol kas ne multitaskinis – tyliai nusiimam
   if(SUCCEEDED(retc)) KpStSelDownDialogPtr = &dialog;

// ----------------- pildom parsisiųstinų setupų sąrašą
   KP_DELETE(m_aGrpDownLoads);

   if(SUCCEEDED(retc)) retc = ExtractGrpDownLoads(m_pGrpCfgNode); // m_pGrpCfgNode tagų <appname> reikšmes į --> m_aGrpDownLoads

// ----------------- tikrinam, kad įrašų skaičius neviršytų KPST_SELDOWN_LISTBOX_MAX_NUM_OF_ROWS
// TODO:


// ----------------- bendraujam su dialogu
   if((m_aGrpDownLoads != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = dialog.OpenWindow(iProdVer, lpszProdName, bUpdFl);
      if(SUCCEEDED(retc)) retc = dialog.DoEdit();
      KpStSelDownDialogPtr = NULL;
   }

// ----------------- išsitraukiam pažymėtus įrašus
// nieko traukt nereikia – viskas jau guli sąrašo m_aGrpDownLoads įrašuose
// TraceGrpDownLoads();

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::AppendGrpDownLoads(/* const */ XmlNode *pPrpCfgSubNode)
{
HRESULT retc = S_OK;

   KP_ASSERT(pPrpCfgSubNode != NULL, E_INVALIDARG, null, True);
XmlNode *cur_node = pPrpCfgSubNode;

KpChar cur_tag = C_Nul;

// -------------- ciklinam per brolius
   while((cur_node != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);

// -------------------- <file>
      if(
         (
            (cur_tag == XG_File) || (cur_tag == XG_BackGround) ||
            (cur_tag == XG_ButImg) || (cur_tag == XG_ButPressed) || (cur_tag == XG_ButHover)
         ) &&
         SUCCEEDED(retc)
        )
      {
KpGrpChk grp_item;

         grp_item.m_bSetupFl = False; // paprasto failo įrašas – diegti/registruoti nereikia
         grp_item.m_bRegFl = False;

// ---------------------------- nutolusio failo vardas
KpChar *remote_fname_i = NULL;
         remote_fname_i = NULL;
         if(SUCCEEDED(retc)) retc = cur_node->ExtractContents(&remote_fname_i);
         KP_ASSERT(remote_fname_i != NULL, KP_E_FILE_FORMAT, null, True);

// konvertuojam nutolusio failo vardą
unsigned char *remote_fname = null;
         KP_NEWA(remote_fname, unsigned char, TvKpStrLen(remote_fname_i) + 1);

// TODO: perdaryt į Unicode failų vardus
         if(SUCCEEDED(retc))
         {
            retc = KptStrDecode(remote_fname, remote_fname_i, TV_MAIN_CTBL);
            if(FAILED(retc))
            {
               KP_WARNING(retc, remote_fname);
               retc = S_OK;
            }
            remote_fname[TvKpStrLen(remote_fname_i)] = C_Nul;
         }

// PutLogMessage_("KpStApp::AppendGrpDownLoads() 1: %s", remote_fname);

         KP_ASSERT(strlen(remote_fname) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, remote_fname, True);
         if(SUCCEEDED(retc)) strcpy(grp_item.m_lpszDownLoadFName, remote_fname);

// lokalaus failo vardas
unsigned char local_fname[KP_MAX_FNAME_LEN + 1];
unsigned char str_msg[KP_MAX_FNAME_LEN + 1];
         if(SUCCEEDED(retc)) retc = GetGrpLocalFName(local_fname, str_msg, remote_fname);
// PutLogMessage_("KpStApp::AppendGrpDownLoads() 1: %s", local_fname);
         KP_ASSERT(strlen(str_msg) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, str_msg, True);
         if(SUCCEEDED(retc)) strcpy(grp_item.m_lpszText, str_msg);

// trinam remote_fname
         KP_DELETEA(remote_fname);

// nutolusio failo sukūrimo data – užpildom šios dienos reikšme – tam atvejui, jei nebūtų <file> parametro "date"
SYSTEMTIME remote_file_date;
         if(SUCCEEDED(retc)) GetSystemTime(&remote_file_date);

// ieškom setup failo dydžio
XmlTagPars *tag_pars = NULL;
         if(SUCCEEDED(retc)) cur_node->GetTagParsPtr(&tag_pars);
         KP_ASSERT(tag_pars != NULL, KP_E_FILE_FORMAT, null, True);
         if((tag_pars != NULL) && SUCCEEDED(retc))
         {
long num_val = 0L;
int par_num = 0;
            retc = tag_pars->SeekNumPar("size", &num_val, &par_num);
            if(FAILED(retc)) KP_ERROR(retc, null);
            if(SUCCEEDED(retc)) grp_item.m_lDownLoadFSize = num_val;
//          retc = S_OK;

// ieškom datos
            if(SUCCEEDED(retc))
            {
static unsigned char date_buf[MAX_XML_PAR_VAL_LEN + 1];
               retc = tag_pars->SeekTextPar("date", date_buf, &par_num);

               if(SUCCEEDED(retc))
               {
/* const */ unsigned char *pnts = date_buf;
unsigned char *pntd = pnts;
int ii;
// metai
                  while((*pntd != '.') && (*pntd != Nul)) pntd++;
                  if(*pntd == '.') *pntd++ = Nul;
                  ii = 0;
                  sscanf((const char *)pnts, "%d", &ii);
                  remote_file_date.wYear = ii;
// mėnuo
                  pnts = pntd;
                  while((*pntd != '.') && (*pntd != Nul)) pntd++;
                  if(*pntd == '.') *pntd++ = Nul;
                  ii = 0;
                  sscanf((const char *)pnts, "%d", &ii);
                  remote_file_date.wMonth = ii;
// diena
                  ii = 0;
                  sscanf((const char *)pntd, "%d", &ii);
                  remote_file_date.wDay = ii;

                  remote_file_date.wDayOfWeek = 0;
                  remote_file_date.wHour   = 0;
                  remote_file_date.wMinute = 0;
                  remote_file_date.wSecond = 0;
                  remote_file_date.wMilliseconds = 0;

// PutLogMessage_("KpStApp::AppendGrpDownLoads() 2: found remote date");
               }

               retc = S_OK;
            }

         } // if((tag_pars != NULL) && SUCCEEDED(retc))

// PutLogMessage_("KpStApp::AppendGrpDownLoads() 3 remote date: %4d.%02d.%02d", remote_file_date.wYear, remote_file_date.wMonth, remote_file_date.wDay);

// tikrinam, ar reikia pridėti failo siuntimą
bool add_file = False;

// lokalaus failo sukūrimo data
SYSTEMTIME local_file_date;
         if(SUCCEEDED(retc))
         {
            retc = KpGetFileCrTime(local_fname, NULL, &local_file_date);
            if(SUCCEEDED(retc))
            {
// PutLogMessage_("KpStApp::AppendGrpDownLoads() 4 local date: %4d.%02d.%02d", local_file_date.wYear, local_file_date.wMonth, local_file_date.wDay);
               if(local_file_date.wYear < remote_file_date.wYear) add_file = True;
               else if(local_file_date.wYear == remote_file_date.wYear)
               {
                  if(local_file_date.wMonth < remote_file_date.wMonth) add_file = True;
                  else if(local_file_date.wMonth == remote_file_date.wMonth)
                  {
                     if(local_file_date.wDay < remote_file_date.wDay) add_file = True;
                  }
               }
            }

            if(retc == KP_E_FILE_NOT_FOUND)
            {
               add_file = True;
               retc = S_OK;
            }
         }

// PutLogMessage_(grp_item.m_lpszDownLoadFName);
// ------------------- pridedam prie parsisiųstinų tik tuos, kurių nėra arba data senesnė
         if(add_file && SUCCEEDED(retc))
         {
// PutLogMessage_("KpStApp::AppendGrpDownLoads() 5 pridedam: %s", local_fname);

            if(m_aGrpDownLoads == NULL)
               KP_NEW(m_aGrpDownLoads, KpTreeEntry(&grp_item, sizeof(grp_item), NULL, KpRecType_TextChk))
            else retc = m_aGrpDownLoads->PutToEnd(&grp_item, sizeof(grp_item), KpRecType_TextChk);
         }

// -------------------------------
      } // if((cur_tag == XG_File) && SUCCEEDED(retc))

      else // rekursinam per vaikus // paties <file> rekursint nereikia – <file> nerekursinis tagas
      {
XmlNode *cur_child = NULL;
//       if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_child);
         if(SUCCEEDED(retc)) cur_child = (XmlNode *)cur_node->m_pFirstChild;

         if(cur_child != NULL) retc = AppendGrpDownLoads(cur_child);
      }

      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node); // ciklinam per brolius

   } // while((cur_node != NULL) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------------
#if FALSE
void KpStApp::TraceGrpDownLoads(/* KpTreeEntry *pCurEntry */)
{
HRESULT retc = S_OK;
KpTreeEntry *cur_entry = m_aGrpDownLoads /* pCurEntry */;
while(cur_entry != NULL)
{
KpGrpChk *val_ptr = (KpGrpChk *)cur_entry->GetValue();
PutLogMessage_("%d %d %d %ld [%s] [%s] [%s]", val_ptr->m_bChecked, val_ptr->m_bSetupFl, val_ptr->m_bRegFl, val_ptr->m_lDownLoadFSize, val_ptr->m_lpszLicCode, val_ptr->m_lpszText, val_ptr->m_lpszDownLoadFName);
// cur_entry->GetFirstChild(&cur_entry);
cur_entry = cur_entry->m_pFirstChild;
}
}
#endif


// -----------------------------------------
HRESULT KpStApp::CountFullGrpSize(long *plFullSize)
{
HRESULT retc = S_OK;

   KP_ASSERT(plFullSize != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) *plFullSize = 0L;

// ciklinam per visus failus grupinio parsisiuntimo sąraše
KpTreeEntry *cur_entry = m_aGrpDownLoads;
   while((cur_entry != NULL) && SUCCEEDED(retc))
   {
KpGrpChk *cur_val = (KpGrpChk *)cur_entry->GetValue();
      KP_ASSERT(cur_val != NULL, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(cur_entry->GetValSize() >= sizeof(KpGrpChk), KP_E_SYSTEM_ERROR, null, True);

// tik pažymėtus siuntimui
      if(SUCCEEDED(retc)) if(cur_val->m_bChecked) *plFullSize += cur_val->m_lDownLoadFSize;
// PutLogMessage_("KpStApp::CountFullGrpSize(): %s %ld %ld", cur_val->m_lpszDownLoadFName, cur_val->m_lDownLoadFSize, *plFullSize);

// kitas sąrašo elementas
//    if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild((KpTreeEntry **)&cur_entry);
      if(SUCCEEDED(retc)) cur_entry = (XmlNode *)cur_entry->m_pFirstChild;

   } // while((cur_entry != NULL) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpLocalFName(unsigned char *lpszLocalFName, unsigned char *lpszProgressMsg, const unsigned char *lpszRemoteFName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszRemoteFName != null, E_INVALIDARG, null, True);

static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];
   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, lpszRemoteFName);
// PutLogMessage_("[%s] [%s] [%s] [%s]", disk, path, fname, ftype);

const unsigned char *fname_ptr = fname;

   if((lpszLocalFName != null) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetGrpLocalDir(lpszLocalFName);

      if(SUCCEEDED(retc))
      {
const unsigned char *pnts;
         pnts = strstr(fname, "file="); // http://siuntiniai.tev.lt/siustis.php?file=lentyna_ekov910_lt_setup.exe
         if(pnts != null) fname_ptr = pnts + strlen("file=");
      }

      KP_ASSERT(strlen(lpszLocalFName) + strlen(fname_ptr) + 1 + strlen(ftype) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcat(lpszLocalFName, fname_ptr);
         strcat(lpszLocalFName, ".");
         strcat(lpszLocalFName, ftype);
// PutLogMessage_(lpszLocalFName);
      }
   }

   if((lpszProgressMsg != null) && SUCCEEDED(retc))
   {
      KP_ASSERT(strlen(KP_MSG_DOWNLOADING_FILE) + strlen(fname_ptr) + strlen(ftype) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)lpszProgressMsg, KP_MSG_DOWNLOADING_FILE, fname_ptr, ftype);
// PutLogMessage_(lpszProgressMsg);
      }
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetInnoRegPar(unsigned char *lpszParValBuf, const unsigned char *lpszProdName, const unsigned char *lpszParName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszParValBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszProdName != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszParName != null, E_INVALIDARG, null, True);

// ----------------- registro rakto vardas
unsigned char key_name[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) strcpy(key_name, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\");
   KP_ASSERT(strlen(key_name) + strlen(lpszProdName) + 4 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcat(key_name, lpszProdName);
      strcat(key_name, "_is1");
   }

unsigned char key_name_wow64[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) strcpy(key_name_wow64, "Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\");
   KP_ASSERT(strlen(key_name_wow64) + strlen(lpszProdName) + 4 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcat(key_name_wow64, lpszProdName);
      strcat(key_name_wow64, "_is1");
   }
// PutLogMessage_("KpStApp::GetInnoRegPar() [%s]", key_name_wow64);

LONG retw = ERROR_SUCCESS;
HKEY key = NULL;
// ----------------- registro raktas HKEY_LOCAL_MACHINE
   if(SUCCEEDED(retc))
   {
      retw = RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
   }
   if(SUCCEEDED(retc)) if(key == NULL) retc = KP_E_KWD_NOT_FOUND;

DWORD data_type;
DWORD data_len;
   if(SUCCEEDED(retc))
   {
      data_len = KP_MAX_FNAME_LEN;
      retw = RegQueryValueEx(key, (const char *)lpszParName, NULL, &data_type, lpszParValBuf, &data_len);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
   }
   if(SUCCEEDED(retc)) if(data_type != REG_SZ) retc = KP_E_KWD_NOT_FOUND;
   if(SUCCEEDED(retc)) lpszParValBuf[data_len] = Nul;


// ------------------ kartojam su Wow6432Node
   if(retc == KP_E_KWD_NOT_FOUND)
   {
      retc = S_OK;

      retw = RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name_wow64, 0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc)) if(key == NULL) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc))
      {
         data_len = KP_MAX_FNAME_LEN;
         retw = RegQueryValueEx(key, (const char *)lpszParName, NULL, &data_type, lpszParValBuf, &data_len);
         if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
      }
      if(SUCCEEDED(retc)) if(data_type != REG_SZ) retc = KP_E_KWD_NOT_FOUND;
      if(SUCCEEDED(retc)) lpszParValBuf[data_len] = Nul;
   }

// ------------------ kartojam su HKEY_CURRENT_USER
   if(retc == KP_E_KWD_NOT_FOUND)
   {
      retc = S_OK;

      retw = RegCreateKeyEx(HKEY_CURRENT_USER, (const char *)key_name, 0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc)) if(key == NULL) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc))
      {
         data_len = KP_MAX_FNAME_LEN;
         retw = RegQueryValueEx(key, (const char *)lpszParName, NULL, &data_type, lpszParValBuf, &data_len);
         if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
      }
      if(SUCCEEDED(retc)) if(data_type != REG_SZ) retc = KP_E_KWD_NOT_FOUND;
      if(SUCCEEDED(retc)) lpszParValBuf[data_len] = Nul;
   }

// ------------------ kartojam su Wow6432Node
   if(retc == KP_E_KWD_NOT_FOUND)
   {
      retc = S_OK;

      retw = RegCreateKeyEx(HKEY_CURRENT_USER, (const char *)key_name_wow64, 0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc)) if(key == NULL) retc = KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc))
      {
         data_len = KP_MAX_FNAME_LEN;
         retw = RegQueryValueEx(key, (const char *)lpszParName, NULL, &data_type, lpszParValBuf, &data_len);
         if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
      }
      if(SUCCEEDED(retc)) if(data_type != REG_SZ) retc = KP_E_KWD_NOT_FOUND;
      if(SUCCEEDED(retc)) lpszParValBuf[data_len] = Nul;
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetInnoInstPath(unsigned char *lpszInstPathBuf, const unsigned char *lpszProdName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszInstPathBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszProdName != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetInnoRegPar(lpszInstPathBuf, lpszProdName, (const unsigned char *)"Inno Setup: App Path");

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetInnoUnInstCmd(unsigned char *lpszUninstPathBuf, const unsigned char *lpszProdName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszUninstPathBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszProdName != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetInnoRegPar(lpszUninstPathBuf, lpszProdName, (const unsigned char *)"UninstallString"); // "QuietUninstallString");

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, const unsigned char *lpszAppName, const unsigned char *lpszLicCode)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   KP_ASSERT(lpszAppName != null, E_INVALIDARG, null, True);

unsigned char inst_path_buf[KP_MAX_FNAME_LEN + 100];
   inst_path_buf[0] = Nul;
bool found = False;

// pradžioj ieškom ProdVer registre
   if((lpszLicCode != null) && SUCCEEDED(retc))
   {
long lic_id = 0L;
int prod_ver = 0;
      if(SUCCEEDED(retc)) retc = ScanLicTmp(&lic_id, &prod_ver, lpszLicCode);

      if(SUCCEEDED(retc))
      {
         retc = GetProdVerRegVariableStr(inst_path_buf, prod_ver, KPST_PRODVER_REG_KEY_ProdDir);
         if(SUCCEEDED(retc)) found = True;
         else if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
      }
   }

// neradom – ieškom Inno registre
   if((!found) && SUCCEEDED(retc))
   {
// Inno registre neieškom – dabar reikia rast tik lentyninius, senų reikia nerodyt
#if FALSE
      inst_path_buf[0] = Nul;
      retc = GetInnoInstPath(inst_path_buf, lpszAppName);
      if(retc == KP_E_KWD_NOT_FOUND)
      {
         inst_path_buf[0] = Nul;
//       KP_WARNING(retc, app_name_str);
//       retc = S_OK;
      }
#else
      retc = KP_E_KWD_NOT_FOUND;
#endif
   }

// ----------
HRESULT retc_sav = retc;
   if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;

// ----------
   if((ppiInstPath != NULL) /* && (inst_path_buf[0] != Nul) */ && SUCCEEDED(retc))
   {
      KP_NEWA(*ppiInstPath, KpChar, strlen(inst_path_buf) + 1);

// TODO: surasti sisteminę kodavimo lentelę
int ctbl = TV_MAIN_CTBL;

      if(SUCCEEDED(retc))
      {
         retc0 = KptStrEncode(*ppiInstPath, inst_path_buf, ctbl);
         if(FAILED(retc0))
         {
            KP_WARNING(retc0, inst_path_buf);
//          retc = S_OK;
         }
         (*ppiInstPath)[strlen(inst_path_buf)] = C_Nul;
      }
   }

   if((lpszInstPathBuf != null) && SUCCEEDED(retc))
   {
      lpszInstPathBuf[0] = Nul;
      KP_ASSERT(strlen(inst_path_buf) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcpy(lpszInstPathBuf, inst_path_buf);
   }

// ----------
   retc = retc_sav;

return(retc);
}


HRESULT KpStApp::GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, const KpGrpChk *GrpDownloadPars)
{
HRESULT retc = S_OK;

   KP_ASSERT(GrpDownloadPars != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetGrpInstPath(lpszInstPathBuf, ppiInstPath, GrpDownloadPars->m_lpszText, GrpDownloadPars->m_lpszLicCode);

return(retc);
}


HRESULT KpStApp::GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, /* const */ XmlNode *pCurNode)
{
HRESULT retc = S_OK;

   KP_ASSERT(pCurNode != NULL, E_INVALIDARG, null, True);

unsigned char *app_name_str = null;
   if(SUCCEEDED(retc)) retc = GetGrpItemAppName(&app_name_str, NULL, pCurNode, True);
   KP_ASSERT(app_name_str != null, KP_E_FILE_FORMAT, null, True);

unsigned char *lic_code = null;
   if(SUCCEEDED(retc)) retc = pCurNode->ExtractSubnodeContentsStr(XG_Licence, &lic_code);

   if(SUCCEEDED(retc)) retc = GetGrpInstPath(lpszInstPathBuf, ppiInstPath, app_name_str, lic_code);

   KP_DELETEA(app_name_str);
   KP_DELETEA(lic_code);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpUnInstCmd(unsigned char *lpszUnInstPathBuf, const unsigned char *lpszAppName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszAppName != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszUnInstPathBuf != null, E_INVALIDARG, null, True);

// -------------------------- nustatom meniu atnaujinimo blokavimo semaforą
// semaforas blokuojasi
// if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
//    m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();
bool refresh_sav = m_bGrpRefreshFlg;
   m_bGrpRefreshFlg = False;

// pradžioj ieškom ProdVer registre
bool found = False;
XmlNode *cur_node = NULL;
   if(SUCCEEDED(retc)) retc = GetGrpCfgItem(&cur_node, lpszAppName, m_pGrpCfgNode, True); // False);
   if((cur_node != NULL) && SUCCEEDED(retc))
   {
      retc = ExtractProdVerRegVariableStr(lpszUnInstPathBuf, cur_node, KPST_PRODVER_REG_KEY_Uninst);
      if(SUCCEEDED(retc)) found = True;
      else if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK; // KP_ERROR(KP_E_FILE_FORMAT, null);
   }

// neradom – ieškom Inno registre
   if((!found) && SUCCEEDED(retc))
   {
      lpszUnInstPathBuf[0] = Nul;
      if(SUCCEEDED(retc)) retc = GetInnoUnInstCmd(lpszUnInstPathBuf, lpszAppName);
      if(retc == KP_E_KWD_NOT_FOUND)
      {
         lpszUnInstPathBuf[0] = Nul;
//       KP_WARNING(retc, app_name_str);
//       retc = S_OK;
      }
   }

// ----------------- tikrinam, ar failas yra
FILE *test_file = NULL;
   if(SUCCEEDED(retc))
   {
      test_file = fopen((const char *)lpszUnInstPathBuf, "rb");
      if(test_file == NULL) retc = KP_E_FILE_NOT_FOUND;
      else
      {
         fclose(test_file);
         test_file = NULL;
      }
   }

// -----------------
   KP_ASSERT(strlen(lpszUnInstPathBuf) + strlen(" /VERYSILENT") < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcat(lpszUnInstPathBuf, " /VERYSILENT");

// -------------------------- atlaisvinam meniu atnaujinimo blokavimo semaforą
// semaforas blokuojasi
// if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
//    m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();
   m_bGrpRefreshFlg = (m_bGrpRefreshGlobalFlg?refresh_sav:False);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpLaunch(unsigned char *lpszLaunchBuf, KpChar **ppiLaunch, bool *pbInstalled, /* const */ XmlNode *pCurNode)
{
HRESULT retc = S_OK;

   KP_ASSERT(pCurNode != NULL, E_INVALIDARG, null, True);

// surandam {app}
KpChar *inst_path = NULL;
   if(SUCCEEDED(retc))
   {
      retc = GetGrpInstPath(null, &inst_path, pCurNode);
      if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
   }

// ištraukiam {launch}
KpChar *launch_path = NULL; // čia grąžinamas buferis, trinti reikia, jei ppiLaunch == NULL (t.y., negrąžinam)
bool found = False;

// pradžioj ieškom ProdVer registre
unsigned char launch_reg_buf[KP_MAX_FNAME_LEN + 1];
   launch_reg_buf[0] = Nul;
   if(SUCCEEDED(retc))
   {
      retc = ExtractProdVerRegVariableStr(launch_reg_buf, pCurNode, KPST_PRODVER_REG_KEY_Launch);
      if(SUCCEEDED(retc)) found = True;
      else if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK; // KP_ERROR(KP_E_FILE_FORMAT, null);
   }

   if(SUCCEEDED(retc))
   {
      if(found)
      {
         KP_NEWA(launch_path, KpChar, TvKpStrLen(KPST_GRP_PATH_PREFIX_W) + strlen(lpszaStartSelKwds[StartActionIx]) + strlen(launch_reg_buf) + 100);
         if(SUCCEEDED(retc))
         {
            TvKpStrCpy(launch_path, KPST_GRP_PATH_PREFIX_W);
            KptStrEncode(launch_path + TvKpStrLen(launch_path), lpszaStartSelKwds[StartActionIx], TV_MAIN_CTBL);
            KptStrEncode(launch_path + TvKpStrLen(launch_path), (const unsigned char *)":", TV_MAIN_CTBL);
            KptStrEncode(launch_path + TvKpStrLen(launch_path), launch_reg_buf, TV_MAIN_CTBL);
         }
      }

// neradom – ištraukiam <launch>
      else // if(found)
      {
KpChar *launch_val = NULL; // čia rodyklė į <launch> reikšmę, trinti nereikia
         if(SUCCEEDED(retc)) retc = pCurNode->ExtractSubnodeContents(XG_Launch, &launch_val);
//       KP_ASSERT(launch_val != NULL, KP_E_FILE_FORMAT, null, True); // nebūtinai
         if((launch_val == NULL) && SUCCEEDED(retc)) retc = KP_E_KWD_NOT_FOUND;

// ------------------------ radom <launch> – parsinam/konvertuojam
         if(SUCCEEDED(retc)) // if((launch_val != NULL) && SUCCEEDED(retc))
         {
// keisim galimą {app}
int launch_buf_len = KP_MAX_FNAME_LEN;
KpChar *launch_src = NULL;
            KP_NEWA(launch_src, KpChar, launch_buf_len + 1);

            KP_ASSERT(TvKpStrLen(launch_val) < launch_buf_len, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)) TvKpStrCpy(launch_src, launch_val);

            KP_NEWA(launch_path, KpChar, launch_buf_len + 1);

// ar yra kitokių makrokomandų, negu {app}?
            if(SUCCEEDED(retc))
               if(
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_FILE_W) != NULL) || // "{file}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_MPAR_W) != NULL) || // "{mpar}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_APPNAME_W) != NULL) || // "{appname}"
//                (TvKpStrStr(launch_src, KPST_GRP_MACRO_APP_W) != NULL) || // "{app}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_LAUNCH_W) != NULL) || // "{launch}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_SETUP_W) != NULL) || // "{setup}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_SETUPSIZE_W) != NULL) || // "{setupsize}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_LIC_W) != NULL) || // "{lic}"
                  (TvKpStrStr(launch_src, KPST_GRP_MACRO_PRC_W) != NULL) // "{prc}"
                )
                  KP_ERROR(KP_E_FILE_FORMAT, null);

//          KP_ASSERT((TvKpStrStr(launch_src, KPST_GRP_MACRO_APP_W) == NULL) || // "{app}"
//                (inst_path != NULL), KP_E_FILE_FORMAT, null, True);

// keičiam galimą {app}
            while(SUCCEEDED(retc))
            {
KpStGrpSubster subster(launch_path, launch_buf_len, launch_src, NULL, NULL,
                     NULL, NULL, NULL, inst_path, NULL,
                     NULL, NULL, NULL, NULL);
               if(SUCCEEDED(retc)) retc = subster.SubstGrpTpl();

// ar dar liko makrokomandų?
               if(SUCCEEDED(retc))
                  if(
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_FILE_W) == NULL) && // "{file}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_MPAR_W) == NULL) && // "{mpar}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_APPNAME_W) == NULL) && // "{appname}"
                     (TvKpStrStr(launch_path, KPST_GRP_MACRO_APP_W) == NULL) // && // "{app}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_LAUNCH_W) == NULL) && // "{launch}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_SETUP_W) == NULL) && // "{setup}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_SETUPSIZE_W) == NULL) && // "{setupsize}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_LIC_W) == NULL) && // "{lic}"
//                   (TvKpStrStr(launch_path, KPST_GRP_MACRO_PRC_W) == NULL) // "{prc}"
                   )
                     break; // neliko

               if(SUCCEEDED(retc)) TvKpStrCpy(launch_src, launch_path);
            }


// naikinam
            KP_DELETEA(launch_src);

         } // else // if((launch_val == NULL)

      } // else // if(found)

   } // if(SUCCEEDED(retc))

// ------------------------------ grąžinam
// TODO: perdaryt į Unicode arba bent jau išsitraukt sisteminį kodavimą
unsigned char launch_str_buf[KP_MAX_FNAME_LEN + 1];
   launch_str_buf[0] = Nul;
   if(((lpszLaunchBuf != null) || (pbInstalled != NULL)) && SUCCEEDED(retc))
      /* retc = */ KptStrDecode(launch_str_buf, launch_path, TV_MAIN_CTBL);

   if((lpszLaunchBuf != null) && SUCCEEDED(retc)) strcpy(lpszLaunchBuf, launch_str_buf);

   if(ppiLaunch != NULL){ if(SUCCEEDED(retc)) *ppiLaunch = launch_path; launch_path = NULL; }
   else KP_DELETEA(launch_path); // trinam tik jei negrąžinsim

// ------------------------ tikrinam, ar įdiegtas
   if((pbInstalled != NULL) && SUCCEEDED(retc))
   {
// paleidimo komandoje surandam {app} (numetam "tux:///KpStart:Start:")
const unsigned char *pnts = NULL;
      if(SUCCEEDED(retc))
      {
         pnts = strstr(launch_str_buf, KPST_GRP_MACRO_APP); // {app}
         if(pnts == null)
         {
            KP_ASSERT(strstr(launch_str_buf, KPST_GRP_PATH_PREFIX) == launch_str_buf, KP_E_FILE_FORMAT, launch_str_buf, True);
            if(SUCCEEDED(retc))
            {
               pnts = launch_str_buf + strlen(KPST_GRP_PATH_PREFIX);
               pnts = strchr(pnts, ':'); // "Start:", "StartAndClose:" etc.
               KP_ASSERT(pnts != null, KP_E_FILE_FORMAT, null, True);
            }
            if(SUCCEEDED(retc)) pnts++;
         }
      }

      if(SUCCEEDED(retc))
      {
         if(*pnts == '\"') pnts++; // numetam pradinę kabutę, jei yra
unsigned char *pntd = strchr(pnts, '\"');
         if(pntd != null) *pntd = Nul; // numetam galinę kabutę
      }

      *pbInstalled = False;
FILE *launch_file = NULL;
      if(SUCCEEDED(retc)) launch_file = fopen((const char *)pnts, "rb");
      if((launch_file != NULL) && SUCCEEDED(retc))
      {
         *pbInstalled = True;
         fclose(launch_file);
      }
   }

   KP_DELETEA(inst_path);

return(retc);
}


HRESULT KpStApp::GetGrpLaunch(unsigned char *lpszLaunchBuf, KpChar **ppiLaunch, bool *pbInstalled, const unsigned char *lpszAppName)
{
HRESULT retc = S_OK;

XmlNode *cur_node = NULL;
   if(SUCCEEDED(retc))
   {
      retc = GetGrpCfgItem(&cur_node, lpszAppName, m_pGrpCfgNode, True); // False);
      if((cur_node == NULL) && SUCCEEDED(retc)) retc = KP_E_OBJ_NOT_FOUND;
   }
   if(SUCCEEDED(retc))
      retc = GetGrpLaunch(lpszLaunchBuf, ppiLaunch, pbInstalled, cur_node);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GetGrpItemAppName(unsigned char **plpszAppName, KpChar **ppiAppName, /* const */ XmlNode *pCurNode, bool bInnoSetup)
{
HRESULT retc = S_OK;

   KP_ASSERT(bInnoSetup || (plpszAppName == NULL), E_INVALIDARG, null, False); // ne Inno užkoduoto appname neišeina perduot per (char *)
   KP_ASSERT(pCurNode != NULL, E_INVALIDARG, null, True);

bool found = False;

// ------------------ pradžiai tiesiog išsitraukiam <appname> reikšmę
KpChar *app_name_i = NULL;
   if(SUCCEEDED(retc)) retc = pCurNode->ExtractSubnodeContents(XG_AppName, &app_name_i);
   KP_ASSERT(app_name_i != NULL, KP_E_FILE_FORMAT, null, True);

// -------------- Inno Setupas saugoja produkto vardą pagal generavimo metu buvusią lokalę
// susirandam tą lentelę
int ctbl = TV_MAIN_CTBL;
bool found_lng = False;
// lenkiškus produktus gaminam lietuviškoj lokalėj
// if(SUCCEEDED(retc)) retc = TestLang(app_name_i, KP_LNG_POL, &found_lng);
// if(found_lng && SUCCEEDED(retc)) ctbl = LangToCtbl[KpLangPl_1250];

   found_lng = False;
   if(SUCCEEDED(retc)) retc = TestLang(app_name_i, KP_LNG_RUS, &found_lng);
   if(found_lng && SUCCEEDED(retc)) ctbl = LangToCtbl[KpLangRu_1251];

// ------------------ pradžioj pagal <lic> ieškom ProdVer registre
unsigned char prod_name_buf[KP_MAX_FNAME_LEN + 1];
   prod_name_buf[0] = Nul;

   if(SUCCEEDED(retc))
   {
      retc = ExtractProdVerRegVariableStr(prod_name_buf, pCurNode, KPST_PRODVER_REG_KEY_ProdName);
      if(SUCCEEDED(retc)) found = True;
      else if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK; // KP_ERROR(KP_E_FILE_FORMAT, null);
   }

   if(found)
   {
      app_name_i = NULL;
      KP_NEWA(app_name_i, KpChar, strlen(prod_name_buf) + 1);

// -------------- Inno Setupas saugoja produkto vardą pagal generavimo metu buvusią lokalę
// koduojam lentele pagal kalbą
      if(SUCCEEDED(retc)) KptStrEncode(app_name_i, prod_name_buf, ctbl);
// PutLogMessage_("GetGrpItemAppName() %d [%s]", ctbl, prod_name_buf);
   }

// -----------------------
// jei neradom, tiesiog grąžinam anksčiau ištrauktą <appname> reikšmę
   if((ppiAppName != NULL) && SUCCEEDED(retc))
   {
      KP_NEWA(*ppiAppName, KpChar, TvKpStrLen(app_name_i) + 1);

      if(SUCCEEDED(retc)) TvKpStrCpy(*ppiAppName, app_name_i);
   }

   if((plpszAppName != NULL) && SUCCEEDED(retc))
   {
// -------------- Inno Setupas saugoja produkto vardą pagal generavimo metu buvusią lokalę
      KP_NEWA(*plpszAppName, unsigned char, TvKpStrLen(app_name_i) + 1);

      if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(*plpszAppName, app_name_i, bInnoSetup?ctbl:TV_MAIN_CTBL);

// PutLogMessage_("GetGrpItemAppName() %d [%s]", ctbl, *plpszAppName);
// if(ctbl == 73) PutLogMessage_("GetGrpItemAppName() [%s]", *plpszAppNameBuf);
   }


// ----------------------
   if(found) KP_DELETEA(app_name_i); // trinam, tik jei buvo ištraukta iš Inno registro
   app_name_i = NULL;

return(retc);
}



// -----------------------------------------
HRESULT KpStApp::SaveVar(const unsigned char *lpszPars)
{
HRESULT retc = S_OK;

// PutLogMessage_("KpStApp::SaveVar() [%s]", lpszPars);

   KP_ASSERT(lpszPars != null, E_INVALIDARG, null, True);

int prod_ver = 0;
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

unsigned char *par_buf = null;
   KP_NEWA(par_buf, unsigned char, strlen(lpszPars) + 1);
   if(SUCCEEDED(retc)) strcpy(par_buf, lpszPars);

unsigned char *pntd = null;
   if(SUCCEEDED(retc)) pntd = strchr(par_buf, '=');
   KP_ASSERT(pntd != null, E_INVALIDARG, par_buf, True);

   if(SUCCEEDED(retc))
   {
      *pntd++ = Nul;
      /* retc = */ CutInitTrailSpcs(par_buf);
      /* retc = */ CutInitTrailSpcs(pntd);

      /* retc = */ SetProdVerRegVariableStr(pntd, prod_ver, par_buf);
   }

   KP_DELETEA(par_buf);

return(retc);
}

// -----------------------------------------
HRESULT KpStApp::ExtractGrpLicProdVer(unsigned char **plpszLicCode, long *piLicID, int *piProdVer, /* const */ XmlNode *pCurNode)
{
HRESULT retc = S_OK;
unsigned char *val_str = null;

   KP_ASSERT(pCurNode != NULL, E_INVALIDARG, null, True);
// KP_ASSERT(pCurNode->m_iNodeTag == XG_Item, E_INVALIDARG, null, True);

   if(plpszLicCode != NULL) *plpszLicCode = null;
   if(piLicID != NULL) *piLicID = 0L;
   if(piProdVer != NULL) *piProdVer = 0L;

   if(SUCCEEDED(retc)) retc = pCurNode->ExtractSubnodeContentsStr(XG_Licence, &val_str);
// KP_ASSERT(val_str != null, KP_E_FILE_FORMAT, null, True);
   if(val_str == null) retc = KP_E_KWD_NOT_FOUND;

// išsitraukiam ProdVer
   if((val_str != null) && ((piLicID != NULL) || (piProdVer != NULL)) && SUCCEEDED(retc))
   {
long lic_id = 0L;
int prod_ver = 0;
      if(SUCCEEDED(retc)) retc = ScanLicTmp(&lic_id, &prod_ver, val_str);
// PutLogMessage_("%x %d %d", lic_id, KpstXRand(lic_id & 0xFFFF), prod_ver);

      if(piLicID != NULL) *piLicID = lic_id;
      if(piProdVer != NULL) *piProdVer = prod_ver;
   }

// grąžinam <lic> / trinam <lic> buferį
   if(plpszLicCode != NULL){ *plpszLicCode = val_str; val_str = null; }
   else KP_DELETEA(val_str);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::ExtractProdVerRegVariableStr(unsigned char *lpszValBuf,  /* const */ XmlNode *pCurNode, const unsigned char *lpszVarName)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszValBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(pCurNode != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszVarName != null, E_INVALIDARG, null, True);

int prod_ver = 0;
   if(SUCCEEDED(retc)) retc = ExtractGrpLicProdVer(NULL, NULL, &prod_ver, pCurNode);
   if(SUCCEEDED(retc)) retc = GetProdVerRegVariableStr(lpszValBuf, prod_ver, lpszVarName);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::WaitTilWndCloses(const unsigned char *lpszWndName, const unsigned char *lpszProdName)
{
HRESULT retc = S_OK;

// ------------------------- tikrinam, ar uždarytas langas
   if((lpszWndName != null) && SUCCEEDED(retc))
   {
HWND wnd = NULL;
unsigned char msg_buf[KP_MAX_FNAME_LEN + 200];
      sprintf((char *)msg_buf, KPST_MSG_CLOSE_PROG_WND, (lpszProdName != null)?lpszProdName:lpszWndName);
      do
      {
         wnd = GetWindowByName(lpszWndName, False);
         if(wnd != NULL) retc = KpMsgOut(msg_buf, IDI_WARNING, KP_MB_GERAI_ATSAUKTI);

      } while((wnd != NULL) && SUCCEEDED(retc));
   }

return(retc);
}

// -----------------------------------------
#define KPST_PRODGRP_DOWNLOAD_RCV_BUF_SIZE ((100L * 1024) + 1) // 100001L // 8001L // KP_MAX_FILE_LIN_LEN // 20000 //
#define KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT 10 // 100
#define KPST_PRODGRP_PRC_STEP 5

HRESULT KpStApp::GrpDownloadSingle(KpGrpChk *GrpDownloadPars, HWND hProgWnd, long *plReceived, long lFullSize, const unsigned char *lpszWndName, const unsigned char *lpszProdName, bool bOutMsg)
{
HRESULT retc = S_OK;

// PutLogMessage_("KpStApp::GrpDownloadSingle() 1");

   KP_ASSERT(GrpDownloadPars != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(plReceived != NULL, E_INVALIDARG, null, True);

// ----------------------------- priėmimo buferis
unsigned char *rcv_buf = null;
   KP_NEWA(rcv_buf, unsigned char, KPST_PRODGRP_DOWNLOAD_RCV_BUF_SIZE + 100);

// ----------- tik pažymėtus siuntimui
unsigned char local_fname[KP_MAX_FNAME_LEN + 1];
   local_fname[0] = Nul;

   if(SUCCEEDED(retc)) if(GrpDownloadPars->m_bChecked)
   {
// strcpy(GrpDownloadPars->m_lpszDownLoadFName, "http://new.tev.lt/content.php");
// strcpy(GrpDownloadPars->m_lpszDownLoadFName, "http://mindep.puslapiai.lt/index.html");
// strcpy(GrpDownloadPars->m_lpszDownLoadFName, "http://mindep.puslapiai.lt/index.php");
// strcpy(GrpDownloadPars->m_lpszDownLoadFName, "http://siuntiniai.tev.lt/updates/index.php");
// strcpy(GrpDownloadPars->m_lpszDownLoadFName, "http://siuntiniai.tev.lt/updates/temp/WinLED_vadovas.htm");

// ----------- išsitraukiam source failo vardą ir termometro tekstą
unsigned char str_msg[KP_MAX_FNAME_LEN + 1];
      if(SUCCEEDED(retc)) retc = GetGrpLocalFName(local_fname, str_msg, GrpDownloadPars->m_lpszDownLoadFName);

// PutLogMessage_("KpStApp::GrpDownloadSingle() local_fname: %s", local_fname);

// ----------------------------- vieno failo termometro ant ikonos parametrai
long full_size_single = Maxlong;
   if(SUCCEEDED(retc)) full_size_single = GrpDownloadPars->m_lDownLoadFSize;
long received_single = 0L;
long prev_prc = -KPST_PRODGRP_PRC_STEP;

// ---------------------------------------
      if(SUCCEEDED(retc))
#ifdef KPST_PRODGRP_NODOWNLOAD // testuojam tik diegimą
         if(!GrpDownloadPars->m_bSetupFl) // kraunam tik nediegiamus (paveiksliukus etc.)
#endif // #ifndef KPST_GRP_NODOWNLOAD // testuojam diegimą
      {
// parodom termometro tekstą
         if((hProgWnd != NULL) && SUCCEEDED(retc)) retc = KpSetProgressTxt(hProgWnd, str_msg, (const unsigned char *)"     0 kB   0 kbps");

// parodom ikonos termometrą
         if(SUCCEEDED(retc)) retc = KpGrSetProgressPrc(GrpDownloadPars->m_lpszText, received_single * 100 / full_size_single);
         if(SUCCEEDED(retc)) retc = RefreshGrpMenu(False);

// ----------- sukuriam priėmimo failą
         if(SUCCEEDED(retc)) retc = CreatePath(local_fname, True);
HANDLE local_file = INVALID_HANDLE_VALUE;
         if(SUCCEEDED(retc))
         {
            local_file = CreateFile((const char *)local_fname, GENERIC_WRITE, FILE_SHARE_WRITE,
               0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
            KP_ASSERT(local_file != INVALID_HANDLE_VALUE, KP_E_DIR_ERROR, m_lpszGrpCfgFName, True);
         }

// ----------------------------- socketo kūrimas
KpSocket *sock_ptr = NULL;
         KP_NEWO(sock_ptr, KpSocket);

// ------------------------------ jungiamės
         if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(GrpDownloadPars->m_lpszDownLoadFName, bOutMsg);
         if(SUCCEEDED(retc)) retc = sock_ptr->Connect(bOutMsg);

// ------------------------------ siunčiam užklausą
         if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, sock_ptr->m_PackedUrl.m_lpszFileName, bOutMsg,
                                                                     0L, True, (const unsigned char *)"",
                                                                     HTTP_GET_REQ_TPL_BIN);
// ---------------------- inicijuojam kbps skaitiklius
long read = KPST_PRODGRP_DOWNLOAD_RCV_BUF_SIZE;

DWORD buffer_start_times[KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT];
long buffer_read_amounts[KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT];
         if((hProgWnd != NULL) && SUCCEEDED(retc))
         {
            buffer_start_times[0] = GetTickCount();
            buffer_read_amounts[0] = 0L;
            for(int ii = 1; ii < KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT; ii++)
            {
               buffer_start_times[ii] = buffer_start_times[0];
               buffer_read_amounts[ii] = 0L;
            }
         }

// ---------------------- ar reikia užkoduoti?
bool encode_fl = False;
unsigned char *file_buf = null;
long file_buf_len = 0;
         if(SUCCEEDED(retc))
         {
            if(strstr(GrpDownloadPars->m_lpszDownLoadFName, KPST_ENCODE_FILE_PATTERN) != null)
#ifdef IBSHT_ENCODED
               encode_fl = False; // failas gaunamas jau užkoduotas
            else
               encode_fl = True;
         }
         if(SUCCEEDED(retc)) if(strstr(local_fname, ".exe") != null) encode_fl = False; // exekų nekoduojam – juos vis tiek reikės paleidinėt iš disko
#else
               encode_fl = True; // atkoduojam užkoduotą failą
         }
#endif

// ---------------------- priimam atsakymą su turiniu
         if(SUCCEEDED(retc))
         {
            retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, False); // True);
            if(FAILED(retc))
            {
//             KP_ERROR(retc, GrpDownloadPars->m_lpszDownLoadFName);
               if(bOutMsg) KpMsgOut(KP_MSG_TRANS_ERR_1, IDI_ERROR, KP_MB_TESTI);
            }
         }
// PutLogMessage_("KpStApp::GrpDownloadSingle() lpszFileName: %s rcv_buf: >>>%s<<<", sock_ptr->m_PackedUrl.m_lpszFileName, rcv_buf);
// PutLogMessage_("KpStApp::GrpDownloadSingle() 1 read: %d received: %d full: %d", read, received_single, full_size_single);

// -------------------- rašom gabalais
long received_file = 0L;
         while((read > 0) && SUCCEEDED(retc))
         {

// #ifdef IBSHT_ENCODED
            if(encode_fl) // pradžiai sukaupiam buferyje, po to užkoduosim ir įrašysim
            {
unsigned char *new_file_buf = null;
               KP_NEWA(new_file_buf, unsigned char, file_buf_len + read + 4 + 1); // padidinam iki 4 baitų ribos
               if(file_buf != null) memcpy(new_file_buf, file_buf, file_buf_len);
               memcpy(new_file_buf + file_buf_len, rcv_buf, read);
               KP_DELETEA(file_buf);
               file_buf = new_file_buf;
               file_buf_len += read;
            }
            else
// #endif
            {
DWORD written = 0;
               KP_ASSERT(WriteFile(local_file, rcv_buf, read, &written, NULL), KP_E_FERROR, local_fname, True);
               KP_ASSERT(written == read, KP_E_FERROR, local_fname, False);
            }

// ------------ pastumiam termometrą
long total_sample_read = 0L;
            if((hProgWnd != NULL) && SUCCEEDED(retc))
            {
               buffer_start_times[0] = GetTickCount();
               buffer_read_amounts[0] = read;
               for(int ii = 0; ii < KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT; ii++) total_sample_read += buffer_read_amounts[ii];

unsigned char str_out[100];
int divider = buffer_start_times[0] - buffer_start_times[KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT - 1];
               if(divider == 0) divider = 1;
               if(SUCCEEDED(retc)) sprintf((char *)str_out, "%6ld kB %3ld kbps",  // "%3ld%% %3ld bps", (received_file += read) * 100 / GrpDownloadPars->m_lDownLoadFSize, 30);
                                       (received_file += read) / 1000, // 1024,
                                       total_sample_read * 8L / divider);
               if(SUCCEEDED(retc)) retc = KpSetProgressTxt(hProgWnd, str_msg, str_out);
               if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(hProgWnd, *plReceived += read, lFullSize);
               if(SUCCEEDED(retc))
                  for(int ii = KPST_PRODGRP_LOAD_TIMES_SAMPLE_CNT - 2; ii >= 0; ii--)
                  {
                     buffer_read_amounts[ii + 1] = buffer_read_amounts[ii];
                     buffer_start_times[ii + 1] = buffer_start_times[ii];
                  }
            }

// ---------------- pergeneruojam meniu progreso slankiklius {prc}
            if(SUCCEEDED(retc))
            {
long prc = 0L;
               received_single += read;
               if(full_size_single < Maxlong / 100L) prc = received_single * 100L / full_size_single;
               else prc = received_single / (full_size_single / 100L);

               if((prc >= prev_prc + KPST_PRODGRP_PRC_STEP) || ((prc > prev_prc) && (prc == 100L)))
               {
                  retc = KpGrSetProgressPrc(GrpDownloadPars->m_lpszText, prc);
// PutLogMessage_("KpStApp::GrpDownloadSingle() 2 read: %d received: %d full: %d prc: %d", read, received_single, full_size_single, prc);
                  if(SUCCEEDED(retc)) retc = RefreshGrpMenu(False);
                  prev_prc = prc;
               }
            }

// ------------ priimam tolesnį gabalą
            read = KPST_PRODGRP_DOWNLOAD_RCV_BUF_SIZE;
            if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpRest(rcv_buf, &read, True);

            if(SUCCEEDED(retc)) retc = KpSleep(100); // gaudom WM_QUIT

         } // while((read > 0) && SUCCEEDED(retc))

// ------------------------------ naikinam socketą
         KP_DELETE(sock_ptr);

#if TRUE // #ifdef IBSHT_ENCODED
         if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
            m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();

         if(encode_fl && SUCCEEDED(retc))
         {
// ---------------- užkoduojam buferį
            KP_ASSERT(file_buf != null, KP_E_SYSTEM_ERROR, local_fname, True);

long entry_id = 0L; // TODO: čia įkomponuot kažkaip failo pavadinimą ar ilgį (lzdsht čia naudojamas lEntryId)

#  if FALSE // KpHp11 iškvietimai kažko laužia multithreadinį Gecko streamų kūrimą
            KP_ASSERT(file_buf_len < (Maxint + 1) * 4, KP_E_BUFFER_OVERFLOW, local_fname, False); // perkoduoja tik tiek, galas lieka neperkoduotas

// PutLogMessage_("KpStApp::GrpDownloadSingle() %x %x %d %d [%s]", retc, file_buf, file_buf_len, MemBankObj[KP11_BLOCK_PROCESSING / 2], local_fname);

static KpRcPars rc_pars;
            if(SUCCEEDED(retc))
            {
               rc_pars.iOpCode = KP_RC_ENCODE_ENTRY;
               rc_pars.iParBlSize = sizeof(rc_pars);
               rc_pars.enc.iDataLen = ((file_buf_len + 4) / 4) * 4;
               rc_pars.enc.pData = file_buf;
               rc_pars.enc.lCtrl = entry_id;

               retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
            }
#  else
int prod_ver = 0;
            if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

//          if(SUCCEEDED(retc)) retc = EnctBufMed(file_buf, file_buf_len, prod_ver, entry_id);
            if(SUCCEEDED(retc)) retc = EnctBufInc(file_buf, file_buf_len, prod_ver, entry_id,
#     ifdef IBSHT_ENCODED
               True);
#     else
               False); // atkoduojam užkoduotus
#     endif
#  endif

// ---------------- rašom užkoduotą buferį į failą
DWORD written = 0;
            KP_ASSERT(WriteFile(local_file, file_buf, file_buf_len, &written, NULL), KP_E_FERROR, local_fname, True);
            KP_ASSERT(written == file_buf_len, KP_E_FERROR, local_fname, False);
         }

// ---------------- naikinam buferį
         if(SUCCEEDED(retc)) KP_DELETEA(file_buf); // jeigu iš ExecRemoteCall() grįžo su klaida, buferio netrinam – kphp11 gal dar jo reikia

         if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
            m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();
#endif

// ------------- uždarom priėmimo failą
         if(local_file != INVALID_HANDLE_VALUE)
         {
BOOL retv = CloseHandle(local_file);
            KP_ASSERT(retv, KP_E_FERROR, m_lpszGrpCfgFName, True);
         }
         local_file = INVALID_HANDLE_VALUE;
      }
// ----------------------

// -------------------------
      if(SUCCEEDED(retc)) if(GrpDownloadPars->m_bSetupFl)
      {
// ------------------------- tikrinam, ar uždarytas langas
         retc = WaitTilWndCloses(lpszWndName, lpszProdName);

// ------------------------- diegiam
HANDLE hproc = NULL;
unsigned char cmd_line[KP_MAX_FNAME_LEN + 100];
         strcpy(cmd_line, local_fname);
         strcat(cmd_line, " /VERYSILENT");
         if(SUCCEEDED(retc)) retc = StartProcess(cmd_line, KP_CUR_DIR, NULL, &hproc, SW_SHOWNORMAL);

// ---------------------------- laukiam kol pasibaigs
DWORD exit_code = ~STILL_ACTIVE;
         if(SUCCEEDED(retc))
         {
            do
            {
               if(SUCCEEDED(retc)) KpSleep(500);
               KP_ASSERT(GetExitCodeProcess(hproc, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);
            } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));
         }

// ------------------- išsitraukiam diegimo katalogą
unsigned char inst_path[KP_MAX_FNAME_LEN + 100];
         inst_path[0] = Nul;
         if((GrpDownloadPars->m_lpszLicCode[0] != Nul) && SUCCEEDED(retc)) // tik jei buvo perduotas lic. kodas
         {
//          retc = GetInnoInstPath(inst_path, GrpDownloadPars->m_lpszText);
            retc = GetGrpInstPath(inst_path, NULL, GrpDownloadPars);
// PutLogMessage_("[%s] [%s] [%s]", GrpDownloadPars->m_lpszText, inst_path, GrpDownloadPars->m_lpszLicCode);

            if(retc == KP_E_KWD_NOT_FOUND)
            {
//             KP_ERROR(retc, GrpDownloadPars->m_lpszText);

               retc = S_OK;

static unsigned char format_str[KP_MAX_FILE_LIN_WDT + 200];
// static unsigned char str_buf[KP_MAX_FILE_LIN_WDT + 200];
static KpChar str_buf_i[KP_MAX_FILE_LIN_WDT + 200];
               KP_ASSERT(strlen(KP_MSG_NOTINST_S) + TvKpStrLen(GrpDownloadPars->m_iazText) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
               if(SUCCEEDED(retc)) strcpy(format_str, KP_MSG_NOTINST_S);
unsigned char *pntd = null;
               if(SUCCEEDED(retc)) pntd = strstr(format_str, "%s");
               KP_ASSERT(pntd != null, KP_E_SYSTEM_ERROR, null, True);
               if(SUCCEEDED(retc)) *pntd++ = Nul;
//             if(SUCCEEDED(retc)) sprintf((char *)str_buf, KP_MSG_NOTINST_S, GrpDownloadPars->m_lpszText);
               if(SUCCEEDED(retc)) KptStrEncode(str_buf_i, format_str, LangToCtbl[iMsgLangOff]);
               if(SUCCEEDED(retc)) TvKpStrCat(str_buf_i, GrpDownloadPars->m_iazText);
               if(SUCCEEDED(retc)) KptStrEncode(str_buf_i + TvKpStrLen(str_buf_i), pntd + 1, LangToCtbl[iMsgLangOff]);
//             if(SUCCEEDED(retc)) KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
               if(SUCCEEDED(retc)) KpMsgOut(str_buf_i, IDI_ERROR, KP_MB_TESTI);
            }
            else if(SUCCEEDED(retc))
            {
// KpMsgOutF("KpStApp::GrpDownloadSingle(): Dabar aktyvuosim");
// -------------------- aktyvuojam licenciją
               strcpy(cmd_line, inst_path);
               strcat(cmd_line, "\\registr.exe ");
               strcat(cmd_line, GrpDownloadPars->m_lpszLicCode);
// PutLogMessage_("GrpDownLoad(): %s", cmd_line);
               retc = StartProcess(cmd_line, inst_path, NULL, &hproc, SW_SHOWNORMAL,
                           False, True, False);
               if(retc == KP_E_FILE_NOT_FOUND)
               {
                  KpMsgOut(KP_MSG_NOTINST_DELETE, IDI_ERROR, KP_MB_TESTI);
                  retc = S_OK;
               }
               else if(FAILED(retc)) retc = S_OK; // KP_ERROR(retc, null); // būna klaidos apie elevacijos reikalingumą

               if(SUCCEEDED(retc))
               {
                  do
                  {
                     if(SUCCEEDED(retc)) KpSleep(500);
                     KP_ASSERT(GetExitCodeProcess(hproc, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);
                  } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));
               }

            } // else // if(retc == KP_E_KWD_NOT_FOUND) // retc = GetInnoInstPath(inst_path, GrpDownloadPars->m_lpszText);

         } // if((GrpDownloadPars->m_lpszLicCode[0] != Nul) && SUCCEEDED(retc)) // tik jei buvo perduotas lic. kodas

         if(SUCCEEDED(retc)) retc = KpGrSetProgressPrc(GrpDownloadPars->m_lpszText, -1);
         if(SUCCEEDED(retc)) retc = RefreshGrpMenu(False);

      } // if(GrpDownloadPars->m_bSetupFl)

// ---------------------------- trinam diegimo ar nepavykusį failą
bool setup_fl = False;
      if(GrpDownloadPars != NULL) setup_fl = GrpDownloadPars->m_bSetupFl;
      if(setup_fl || FAILED(retc))
      {
         retc = S_OK; // naikinam einamojo failo siuntimo klaidą

#ifndef KPST_PRODGRP_NODOWNLOAD // testuojam diegimą
         if(local_fname[0] != Nul) KP_ASSERT(DeleteFile((const char *)local_fname), KP_E_DIR_ERROR, GetLastError(), False);
#endif
      } // if(GrpDownloadPars->m_bSetupFl)

   } // if(GrpDownloadPars->m_bChecked)

// -------------------- nuimam dubliavimo blokavimą
// laukiam, kol atsilaisvins m_GrpDownloadFNameList
   while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
   m_bGrpDownloadListProcessing = True;

   if((m_GrpDownloadFNameList != NULL) && SUCCEEDED(retc))
   {
KpTreeEntry *setup_entry = NULL;
KpTreeEntry *name_list = (KpTreeEntry *)m_GrpDownloadFNameList;
      KP_ASSERT(name_list != NULL, E_POINTER, null, True);
      if(SUCCEEDED(retc)) retc = name_list->SearchTreeEntry(local_fname, TvStrCmpStrict_, &setup_entry, NULL);
      if((setup_entry != NULL) && SUCCEEDED(retc))
      {
KpTreeEntry *next_entry = setup_entry->m_pNextBrother;
         retc = DeleteKpTreeEntry(setup_entry);
         if(setup_entry == m_GrpDownloadFNameList) m_GrpDownloadFNameList = next_entry;
      }
   }

   m_bGrpDownloadListProcessing = False;

// ---------------------------
   KP_DELETEA(rcv_buf);

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::GrpDownLoad(bool bMainThread, const unsigned char *lpszWndName, const unsigned char *lpszProdName)
{
HRESULT retc = S_OK;

// ----------- skaičiuojam visų parsisiųstinų failų suminį ilgį termometrui
long full_size = 0L;
   if(SUCCEEDED(retc)) retc = CountFullGrpSize(&full_size);

   if((full_size > 0) && SUCCEEDED(retc))
   {
// ----------- išvedam termometro langą
HWND prog_wnd = NULL;
      if(bMainThread && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = KpCreateProgressWnd(&prog_wnd, KP_MSG_DOWNLOADING, Maxint, full_size);
         KP_ASSERT(prog_wnd, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, 0L, full_size);
      }

// ----------- ciklinam per m_aGrpDownLoads
long received = 0L;
KpTreeEntry *cur_entry = m_aGrpDownLoads;
      while((cur_entry != NULL) && SUCCEEDED(retc))
      {
KpGrpChk *cur_val = (KpGrpChk *)cur_entry->GetValue();
         KP_ASSERT(cur_val != NULL, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(cur_entry->GetValSize() >= sizeof(KpGrpChk), KP_E_SYSTEM_ERROR, null, True);

         if(SUCCEEDED(retc)) retc = GrpDownloadSingle(cur_val, prog_wnd, &received, full_size, lpszWndName, lpszProdName, False);

// ------------ kitas sąrašo elementas
//       if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild((KpTreeEntry **)&cur_entry);
         if(SUCCEEDED(retc)) cur_entry = (XmlNode *)cur_entry->m_pFirstChild;

      } // while((cur_entry != NULL) && SUCCEEDED(retc))

// ------------ pabaigiam termometro rodymą
// ------------ pabaigiam termometro rodymą
      if(bMainThread && SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, received, full_size);
         if(SUCCEEDED(retc)) KpSleep(300);
         if(SUCCEEDED(retc)) retc = KillProgressWnd(prog_wnd);
      }

   } // if((full_size > 0) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------
HRESULT KpStApp::DecodeAppNameUTF8toStr(unsigned char *lpszAppName, const unsigned char *lpszAppNameUTF8, bool bInnoSetup)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszAppNameUTF8 != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszAppNameUTF8) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, lpszAppNameUTF8, True);
   if(SUCCEEDED(retc))
   {
// kopijuojam perkoduodami iš UTF-8 į Win-1257
#if FALSE
UniChar *utf16_buf = NULL;
      KP_NEWA(utf16_buf, UniChar, KP_MAX_FILE_LIN_WDT + 1);

      if(SUCCEEDED(retc)) /* retc = */ KptUTF8ToUnicode(utf16_buf, lpszAppNameUTF8);

      if(SUCCEEDED(retc)) /* retc = */ KptUnicodeToStr(lpszAppNameWin1257, utf16_buf, TV_MAIN_CTBL);

      KP_DELETEA(utf16_buf);
#else
KpChar *istr_buf = NULL;
      KP_NEWA(istr_buf, KpChar, KP_MAX_FILE_LIN_WDT + 1);

      if(SUCCEEDED(retc)) /* retc = */ DecodeKpStrUnicode(istr_buf, KP_MAX_FILE_LIN_WDT, lpszAppNameUTF8, UC_UTF_8);

int ctbl = TV_MAIN_CTBL; // TODO: išsitraukti kompo standartinę lentelę
      if(bInnoSetup)
      {
bool found = False;
         if(SUCCEEDED(retc)) retc = TestLang(istr_buf, KP_LNG_RUS, &found);
         if(found && SUCCEEDED(retc)) ctbl = LangToCtbl[KpLangRu_1251];
      }

      if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(lpszAppName, istr_buf, ctbl);

      KP_DELETEA(istr_buf);
#endif
   }

return(retc);
}


// -----------------------------------
HRESULT KpStApp::AppendGrpDownloadThreadListEntry(DWORD lCurThread)
{
HRESULT retc = S_OK;

// ------------
// laukiam, kol atsilaisvins m_GrpDownLoadThreadList
   while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
   m_bGrpDownloadListProcessing = True;

// atsižymim threadą – blokuojam pagrindinio threado meniu atnaujinimą
KpTreeEntry *thread_entry = NULL;
   KP_NEWO(thread_entry, KpTreeEntry(&lCurThread, sizeof(lCurThread), NULL));
   if(SUCCEEDED(retc))
   {
      if(m_GrpDownLoadThreadList != NULL)
      {
KpTreeEntry *thread_list = (KpTreeEntry *)m_GrpDownLoadThreadList;
         KP_ASSERT(thread_list != NULL, E_POINTER, null, True);
         if(SUCCEEDED(retc)) retc = thread_list->AppendBrother(thread_entry);
      }
      else m_GrpDownLoadThreadList = thread_entry;
      thread_entry = NULL;
   }
   else KP_DELETE(thread_entry);

   m_bGrpDownloadListProcessing = False;

return(retc);
}


// -----------------------------------
HRESULT KpStApp::DeleteGrpDownloadThreadListEntry(DWORD lCurThread)
{
HRESULT retc = S_OK;

// laukiam, kol atsilaisvins m_GrpDownLoadThreadList
   while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
   m_bGrpDownloadListProcessing = True;

// naikinam atsižymėjimą
   KP_ASSERT(sizeof(DWORD) == sizeof(long), KP_E_SYSTEM_ERROR, null, True);

KpTreeEntry *thread_entry = NULL;
KpTreeEntry *thread_list = (KpTreeEntry *)m_GrpDownLoadThreadList;
   KP_ASSERT(thread_list != NULL, E_POINTER, null, True);
   if(SUCCEEDED(retc))
      retc = thread_list->SearchTreeEntry(&lCurThread, KpCompareLong, &thread_entry, NULL);
   KP_ASSERT(thread_entry != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
KpTreeEntry *next_entry = thread_entry->m_pNextBrother;
      retc = DeleteKpTreeEntry(thread_entry);
      if(thread_entry == m_GrpDownLoadThreadList) m_GrpDownLoadThreadList = next_entry;
   }
   thread_entry = NULL;

   m_bGrpDownloadListProcessing = False;

return(retc);
}


// -----------------------------------------
#if FALSE
HRESULT KpStApp::DumpGrpDownloadThreadList(unsigned char *lpszOutStrBuf, bool bSetSemaphore)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszOutStrBuf != null, E_INVALIDARG, null, True);

// laukiam, kol atsilaisvins m_GrpDownLoadThreadList
   if(bSetSemaphore)
   {
      while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
      m_bGrpDownloadListProcessing = True;
   }

unsigned char *pntd = lpszOutStrBuf;
   if(SUCCEEDED(retc)) *pntd = Nul;

KpTreeEntry *cur_node = (KpTreeEntry *)m_GrpDownLoadThreadList;

#if FALSE
   KP_ASSERT(strlen(lpszOutStrBuf) + MAX_LONG_HEX_DIGITS + 2 + MAX_LONG_HEX_DIGITS + 2 + MAX_LONG_HEX_DIGITS + 2 < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)pntd, "%08x %08x %08x: ", this, m_GrpDownLoadThreadList, cur_node);
      pntd += strlen(pntd);
   }
#endif

   while((cur_node != NULL) && SUCCEEDED(retc))
   {
DWORD *cur_thread_ptr = (DWORD *)cur_node->GetValue();
      KP_ASSERT(cur_thread_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT(strlen(lpszOutStrBuf) + /* MAX_LONG_HEX_DIGITS + 2 + */ MAX_LONG_DIGITS + 2 < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
//       sprintf((char *)pntd, "%08x: %ld  ", cur_node, *cur_thread_ptr);
         sprintf((char *)pntd, "%ld  ", *cur_thread_ptr);
         pntd += strlen(pntd);
      }

      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother(&cur_node);
   }

   if(bSetSemaphore) m_bGrpDownloadListProcessing = False;

return(retc);
}
#endif


// -----------------------------------------
DWORD WINAPI StartGrpDownloadThreadProc(LPVOID lpParameter)
{
HRESULT retc = S_OK;
KpGrpChk *par_ptr = (KpGrpChk *)lpParameter;

   KP_ASSERT(par_ptr != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(theKpStAppPtr != NULL, KP_E_NO_FILE, null, True);

DWORD cur_thread = GetCurrentThreadId();

// PutLogMessage_("StartGrpDownloadThreadProc() thread: %d pradžia", cur_thread);

// ------------
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->AppendGrpDownloadThreadListEntry(cur_thread);

// if(SUCCEEDED(retc)) retc = theKpStAppPtr->StartHp11(theKpStAppPtr->m_hInstance);

// ------------
long full_size = 0L;
   if(SUCCEEDED(retc)) full_size = par_ptr->m_lDownLoadFSize;

long received = 0L;

#if FALSE
HWND prog_wnd = NULL;
if(SUCCEEDED(retc)) retc = KpCreateProgressWnd(&prog_wnd, KP_MSG_DOWNLOADING, Maxint, full_size);
KP_ASSERT(prog_wnd, KP_E_SYSTEM_ERROR, null, True);
if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, 0L, full_size);
#endif

#if FALSE
unsigned char *pnts = null;
KP_NEWA(pnts, unsigned char, 1000);
PutLogMessage_("StartGrpDownloadThreadProc() pries %x", pnts);
KP_DELETEA(pnts);
#endif

   try
   {
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GrpDownloadSingle(par_ptr, NULL /* prog_wnd */, &received, full_size);
   }
   catch(...) KP_ERROR(KP_E_SYSTEM_ERROR, null);

#if FALSE
KP_NEWA(pnts, unsigned char, 1000);
PutLogMessage_("StartGrpDownloadThreadProc() po %x", pnts);
KP_DELETEA(pnts);
#endif

#if FALSE
if(SUCCEEDED(retc)) KpSleep(300);
if(SUCCEEDED(retc)) retc = KillProgressWnd(prog_wnd);
#endif

   KP_DELETE(par_ptr);

// ------------
   if((retc == KP_E_CANCEL) || SUCCEEDED(retc)) retc = theKpStAppPtr->DeleteGrpDownloadThreadListEntry(cur_thread);

#if FALSE
unsigned char str_buf[KP_MAX_FILE_LIN_LEN + 1];
str_buf[0] = Nul;
if((retc == KP_E_CANCEL) || SUCCEEDED(retc)) retc = theKpStAppPtr->DumpGrpDownloadThreadList(str_buf, True);
PutLogMessage_("StartGrpDownloadThreadProc() thread: %d fin %x [%s]", cur_thread, retc, str_buf);
#endif

return(RET_CODE_WIN(retc));
}


// -----------------------------------
HRESULT KpStApp::StartGrpDownloadThread(const unsigned char *lpszAppNameUTF8)
{
HRESULT retc = S_OK;
KpGrpChk *download_pars = NULL;
   KP_NEW(download_pars, KpGrpChk);

// -------------------------- nustatom meniu atnaujinimo blokavimo semaforą
// semaforas blokuojasi
// if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
//    m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();
bool refresh_sav = m_bGrpRefreshFlg;
   m_bGrpRefreshFlg = False;

// ----------------------------------------------------------
   KP_ASSERT(download_pars != NULL, KP_E_OUTOFMEM, null, True);
   KP_ASSERT(lpszAppNameUTF8 != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszAppNameUTF8) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, lpszAppNameUTF8, True);

// ----------------------------------------------------------
   if(SUCCEEDED(retc))
   {
      download_pars->m_bSetupFl = True;
      download_pars->m_bRegFl = True;
      download_pars->m_bChecked = True;
   }

// -------------------- {appname}
unsigned char app_name[KP_MAX_FILE_LIN_WDT + 1];
   if(SUCCEEDED(retc)) retc = DecodeAppNameUTF8toStr(app_name, lpszAppNameUTF8, True); // False);
// PutLogMessage_("KpStApp::StartGrpDownloadThread() %s", lpszAppNameUTF8);
// PutLogMessage_("KpStApp::StartGrpDownloadThread() <appname>: [%s]", app_name);

// -----------------
XmlNode *item_node = NULL;
   if(SUCCEEDED(retc)) retc = GetGrpCfgItem(&item_node, app_name, m_pGrpCfgNode, True); // False);
   KP_ASSERT(item_node != NULL, KP_E_FILE_FORMAT, download_pars->m_lpszText, True);

unsigned char *val_str = null;
KpChar *val_str_i = NULL;
   if(SUCCEEDED(retc)) retc = GetGrpItemAppName(&val_str, &val_str_i, item_node, True);
   KP_ASSERT(val_str != NULL, KP_E_FILE_FORMAT, null, True);

// išsaugojam į grp_item
   KP_ASSERT(strlen(val_str) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, val_str, True);
   if(SUCCEEDED(retc)) strcpy(download_pars->m_lpszText, val_str);
   KP_ASSERT(TvKpStrLen(val_str_i) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, val_str, True);
   if(SUCCEEDED(retc)) TvKpStrCpy(download_pars->m_iazText, val_str_i);

// trinam val_str
   KP_DELETEA(val_str);
   KP_DELETEA(val_str_i);

// -------------------- <setup>
XmlNode *setup_node = NULL;
   if(SUCCEEDED(retc)) retc = item_node->SearchChildSubNode(XG_Setup, &setup_node);
   KP_ASSERT(item_node != NULL, KP_E_FILE_FORMAT, null, True);

KpChar *node_val = NULL;
   if(SUCCEEDED(retc)) retc = setup_node->ExtractContents(&node_val);
   KP_ASSERT(node_val != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(download_pars->m_lpszDownLoadFName, node_val, TV_MAIN_CTBL);
PutLogMessage_("KpStApp::StartGrpDownloadThread() <setup>: %s", download_pars->m_lpszDownLoadFName);

unsigned char local_fname[KP_MAX_FNAME_LEN + 1];
   local_fname[0] = Nul;
   if(SUCCEEDED(retc)) retc = GetGrpLocalFName(local_fname, null, download_pars->m_lpszDownLoadFName);

// ----------------------------------------------------- apsauga nuo dubliavimosi
// laukiam, kol atsilaisvins m_GrpDownloadFNameList
   while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc = KpSleep(100);
   m_bGrpDownloadListProcessing = True;

bool found = False;
   if((m_GrpDownloadFNameList != NULL) && SUCCEEDED(retc))
   {
KpTreeEntry *setup_entry = NULL;
KpTreeEntry *name_list = (KpTreeEntry *)m_GrpDownloadFNameList;
      KP_ASSERT(name_list != NULL, E_POINTER, null, True);
      if(SUCCEEDED(retc)) retc = name_list->SearchTreeEntry(local_fname, TvStrCmpStrict_, &setup_entry, NULL);
      if((setup_entry != NULL) && SUCCEEDED(retc)) found = True;
   }
   if(found) m_bGrpDownloadListProcessing = False;

   if((!found) && SUCCEEDED(retc))
   {

// -----------
KpTreeEntry *setup_entry = NULL;
      KP_NEWO(setup_entry, KpTreeEntry(local_fname, NULL));

      if(m_GrpDownloadFNameList != NULL)
      {
KpTreeEntry *name_list = (KpTreeEntry *)m_GrpDownloadFNameList;
         KP_ASSERT(name_list != NULL, E_POINTER, null, True);
         if(SUCCEEDED(retc)) retc = name_list->AppendBrother(setup_entry);
      }
      else m_GrpDownloadFNameList = setup_entry;

      m_bGrpDownloadListProcessing = False;

// -------------------- {setupsize}
XmlTagPars *tag_pars = NULL;
      if(SUCCEEDED(retc)) retc = setup_node->GetTagParsPtr(&tag_pars);
      KP_ASSERT(tag_pars != NULL, KP_E_FILE_FORMAT, null, True);

long num_val = 0L;
int par_num = 0;
      if(SUCCEEDED(retc))
      {
         retc = tag_pars->SeekNumPar("size", &num_val, &par_num);
         if(FAILED(retc)) KP_ERROR(retc, null);
      }
      if(SUCCEEDED(retc)) download_pars->m_lDownLoadFSize = num_val;
PutLogMessage_("KpStApp::StartGrpDownloadThread() {setupsize}: %ld", download_pars->m_lDownLoadFSize);

// -------------------- ieškom <lic> reikšmės
      val_str = null;
      if(SUCCEEDED(retc)) retc = item_node->ExtractSubnodeContentsStr(XG_Licence, &val_str);
      KP_ASSERT(val_str != null, KP_E_FILE_FORMAT, null, True);

      KP_ASSERT(strlen(val_str) <= KPST_NUM_OF_LIC_CHARS, KP_E_BUFFER_OVERFLOW, val_str, True);
      if(SUCCEEDED(retc)) strcpy(download_pars->m_lpszLicCode, val_str);
PutLogMessage_("KpStApp::StartGrpDownloadThread() <lic>: %s", download_pars->m_lpszLicCode);

// trinam val_str
      KP_DELETEA(val_str);

// ---------------------- stabdom KpHp11 threadą – bus paleistas iš naujo StartGrpDownloadThreadProc() threade
//    HRESULT retc0 = EmuTv.StopThread();
//    if(SUCCEEDED(retc)) retc = retc0;

// ---------------------- paleidžiam StartGrpDownloadThreadProc()
      if(SUCCEEDED(retc))
      {
HANDLE thread = NULL;
         thread = CreateThread
         (
            NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
            0L,                  // DWORD dwStackSize,                         // initial thread stack size
            StartGrpDownloadThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
            download_pars,                // LPVOID lpParameter,                        // argument for new thread
            0L,                  // DWORD dwCreationFlags,                     // creation flags
            NULL           // LPDWORD lpThreadId                         // pointer to receive thread ID
         );
         KP_ASSERT(thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

// ------------ nesėkmės atveju naikinam dubliavimo blokavimą
      if(FAILED(retc))
      {
HRESULT retc0 = S_OK;
         while(m_bGrpDownloadListProcessing && SUCCEEDED(retc)) retc0 = KpSleep(100);
         m_bGrpDownloadListProcessing = True;

         KP_ASSERT00(m_GrpDownloadFNameList != NULL, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT00(setup_entry != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc0))
         {
KpTreeEntry *next_entry = setup_entry->m_pNextBrother;
            retc0 = DeleteKpTreeEntry(setup_entry);
            if(setup_entry == m_GrpDownloadFNameList) m_GrpDownloadFNameList = next_entry;
         }

         m_bGrpDownloadListProcessing = False;
      }

   } // if((!found) && SUCCEEDED(retc))

// -------------------------- atlaisvinam meniu atnaujinimo blokavimo semaforą
// semaforas negerai – blokuojasi
// if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
//    m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();
   m_bGrpRefreshFlg = (m_bGrpRefreshGlobalFlg?refresh_sav:False);

return(retc);
}


// ------------------------------------
HRESULT KpStApp::KpGrSetProgressPrc(const unsigned char *lpszAppName, int iPrc)
{
HRESULT retc = S_OK;

   KP_ASSERTE(lpszAppName != null, E_POINTER, null, False);

// -------------------------- nustatom meniu atnaujinimo blokavimo semaforą
   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();

// ------------------------ susirandam produkto <item> mazgą
XmlNode *item_node = NULL;
   if(SUCCEEDED(retc)) retc = GetGrpCfgItem(&item_node, lpszAppName, m_pGrpCfgNode, True);
// KP_ASSERT(item_node != NULL, KP_E_FILE_FORMAT, null, True);
   if((item_node != NULL) && SUCCEEDED(retc))
   {

// -----------------------------
KpChar cur_tag = C_Nul;
      if(SUCCEEDED(retc)) retc = item_node->GetNodeTag(&cur_tag);
      KP_ASSERT(cur_tag == XG_Item, E_INVALIDARG, null, True);

// progreso tagas
XmlNode *prc_node = NULL;
      if(SUCCEEDED(retc)) retc = item_node->SearchChildSubNode(XG_Prc, &prc_node);

// naikinam seną <prc>
      if((prc_node != NULL) && SUCCEEDED(retc)) retc = DeleteKpTreeEntry(prc_node);

// kuriam naują <prc>
      if((iPrc >= 0) && SUCCEEDED(retc))
      {
unsigned char prc_val[MAX_LONG_DIGITS + 1];
         if(SUCCEEDED(retc)) sprintf((char *)prc_val, "%d", iPrc);

         if(SUCCEEDED(retc)) retc = item_node->AppendTextTag(XG_Prc, NULL, prc_val, TV_MAIN_CTBL);
      }

   } // if((item_node != NULL) && SUCCEEDED(retc))

// -------------------------- atlaisvinam meniu atnaujinimo blokavimo semaforą
   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

return(retc);
}


// -----------------------------------------
DWORD WINAPI StartUninstThreadProc(LPVOID lpParameter)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char *app_name_ptr = (unsigned char *)lpParameter;

   KP_ASSERT(app_name_ptr != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(app_name_ptr) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, app_name_ptr, True);

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_NO_FILE, null, True);

// -----------------------
DWORD cur_thread = GetCurrentThreadId();
// PutLogMessage_("StartUninstThreadProc() thread: %d pradžia", cur_thread);
   if(theKpStAppPtr != NULL) retc0 = theKpStAppPtr->AppendGrpDownloadThreadListEntry(cur_thread);
   if(SUCCEEDED(retc)) retc = retc0;

// ------------ off-line neišmetinėjam
   if(SUCCEEDED(retc)) if(theKpStAppPtr->m_bForceGrpCfg)
   {
      PutMsgFirewall(KP_MSG_FIREWALL);
      retc = KP_E_NO_CONN;
   }

// ------------
unsigned char uninst_cmd[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc))
   {
//    retc = KpStApp::GetInnoUnInstCmd(uninst_cmd, app_name_ptr);
      retc = theKpStAppPtr->GetGrpUnInstCmd(uninst_cmd, app_name_ptr);
PutLogMessage_("StartUninstThreadProc() StartProcess(\"%s\");", uninst_cmd);
      if(retc != KP_E_FILE_NOT_FOUND) KP_ASSERT_(SUCCEEDED(retc), retc);

// PutLogMessage_("StartUninstThreadProc(): %s", uninst_cmd);

      if(SUCCEEDED(retc)) retc = StartProcess(uninst_cmd, KP_CUR_DIR, NULL, NULL, SW_SHOWNORMAL);

// ------------ diegimo failo neradom – ištrinam bent XFS.exe – kad po to galima būtų įdiegti iš naujo
      if(retc == KP_E_FILE_NOT_FOUND)
      {
bool installed = False;
         retc = theKpStAppPtr->GetGrpLaunch(uninst_cmd, NULL, &installed, app_name_ptr);
         if((!installed) && SUCCEEDED(retc)) retc = KP_E_FILE_NOT_FOUND;
         if(FAILED(retc)) KP_WARNING0(retc, null);

// numetam "tux:///KpStart:Start:"
unsigned char *pnts = uninst_cmd;
unsigned char *pnts1 = null;
         if(SUCCEEDED(retc))
         {
            pnts1 = strstr(uninst_cmd, KPST_GRP_PATH_PREFIX);
            if(pnts1 != null)
            {
               KP_ASSERT(pnts1 == uninst_cmd, KP_E_FILE_FORMAT, uninst_cmd, False);
               pnts = pnts1 + strlen(KPST_GRP_PATH_PREFIX);

               pnts1 = strchr(pnts, ':'); // "Start:", "StartAndClose:" etc.
               KP_ASSERT(pnts1 != null, KP_E_FILE_FORMAT, uninst_cmd, False);
               if(pnts1 != null) pnts = pnts1 + 1;
            }
PutLogMessage_("StartUninstThreadProc() DeleteFile(\"%s\");", pnts);

            if(!DeleteFile((const char *)pnts))
            {
               KP_WARNING0(KP_E_FILE_NOT_FOUND, uninst_cmd);
               KP_WARNING0(KP_E_FILE_NOT_FOUND, GetLastError());
            }
         }
      }
   }

// ------------
   KP_DELETEA(app_name_ptr);

   if(theKpStAppPtr != NULL) retc0 = theKpStAppPtr->DeleteGrpDownloadThreadListEntry(cur_thread);
   if((retc == KP_E_CANCEL) || SUCCEEDED(retc)) retc = retc0;

#if FALSE
unsigned char str_buf[KP_MAX_FILE_LIN_LEN + 1];
str_buf[0] = Nul;
if((retc == KP_E_CANCEL) || SUCCEEDED(retc)) retc = theKpStAppPtr->DumpGrpDownloadThreadList(str_buf, True);
PutLogMessage_("StartUninstThreadProc() thread: %d fin %x [%s]", cur_thread, retc, str_buf);
#endif

return(RET_CODE_WIN(retc));
}


// -----------------------------------
HRESULT KpStApp::StartUninstThread(const unsigned char *lpszAppNameUTF8)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszAppNameUTF8 != null, E_INVALIDARG, null, True);

// -------------------- {appname}
unsigned char *app_name = null;
   KP_NEWA(app_name, unsigned char, KP_MAX_FILE_LIN_WDT + 1);
   if(SUCCEEDED(retc)) retc = DecodeAppNameUTF8toStr(app_name, lpszAppNameUTF8, True); // False);

// ---------------------- paleidžiam StartGrpDownloadThreadProc()
   if(SUCCEEDED(retc))
   {
HANDLE thread = NULL;
      thread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         StartUninstThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         app_name,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         NULL           // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      KP_ASSERT(thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

return(retc);
}


// ------------------------------------ meniu dėl StartGrp.exe
HRESULT KpStApp::ExtractStartMenuSubsts(KpTreeEntry **pElemList, const XmlNode *pCfgSubNode,
   KpChar iTag, /* const */ KpTreeEntry *pFilesList, int *piFilesIx)
{
HRESULT retc = S_OK;

   KP_ASSERT(pElemList != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(pCfgSubNode != NULL, E_INVALIDARG, null, True);

XmlNode *cur_node = NULL;
// if(SUCCEEDED(retc)) retc = pCfgSubNode->GetFirstChild((KpTreeEntry **)&cur_node); // pirmas vaikas
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)pCfgSubNode->m_pFirstChild;

// ciklinsim tik per pirmos kartos vaikus
   while((cur_node != NULL) && SUCCEEDED(retc))
   {
KpChar cur_tag = C_Nul;
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);

      if((cur_tag == iTag) && SUCCEEDED(retc))
      {
// ištraukiam tago reikšmę
KpChar *tag_val = NULL;
         if(SUCCEEDED(retc)) retc = cur_node->ExtractContents(&tag_val);
         KP_ASSERT(tag_val != NULL, KP_E_FILE_FORMAT, null, True);

// pakonvertuojam
KpChar *subst_val = NULL;
int subst_val_len = 0;
int num_of_files = 0; // *pFilesList įrašų skaičius
int full_files_length = 0; // *pFilesList įrašų reikšmių suminis ilgis

// skaičiuojam konvertavimo buferio ilgį
         if(SUCCEEDED(retc)) switch(iTag)
         {
         case XG_File: subst_val_len = KP_MAX_FNAME_LEN + 100; break;
         case XG_MPar:
            if(pFilesList != NULL)
            {
               if(SUCCEEDED(retc)) retc = pFilesList->CountEntries(&num_of_files);
               if(SUCCEEDED(retc)) retc = CountKpCharListFullLength(&full_files_length, pFilesList);
            }
            subst_val_len = TvKpStrLen(tag_val) + full_files_length;
            break;
         default: subst_val_len = TvKpStrLen(tag_val); break;
         }
// kuriam konvertavimo buferį
         KP_NEWA(subst_val, KpChar, subst_val_len + 1);

// konvertuojam/substinam
         if(SUCCEEDED(retc)) switch(iTag)
         {
         case XG_File:
// keičiam remote failo vardą į local
// TODO: failų vardus perdaryt į Unicode
unsigned char remote_fname[KP_MAX_FNAME_LEN + 1];
unsigned char local_fname[KP_MAX_FNAME_LEN + 1];
            KP_ASSERT(TvKpStrLen(tag_val) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, tag_val, True);
            if(SUCCEEDED(retc))
            {
               retc = KptStrDecode(remote_fname, tag_val, TV_MAIN_CTBL);
               if(FAILED(retc))
               {
                  KP_WARNING(retc, remote_fname);
                  retc = S_OK;
               }
               remote_fname[KP_MAX_FNAME_LEN] = Nul;
            }
            if(SUCCEEDED(retc)) retc = GetGrpLocalFName(local_fname, null, remote_fname);
            if(SUCCEEDED(retc))
            {
               TvKpStrCpy(subst_val, TV_XL_TUX_PATH_PREFIX_W); // TV_XM_URL_FILE_PREFIX_W);
               retc = KptStrEncode(subst_val + TvKpStrLen(TV_XL_TUX_PATH_PREFIX_W), // TV_XM_URL_FILE_PREFIX_W),
                                          local_fname, TV_MAIN_CTBL);
               if(FAILED(retc))
               {
                  KP_WARNING(retc, local_fname);
                  retc = S_OK;
               }
               subst_val[KP_MAX_FNAME_LEN] = C_Nul;
            }
         break;

         case XG_MPar:
// {files} substinam į *pFilesList
            if(SUCCEEDED(retc))
            {
KpStGrpSubster subster(subst_val, subst_val_len, tag_val, pFilesList, piFilesIx);
               retc = subster.SubstGrpTpl();
            }
            break;

         default:
            KP_ASSERT(TvKpStrCpy(subst_val, tag_val) != NULL, KP_E_SYSTEM_ERROR, tag_val, True);
            break;
         }

// pridedam prie *pElemList
         if(SUCCEEDED(retc))
         {
            if(*pElemList == NULL) KP_NEWO(*pElemList, KpTreeEntry(subst_val, NULL))
            else retc = (*pElemList)->PutToEnd(subst_val);
         }

         KP_DELETEA(subst_val);
      }

// kitas tagas
      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node);

   } // while((cur_node != NULL) && SUCCEEDED(retc))

return(retc);
}


// -------------------------------------
KpStGrpSubster::KpStGrpSubster(KpChar *iazOutBuf, int iOutBufLen, const KpChar *iazTemplate,
      /* const */ KpTreeEntry *pFilesList, int *piFilesIx,
      /* const */ KpTreeEntry *pMParsList, int *piMParsIx,
      const KpChar *iazAppName, const KpChar *iazInstPath, const KpChar *iazLaunch,
      const KpChar *iazSetup, const KpChar *iazSetupSize, const KpChar *iazLic,
      const KpChar *iazPrc)
{
HRESULT retc = S_OK;

   m_hOpenError = S_OK;

   m_iazOutBuf = iazOutBuf;
   m_iOutBufLen = iOutBufLen;
   m_iazTemplate = iazTemplate;

   m_pFilesList = pFilesList;
   m_piFilesIx = piFilesIx;
   m_iFilesCnt = 0;
   if((m_pFilesList != NULL) && SUCCEEDED(m_hOpenError)) m_hOpenError = m_pFilesList->CountEntries(&m_iFilesCnt);

   m_pMParsList = pMParsList;
   m_piMParsIx = piMParsIx;
   m_iMParsCnt = 0;
   if((m_pMParsList != NULL) && SUCCEEDED(m_hOpenError)) m_hOpenError = m_pMParsList->CountEntries(&m_iMParsCnt);

   m_iazAppName = iazAppName;
   m_iazInstPath = iazInstPath;
   m_iazLaunch = iazLaunch;

   m_iazSetup = iazSetup;
   m_iazSetupSize = iazSetupSize;
   m_iazLic = iazLic;

   m_iazPrc = iazPrc;

   m_iazTemp = NULL;
unsigned char temp_path[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetLocalPath(temp_path, KP_Temp_Dir, False);
   KP_NEWA(m_iazTemp, KpChar, strlen(temp_path) + 1);
   if(SUCCEEDED(retc)) KptStrEncode(m_iazTemp, temp_path, TV_MAIN_CTBL);

   m_iazPnts = m_iazTemplate;
   m_iazPntd = m_iazOutBuf;

   if(SUCCEEDED(m_hOpenError)) m_hOpenError = retc;
}


KpStGrpSubster::~KpStGrpSubster()
{
HRESULT retc = S_OK;
   KP_DELETEA(m_iazTemp);
}


HRESULT KpStGrpSubster::SubstFromList(const KpChar *iazMacroName, /* const */ KpTreeEntry *pSubstList, int *piSubstListIx, int iSubstListSize)
{
HRESULT retc = m_hOpenError;

   KP_ASSERT(m_iazPnts != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_iazPntd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(iazMacroName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(pSubstList != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(piSubstListIx != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(iSubstListSize != 0, E_INVALIDARG, null, True);
   KP_ASSERT(*piSubstListIx < iSubstListSize, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
KpTreeEntry *entry_ptr = NULL;
      if(SUCCEEDED(retc))
      {
int entry_num = *piSubstListIx;
         retc = pSubstList->GetEntryPtr(&entry_num, &entry_ptr, 0, NULL);
      }
      KP_ASSERT(entry_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
KpChar *entry_val = NULL;
      if(SUCCEEDED(retc)) entry_val = (KpChar *)entry_ptr->GetValue();
      KP_ASSERT(entry_val != NULL, KP_E_SYSTEM_ERROR, null, True);
int entry_len = 0;
      if(SUCCEEDED(retc)) entry_len = TvKpStrLen(entry_val);
      KP_ASSERT((m_iazPntd - m_iazOutBuf) + entry_len < m_iOutBufLen, KP_E_BUFFER_OVERFLOW, entry_val, True);
      if(SUCCEEDED(retc))
      {
         TvKpStrCpy(m_iazPntd, entry_val);
         m_iazPntd += entry_len;
         m_iazPnts += TvKpStrLen(iazMacroName);
         (*piSubstListIx)++;
         if(*piSubstListIx >= iSubstListSize) *piSubstListIx = 0;
      }
   }

return(retc);
}


HRESULT KpStGrpSubster::SubstSingle(const KpChar *iazMacroName, const KpChar *iazSubstText)
{
HRESULT retc = m_hOpenError;

   KP_ASSERT(m_iazPnts != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_iazPntd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(iazMacroName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(iazSubstText != NULL, E_INVALIDARG, null, True);

// if((iazSubstText != NULL) && SUCCEEDED(retc)) // čia jau vėlu, reikia prieš iškviečiant, nes tada reikia vieną simbolį permest į *m_iazPntd++
   {
int subst_len = 0;
      if(SUCCEEDED(retc)) subst_len = TvKpStrLen(iazSubstText);
      KP_ASSERT((m_iazPntd - m_iazOutBuf) + subst_len < m_iOutBufLen, KP_E_BUFFER_OVERFLOW, iazSubstText, True);
      if(SUCCEEDED(retc))
      {
         TvKpStrCpy(m_iazPntd, iazSubstText);
         m_iazPntd += subst_len;
         m_iazPnts += TvKpStrLen(iazMacroName);
      }
   }

return(retc);
}


HRESULT KpStGrpSubster::SubstGrpTpl(void)
{
HRESULT retc = m_hOpenError;

   KP_ASSERT(m_iazOutBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(m_iazTemplate != NULL, E_INVALIDARG, null, True);

   m_iazPnts = m_iazTemplate;
   m_iazPntd = m_iazOutBuf;

   if(SUCCEEDED(retc)) while((*m_iazPnts != C_Nul) && SUCCEEDED(retc))
   {
// PutLogMessage_("SubstGrpTpl() 1: %x %c%c%c%c%c", retc, m_iazPnts[0], m_iazPnts[1], m_iazPnts[2], m_iazPnts[3], m_iazPnts[4]);
// ieškom makrokomandų
      if((m_pFilesList != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_FILE_W) == m_iazPnts)) retc = SubstFromList(KPST_GRP_MACRO_FILE_W, m_pFilesList, m_piFilesIx, m_iFilesCnt); // L"{file}"
      else if((m_pMParsList != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_MPAR_W) == m_iazPnts)) retc = SubstFromList(KPST_GRP_MACRO_MPAR_W, m_pMParsList, m_piMParsIx, m_iMParsCnt); // L"{mpar}"

      else if((m_iazAppName != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_APPNAME_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_APPNAME_W, m_iazAppName); // L"{appname}"
      else if((m_iazInstPath != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_APP_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_APP_W, m_iazInstPath); // L"{app}"
      else if((m_iazLaunch != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_LAUNCH_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_LAUNCH_W, m_iazLaunch); // L"{launch}"

      else if((m_iazSetup != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_SETUP_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_SETUP_W, m_iazSetup); // L"{setup}"
      else if((m_iazSetupSize != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_SETUPSIZE_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_SETUPSIZE_W, m_iazSetupSize); // L"{setupsize}"
      else if((m_iazLic != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_LIC_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_LIC_W, m_iazLic); // L"{lic}"

      else if((m_iazPrc != NULL) && (TvKpStrStr(m_iazPnts, KPST_GRP_MACRO_PRC_W) == m_iazPnts)) retc = SubstSingle(KPST_GRP_MACRO_PRC_W, m_iazPrc); // L"{prc}"

      else if((m_iazTemp != NULL) && (TvKpStrStr(m_iazPnts, KPST_FNAME_SHORTCUT_TEMP_W) == m_iazPnts)) retc = SubstSingle(KPST_FNAME_SHORTCUT_TEMP_W, m_iazTemp); // L"{temp}"

      else
      {
         KP_ASSERT(m_iazPntd - m_iazOutBuf < m_iOutBufLen, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc)) *m_iazPntd++ = *m_iazPnts++;
      }

   } // while((*m_iazPnts != C_Nul) && SUCCEEDED(retc))

   if(SUCCEEDED(retc)) *m_iazPntd = C_Nul;

return(retc);
}


HRESULT KpStApp::SaveGrpMenu(void)
{
HRESULT retc = S_OK;

unsigned char *grp_menu_buf = null;
long grp_menu_len = strlen(m_lpszGrpMenu);

   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();

#ifdef IBSHT_ENCODED
// ---------------- kuriam kodavimo buferį
   KP_NEWA(grp_menu_buf, unsigned char, grp_menu_len + 4 + 1);
   if(SUCCEEDED(retc)) strcpy(grp_menu_buf, m_lpszGrpMenu);

// ---------------- užkoduojam buferį
long entry_id = 0L; // TODO: čia įkomponuot kažkaip failo pavadinimą ar ilgį (lzdsht čia naudojamas lEntryId)

   KP_ASSERT(grp_menu_buf != null, KP_E_SYSTEM_ERROR, null, True);

#  if FALSE // KpHp11 iškvietimai kažko laužia multithreadinį Gecko streamų kūrimą
static KpRcPars rc_pars;
   KP_ASSERT(grp_menu_len < (Maxint + 1) * 4, KP_E_BUFFER_OVERFLOW, null, False); // perkoduoja tik tiek, galas lieka neperkoduotas

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_ENCODE_ENTRY;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iDataLen = ((grp_menu_len + 4) / 4) * 4;
      rc_pars.enc.pData = grp_menu_buf;
      rc_pars.enc.lCtrl = entry_id;

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }
#  else
int prod_ver = 0;
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

// if(SUCCEEDED(retc)) retc = EnctBufMed(grp_menu_buf, grp_menu_len, prod_ver, entry_id);
   if(SUCCEEDED(retc)) retc = EnctBufInc(grp_menu_buf, grp_menu_len, prod_ver, entry_id, True);
#  endif

#else
   grp_menu_buf = m_lpszGrpMenu;
#endif

// -------------------- rašom į failą
// FILE *tmp_file = fopen((const char *)KPST_GRP_MENU_FNAME, "wb");
// fputs((const char *)m_lpszGrpMenu, tmp_file);
// fclose(tmp_file);

// ---------------- rašom užkoduotą buferį į failą
HANDLE local_file = INVALID_HANDLE_VALUE;
   if(SUCCEEDED(retc))
   {
      local_file = CreateFile((const char *)KPST_GRP_MENU_FNAME, GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
      KP_ASSERT(local_file != INVALID_HANDLE_VALUE, KP_E_DIR_ERROR, m_lpszGrpCfgFName, True);
   }

DWORD written = 0;
   KP_ASSERT(WriteFile(local_file, grp_menu_buf, grp_menu_len, &written, NULL), KP_E_FERROR, KPST_GRP_MENU_FNAME, True);
   KP_ASSERT(written == grp_menu_len, KP_E_FERROR, KPST_GRP_MENU_FNAME, False);

   if(local_file != INVALID_HANDLE_VALUE)
      KP_ASSERT(CloseHandle(local_file), KP_E_FERROR, m_lpszGrpCfgFName, True);
   local_file = INVALID_HANDLE_VALUE;

// ---------------- naikinam buferį
#ifdef IBSHT_ENCODED
   if(SUCCEEDED(retc)) KP_DELETEA(grp_menu_buf); // jeigu iš ExecRemoteCall() grįžo su klaida, buferio netrinam – kphp11 gal dar jo reikia
#endif

   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

return(retc);
}


HRESULT KpStApp::LoadGrpImg(XmlNode *pFather, int iTag, KpBmpData *pBmpPars, HBITMAP *pBitmap, XmlNode **pChild)
{
HRESULT retc = S_OK;

   KP_ASSERT(pFather != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(pBmpPars != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(pBitmap != NULL, E_INVALIDARG, null, True);

XmlNode *img_child = NULL;
   if(SUCCEEDED(retc)) retc = pFather->SearchChildSubNode(iTag, &img_child);
   if((img_child != NULL) && SUCCEEDED(retc))
   {
KpChar *imgfname = NULL;
//    if(SUCCEEDED(retc)) retc = img_child->ExtractSubnodeContents(iTag, &imgfname);
      if(SUCCEEDED(retc)) retc = img_child->ExtractContents(&imgfname);
      if(imgfname != NULL)
      {
         KP_ASSERT(TvKpStrLen(imgfname) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
unsigned char remote_fname[KP_MAX_FNAME_LEN + 1];
// TODO: čia šiaip jau UTF-8, ne ISO-8859-13
         if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(remote_fname, imgfname, TV_MAIN_CTBL);
unsigned char local_fname[KP_MAX_FNAME_LEN + 1];
unsigned char str_msg[KP_MAX_FNAME_LEN + 1];
         if(SUCCEEDED(retc)) retc = GetGrpLocalFName(local_fname, str_msg, remote_fname);

         if(SUCCEEDED(retc))
         {
// negerai – controlas dar atviras – sunaikinam jo bitmapą
//          if(*pBitmap != NULL) DeleteObject(*pBitmap);
//          *pBitmap = NULL;

            *pBitmap = (HBITMAP)LoadImage(GetModuleHandle(0), (const char *)local_fname,
                                             IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
         }
      }
   }

// -------------------
   if(SUCCEEDED(retc))
   {
      if(*pBitmap != NULL)
      {
         if(SUCCEEDED(retc)) pBmpPars->m_hdcBmpHdc =
            GetWindowDC(m_pGrpKpPubDlg->m_hDialogWindow /* HWND_DESKTOP */);

static BITMAPINFO bmp_info;
         memset(&bmp_info, 0 , sizeof(bmp_info));
         bmp_info.bmiHeader.biSize = sizeof(bmp_info);

         if(GetDIBits(pBmpPars->m_hdcBmpHdc, *pBitmap, 0, 0, NULL, &bmp_info, DIB_RGB_COLORS))
         {
            pBmpPars->m_iBmpWdt = bmp_info.bmiHeader.biWidth;
            pBmpPars->m_iBmpHgt = bmp_info.bmiHeader.biHeight;

// PutLogMessage_("KpStApp::GenStartMenu() <background> %d %d", m_pGrpKpPubDlg->m_BgrBmpData.m_iBmpWdt, m_pGrpKpPubDlg->m_BgrBmpData.m_iBmpHgt);
         }
         else
         {
            DeleteObject(*pBitmap);
            *pBitmap = NULL;
         }
      }
   }

// -------------------
   if(pChild != NULL) *pChild = img_child;

return(retc);
}


HRESULT KpStApp::GenStartMenu(bool bLauncher)
{
HRESULT retc = S_OK;
int prod_ver = 0;

// -----------------------
   KP_ASSERT(m_pGrpCfgNode != NULL, KP_E_NO_FILE, null, True);

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

// ------------------------ surandam tagą <pr> – viskas vyks nuo jo
XmlNode *pr_node = m_pGrpCfgNode;
   while((pr_node != NULL) && SUCCEEDED(retc))
   {
KpChar cur_tag = C_Nul;
      if(SUCCEEDED(retc)) retc = pr_node->GetNodeTag(&cur_tag);
      if(cur_tag == XG_GrPars) break;

      if(SUCCEEDED(retc)) retc = pr_node->GetNextBrother((KpTreeEntry **)&pr_node);
   }
   KP_ASSERT(pr_node != NULL, KP_E_FILE_FORMAT, null, True);

// ------------------------ ieškom <background>
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   KP_ASSERT(m_pGrpKpPubDlg != NULL, KP_E_SYSTEM_ERROR, null, True);
XmlNode *bgr_child = NULL;
   if(SUCCEEDED(retc)) retc = LoadGrpImg(pr_node, XG_BackGround, &m_pGrpKpPubDlg->m_BgrBmpData, &m_pGrpKpPubDlg->m_BgrBmpData.m_hBitMap, &bgr_child);

   if((bgr_child != NULL) && SUCCEEDED(retc))
   {
//    KP_ASSERT(m_pGrpKpPubDlg->m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

// -------------------
      if(SUCCEEDED(retc)) // parametras caption="20"
      {
HRESULT retc0 = S_OK;
XmlTagPars *tag_pars = NULL;
         if(SUCCEEDED(retc0)) retc0 = bgr_child->GetTagParsPtr(&tag_pars);
         if((tag_pars != NULL) && SUCCEEDED(retc0))
         {
int par_num = 0;
long capt_hgt = IBSH_WND_SOFT_CAPTION_HGT;
            retc0 = tag_pars->SeekNumPar("caption", &capt_hgt, &par_num);
            if(SUCCEEDED(retc0)) m_pGrpKpPubDlg->m_BgrBmpData.m_iCaptHgt = capt_hgt;
         }
      }
   }
#endif

// --------------------------------------- užkraunam <button>-us
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
XmlNode *but_child = NULL;
   if(SUCCEEDED(retc)) retc = pr_node->SearchChildSubNode(XG_Button, &but_child);
   while((but_child != NULL) && SUCCEEDED(retc))
   {
      KP_ASSERT(m_pGrpKpPubDlg != NULL, KP_E_SYSTEM_ERROR, null, True);

// ------------------- parametras id=""
XmlTagPars *tag_pars = NULL;
unsigned char but_id[MAX_XML_PAR_VAL_LEN + 1];
      if(SUCCEEDED(retc)) retc = but_child->GetTagParsPtr(&tag_pars);
      KP_ASSERT(tag_pars != NULL, KP_E_FILE_FORMAT, null, True);
      if(SUCCEEDED(retc))
      {
int par_num = 0;
         but_id[0] = Nul;
         retc = tag_pars->SeekTextPar("id", but_id, &par_num);
         if(FAILED(retc)) KP_ERROR(KP_E_FILE_FORMAT, null);
      }
KpBmpData *bmp_pars = NULL;
      if(SUCCEEDED(retc))
      {
         if(strcmp(but_id, "exit") == 0)
         {
            bmp_pars = &m_pGrpKpPubDlg->m_ButExitBmpData;
            if(m_pGrpKpPubDlg->m_ButExit != NULL) ::DestroyWindow(m_pGrpKpPubDlg->m_ButExit);
            m_pGrpKpPubDlg->m_ButExit = NULL;
         }
         else if(strcmp(but_id, "minimize") == 0)
         {
            bmp_pars = &m_pGrpKpPubDlg->m_ButMinBmpData;
            if(m_pGrpKpPubDlg->m_ButMinimize != NULL) ::DestroyWindow(m_pGrpKpPubDlg->m_ButMinimize);
            m_pGrpKpPubDlg->m_ButMinimize = NULL;
         }
         else KP_ERROR(KP_E_FILE_FORMAT, null);
      }

// ------------------ <butimg>, <butpressed>, <buthover>
      if(SUCCEEDED(retc)) retc = LoadGrpImg(but_child, XG_ButPressed, bmp_pars, &bmp_pars->m_hPressed);
      if(SUCCEEDED(retc)) retc = LoadGrpImg(but_child, XG_ButHover, bmp_pars, &bmp_pars->m_hHover);
      if(SUCCEEDED(retc)) retc = LoadGrpImg(but_child, XG_ButImg, bmp_pars, &bmp_pars->m_hBitMap);

// ----------------
      if(SUCCEEDED(retc))
      {
XmlNode *next_node = (XmlNode *)but_child->m_pNextBrother; // peršokam prie sekančio
         but_child = NULL;
         if(next_node != NULL) retc = next_node->SearchSubNode(XG_Button, &but_child); // ieškom tolesnio <button>
      }

   } // while((but_child != NULL) && SUCCEEDED(retc))
#endif

// ------------------------  viršutinio lygmens failų sąrašas, naudojamas kepurei ir uodegai
KpTreeEntry *top_files = NULL; // KpChar[] stringų sąrašas
   if(SUCCEEDED(retc)) retc = ExtractStartMenuSubsts(&top_files, pr_node, XG_File); // XG_File – reikšmes keičiam į lokalius failų vardus

int top_files_ix = 0; // indexas vaikščiojimui per viršutinio lygmens failų sąrašą

// pilnas visų viršutinio lygmens failų vardų ilgis
int top_files_cont_len = 0;
   if((top_files != NULL) && SUCCEEDED(retc)) retc = CountKpCharListFullLength(&top_files_cont_len, top_files);

// ------------------------ kepurės šablonas
KpChar *head_tpl = NULL;
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MHead, &head_tpl);
   KP_ASSERT(head_tpl != NULL, KP_E_FILE_FORMAT, null, True);

// ------------------------ formuojam kepurę
int head_buf_len = 0;
   if(SUCCEEDED(retc)) head_buf_len = TvKpStrLen(head_tpl) + top_files_cont_len + 100;
KpChar *head_buf = NULL;
   KP_NEWA(head_buf, KpChar, head_buf_len + 1);
   if(SUCCEEDED(retc)) head_buf[0] = C_Nul;

KpStGrpSubster subster(head_buf, head_buf_len, head_tpl, top_files, &top_files_ix);
   if(SUCCEEDED(retc)) retc = subster.SubstGrpTpl();

// ----------------------- meniu punktai
KpTreeEntry *items = NULL; // čia kaupiam suformuotus HTML meniu punktus – KpChar eilutes

// ------------------------ meniu punkto šablonas
KpChar *item_tpl = NULL; // galutinis šablono elementas, į kurį pasirinksim vieną iš konkrečių <m*>, nustatę, koks <item> įrašo tipas
KpChar *mitem_tpl = NULL;
KpChar *mwait_tpl = NULL;
KpChar *mfree_tpl = NULL;
KpChar *mpend_tpl = NULL;
KpChar *munavail_tpl = NULL;

   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MItem, &mitem_tpl);
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MWait, &mwait_tpl);
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MFree, &mfree_tpl);
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MPend, &mpend_tpl);
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MUnavail, &munavail_tpl);

// ----------------------- ciklinam per <item>-us ir generuojam sąrašą items
bool alive_present = False; // ar turim aktyvių produktų?

XmlNode *cur_node = m_pGrpCfgNode;
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&cur_node); // ieškosim tik tarp pirmos kartos <pr> vaikų – visi <item> turi būti ten
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)cur_node->m_pFirstChild;
   while((cur_node != NULL) && SUCCEEDED(retc))
   {
KpChar cur_tag = C_Nul;
      if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
      if((cur_tag == XG_Item) && SUCCEEDED(retc))
      {
// ----- tikrinam, ar čia ne launčerio įrašas
bool proceed = True;
         if(bLauncher && SUCCEEDED(retc))
         {
int cur_prod_ver = 0;
            retc = ExtractGrpLicProdVer(NULL, NULL, &cur_prod_ver, cur_node);
            if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK; // KP_ERROR(KP_E_FILE_FORMAT, null);
            if((cur_prod_ver == prod_ver) && SUCCEEDED(retc)) proceed = False;
         }
         if(proceed && SUCCEEDED(retc))
         {
// -------  vieno item failų {file} sąrašas
KpTreeEntry *item_files = NULL; // KpChar[] stringų sąrašas
            if(SUCCEEDED(retc)) retc = ExtractStartMenuSubsts(&item_files, cur_node, XG_File); // XG_File – reikšmes keičiam į lokalius failų vardus
int item_files_ix = 0; // indexas vaikščiojimui per item'o failų sąrašą

// pilnas visų meniu punkto failų vardų ilgis
int item_files_cont_len = 0;
            if((item_files != NULL) && SUCCEEDED(retc)) retc = CountKpCharListFullLength(&item_files_cont_len, item_files);

// -------  vieno item parametrų {mpar} sąrašas
KpTreeEntry *item_mpars = NULL; // KpChar[] stringų sąrašas
            if(SUCCEEDED(retc)) retc = ExtractStartMenuSubsts(&item_mpars, cur_node, XG_MPar, item_files, &item_files_ix); // XG_MPar – reikšmėse išskleidžiam makrokomandas {file}
int item_mpars_ix = 0; // indexas vaikščiojimui per item'o failų sąrašą

// pilnas visų meniu punkto parametrų tekstų ilgis
int item_mpars_cont_len = 0;
            if((item_mpars != NULL) && SUCCEEDED(retc)) retc = CountKpCharListFullLength(&item_mpars_cont_len, item_mpars);

// ---- {appname}
KpChar *app_name = NULL;
            if(SUCCEEDED(retc)) retc = GetGrpItemAppName(NULL, &app_name, cur_node, True); // False);
            KP_ASSERT(app_name != NULL, KP_E_FILE_FORMAT, null, True);

// ---- {app}
KpChar *inst_path = NULL;
            if(SUCCEEDED(retc))
            {
               retc = GetGrpInstPath(null, &inst_path, cur_node);
               if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
            }

// ---- {launch}
KpChar *launch_val = NULL;
bool installed = False;
            if(SUCCEEDED(retc))
            {
               retc = GetGrpLaunch(null, &launch_val, &installed, cur_node);
               if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
            }

// ----- {setup}
KpChar *setup_val = NULL;
            if(SUCCEEDED(retc)) retc = cur_node->ExtractSubnodeContents(XG_Setup, &setup_val);

// ----- {setupsize}
KpChar setupsize_val[MAX_XML_PAR_VAL_LEN + 1];
            setupsize_val[0] = C_Nul;
XmlNode *setup_node = NULL;
            if(SUCCEEDED(retc)) retc = cur_node->SearchChildSubNode(XG_Setup, &setup_node);
            if((setup_node != NULL) && SUCCEEDED(retc))
            {
XmlTagPars *tag_pars = NULL;
               if(SUCCEEDED(retc)) retc = setup_node->GetTagParsPtr(&tag_pars);
               KP_ASSERT(tag_pars != NULL, KP_E_FILE_FORMAT, null, True);

               if(SUCCEEDED(retc))
               {
int par_num = 0;
                  retc = tag_pars->SeekKpTextPar("size", setupsize_val, &par_num);
                  if(FAILED(retc)) setupsize_val[0] = C_Nul;
                  retc = S_OK;
               }
            }

// ----- {lic}
KpChar *lic_val = NULL;
            if(SUCCEEDED(retc)) retc = cur_node->ExtractSubnodeContents(XG_Licence, &lic_val);

// --------- <status>
KpChar *status_val = NULL;
            if(SUCCEEDED(retc)) retc = cur_node->ExtractSubnodeContents(XG_Status, &status_val);
XmlGrpStatus status = XGS_None;
            if((status_val != NULL) && SUCCEEDED(retc)) retc = GetKwrdIntIndex((int *)&status, status_val, piazGrpStuses,
               XGS_NumOfStat, True);

// ------------------------ pasirenkam šabloną
XmlNode *prc_node = NULL;
KpChar *prc_val = NULL;

XmlNode *prc_val_node = NULL;

            if(SUCCEEDED(retc))
            {
               if(installed &&  // if(inst_path[0] != C_Nul)
                  (status != XGS_Unavailable))
               {
// jau įdiegtas
                  KP_ASSERT(mitem_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                  item_tpl = mitem_tpl;
               }
               else
               {
                  switch(status)
                  {
                  case XGS_Wait:
// dar nepasiekiamas
                     KP_ASSERT(mwait_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                     item_tpl = mwait_tpl;
                     break;

                  case XGS_Unavailable:
// įdiegtas kitame kompiuteryje
                     KP_ASSERT(munavail_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                     item_tpl = munavail_tpl;
                     break;


                  case XGS_Available:
// užimtas, bet buvo aktyvuotas šitame kompiuteryje
                     if(installed) // if(inst_path[0] != C_Nul)
                     {
// jau įdiegtas
                        KP_ASSERT(mitem_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                        item_tpl = mitem_tpl;
                        break;
                     }
// diegimas dingęs – reikia pakartoti
                  case XGS_Free:
// laisvas, galima siųstis
                     KP_ASSERT(mfree_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                     item_tpl = mfree_tpl;

                     KP_ASSERT(setup_val != NULL, KP_E_FILE_FORMAT, null, True);

// o gal jau šiuo metu siunčiamas?
                     if(SUCCEEDED(retc)) retc = cur_node->SearchChildSubNode(XG_Prc, &prc_node);
                     if((prc_node != NULL) && SUCCEEDED(retc))
                     {
                        KP_ASSERT(mpend_tpl != NULL, KP_E_FILE_FORMAT, null, True);
                        item_tpl = mpend_tpl;

                        if(SUCCEEDED(retc)) retc = prc_node->ExtractContents(&prc_val);
                     }
                     break;

                  default:
                     KP_ERROR(KP_E_FILE_FORMAT, null);
                     break;
                  }
               }
            }

            KP_ASSERT(item_tpl != NULL, KP_E_SYSTEM_ERROR, null, True);

            alive_present |= (item_tpl == mitem_tpl); // turim aktyvų produktą

// ---- skleidžiam meniu punktą, pakeisdami makrokomandas reikšmėmis
int item_val_len = 0;
            if(SUCCEEDED(retc))
            {
               item_val_len = TvKpStrLen(item_tpl) + item_files_cont_len + item_mpars_cont_len +
                  TvKpStrLen(app_name) * 4 + 100;
               if(inst_path != NULL) item_val_len += TvKpStrLen(inst_path);
               if(launch_val != NULL) item_val_len += TvKpStrLen(launch_val); // <launch> gali ir nebūti
            }

KpChar *item_src = NULL;
            KP_NEWA(item_src, KpChar, item_val_len + 1);

KpChar *item_val = NULL;
            KP_NEWA(item_val, KpChar, item_val_len + 1);

            if(SUCCEEDED(retc)) TvKpStrCpy(item_src, item_tpl);

// keičiam
            while(SUCCEEDED(retc))
            {
KpStGrpSubster subster(item_val, item_val_len, item_src, item_files, &item_files_ix,
                     item_mpars, &item_mpars_ix, app_name, inst_path, launch_val,
                     setup_val, setupsize_val, lic_val, prc_val);
               if(SUCCEEDED(retc)) retc = subster.SubstGrpTpl();

// ar dar liko makrokomandų?
               if(SUCCEEDED(retc))
                  if(
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_FILE_W) == NULL) && // "{file}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_MPAR_W) == NULL) && // "{mpar}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_APPNAME_W) == NULL) && // "{appname}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_APP_W) == NULL) && // "{app}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_LAUNCH_W) == NULL) && // "{launch}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_SETUP_W) == NULL) && // "{setup}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_SETUPSIZE_W) == NULL) && // "{setupsize}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_LIC_W) == NULL) && // "{lic}"
                     (TvKpStrStr(item_val, KPST_GRP_MACRO_PRC_W) == NULL) // "{prc}"
                    )
                     break; // neliko

               if(SUCCEEDED(retc)) TvKpStrCpy(item_src, item_val);
            }

// ---- pridedam prie sąrašo
            if(SUCCEEDED(retc))
            {
               if(items == NULL) KP_NEWO(items, KpTreeEntry(item_val, NULL))
               else retc = items->PutToEnd(item_val);
            }

// ----- trinam item laikinus objektus
            KP_DELETEA(inst_path);
            KP_DELETEA(launch_val);
            KP_DELETEA(item_val);
            KP_DELETEA(item_src);
            KP_DELETE(item_files);
            KP_DELETE(item_mpars);
            KP_DELETEA(app_name);

// ------------
         } // if(proceed && SUCCEEDED(retc))


      } // if((cur_tag == XG_Item) && SUCCEEDED(retc))

      if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&cur_node); // tolimesnis brolis

   } // while((cur_node != NULL) && SUCCEEDED(retc))

// ------------ sukuriam failą – aktyvių produktų indikatorių; pagal jo buvimą neleisim išdiegt lentynos
   if(SUCCEEDED(retc))
   {
      if(alive_present)
      {
fstream out_file((const char *)KPST_GRP_ALIVE_PRESENT_FILE_NAME, ios::out);
         KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, KPST_GRP_ALIVE_PRESENT_FILE_NAME, False);
         if(!out_file.fail())
         {
            out_file << alive_present << endl;
            KP_ASSERT(!out_file.fail(), KP_E_FERROR, KPST_GRP_ALIVE_PRESENT_FILE_NAME, False);
            if(!out_file.fail())
            {
               out_file.close();
               KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, KPST_GRP_ALIVE_PRESENT_FILE_NAME, False);
            }
         }
      }
      else KP_ASSERT(DeleteFile((const char *)KPST_GRP_ALIVE_PRESENT_FILE_NAME), KP_E_DIR_ERROR, GetLastError(), False);
   }

// ------------ pilnas visų meniu punktų sąrašo suminio teksto ilgis
int items_cont_len = 0;
   if((items != NULL) && SUCCEEDED(retc)) retc = CountKpCharListFullLength(&items_cont_len, items);

// ------------------------ uodegos šablonas
KpChar *tail_tpl = NULL;
   if(SUCCEEDED(retc)) retc = pr_node->ExtractSubnodeContents(XG_MTail, &tail_tpl);
   KP_ASSERT(tail_tpl != NULL, KP_E_FILE_FORMAT, null, True);

// ------------------------ formuojam uodegą
int tail_buf_len = 0;
   if(SUCCEEDED(retc)) tail_buf_len = TvKpStrLen(tail_tpl) + top_files_cont_len + 100;
KpChar *tail_buf = NULL;
   KP_NEWA(tail_buf, KpChar, tail_buf_len + 1);
   if(SUCCEEDED(retc)) tail_buf[0] = C_Nul;

KpStGrpSubster subster1(tail_buf, tail_buf_len, tail_tpl, top_files, &top_files_ix);
   if(SUCCEEDED(retc)) retc = subster1.SubstGrpTpl();

// ----------------------- trinam seną meniu buferį
   KP_DELETEA(m_lpszGrpMenu);

// ----------------------- gaminam meniu failo turinio buferį
int menu_file_length = 0;
   if(SUCCEEDED(retc)) menu_file_length = (head_buf_len + items_cont_len + tail_buf_len) * 2; // kad tilptų dvigubi UTF-8 simboliai
   KP_NEWA(m_lpszGrpMenu, unsigned char, menu_file_length + 1);

// ---------------- buferinio failo vardas
unsigned char file_name[KP_MAX_FNAME_LEN + 1];
   file_name[0] = Nul;
   if(SUCCEEDED(retc)) sprintf((char *)file_name, "%x %x", m_lpszGrpMenu, menu_file_length);

// ------------- atidarom buferinį failą
TvXmlUniFile *out_file = NULL;
   KP_NEWO(out_file, TvXmlUniFile(file_name, (const unsigned char *)"w",
                           XL_FT_DataFile, CreateNewBFile, // CreateNewUniBFile,
                           False, UC_UTF_8));

// ----- rašom meniu
   if(SUCCEEDED(retc)) out_file->PutKpStr(head_buf, False);
   if(SUCCEEDED(retc)) retc = out_file->PutChar(C_Lf, False);

KpTreeEntry *cur_entry = items;
   while((cur_entry != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = out_file->PutKpStr((KpChar *)cur_entry->GetValue(), False);
      if(SUCCEEDED(retc)) retc = out_file->PutChar(C_Lf, False);
//    if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild((KpTreeEntry **)&cur_entry);
      if(SUCCEEDED(retc)) cur_entry = (XmlNode *)cur_entry->m_pFirstChild;
   }

   if(SUCCEEDED(retc)) out_file->PutKpStr(tail_buf, False);
   if(SUCCEEDED(retc)) retc = out_file->PutChar(C_Lf, False);

   if(SUCCEEDED(retc)) out_file->CloseFile(True);

   KP_DELETE(out_file);

// ------------------------------------ rašom m_lpszGrpMenu[] į KPST_GRP_MENU_FNAME
   if(SUCCEEDED(retc)) retc = SaveGrpMenu();

// ------------------------- trinam bendrus laikinus objektus
   KP_DELETE(items);
   KP_DELETEA(head_buf);
   KP_DELETEA(tail_buf);
   KP_DELETE(top_files);

return(retc);
}


#ifndef KPST_PRODGRP_OLD_LOGIN
// --------------------------------------------------
HRESULT KpStApp::GenLoginDlg(void)
{
HRESULT retc = S_OK;
HRESULT retc_sav = S_OK;

// PutLogMessage_("KpStApp::GenLoginDlg() 1");

// ----------------------- logino fono paveiksliukas – užkoduojamas ir į failą
unsigned char *file_buf = null;
long file_len = StartGrp_fonas_len;
#ifdef IBSHT_ENCODED
      KP_NEWA(file_buf, unsigned char, file_len + 4 + 1);

      if(SUCCEEDED(retc)) memcpy(file_buf, StartGrp_fonas, file_len);

int prod_ver = 0;
      if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

//    if(SUCCEEDED(retc)) retc = EnctBufMed(file_buf, file_len, prod_ver, 0L);
      if(SUCCEEDED(retc)) retc = EnctBufInc(file_buf, file_len, prod_ver, 0L, True);
#else
      file_buf = StartGrp_fonas;
#endif

HANDLE fonas_file = INVALID_HANDLE_VALUE;
      if(SUCCEEDED(retc))
      {
         fonas_file = CreateFile((const char *)KPST_GRP_FONAS_FNAME, GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
         KP_ASSERT(fonas_file != INVALID_HANDLE_VALUE, KP_E_DIR_ERROR, KPST_GRP_FONAS_FNAME, True);
      }

// rašom
DWORD written = 0;
      KP_ASSERT(WriteFile(fonas_file, (const char *)file_buf, file_len, &written, NULL), KP_E_FERROR, KPST_GRP_FONAS_FNAME, True);
      KP_ASSERT(written == file_len, KP_E_FERROR, KPST_GRP_FONAS_FNAME, False);

      if(fonas_file != INVALID_HANDLE_VALUE)
         KP_ASSERT(CloseHandle(fonas_file), KP_E_FERROR, KPST_GRP_FONAS_FNAME, True);

#ifdef IBSHT_ENCODED
      KP_DELETEA(file_buf);
#endif

// ----------------------- logino kodas į meniu buferį
      KP_DELETEA(m_lpszGrpMenu);

const unsigned char *login_file_buf = lpszStartGrpLoginHtml;
#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ----------------------------- socketo kūrimas
unsigned char *rcv_buf = null;

      if(SUCCEEDED(retc))
      {
KpSocket *sock_ptr = NULL;
         KP_NEWO(sock_ptr, KpSocket);

// ------------------------------ jungiamės
         if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_GRP_LOGIN_URL, False);
         if(SUCCEEDED(retc)) retc = sock_ptr->Connect(False);

// ------------------------------ siunčiam užklausą
         if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, KPST_GRP_LOGIN_FILE, False);

// ------------------------------ priimam logino html-ą
long read = 0L; // 10000L;
//       KP_NEWA(rcv_buf, unsigned char, read + 1);

         if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpMsg(&rcv_buf, &read, False);
         if(SUCCEEDED(retc))
         {
            rcv_buf[read] = Nul;
            login_file_buf = rcv_buf;
         }

         retc_sav = retc;
         retc = S_OK;

         KP_DELETE(sock_ptr);
      }
#endif

// ----------------------------- kopijuojam lokalų logino HTML
      KP_NEWA(m_lpszGrpMenu, unsigned char, strlen(login_file_buf) + 1);
      if(SUCCEEDED(retc)) strcpy(m_lpszGrpMenu, login_file_buf);

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
      KP_DELETEA(rcv_buf);
#endif

// ------------------------------------ rašom m_lpszGrpMenu[] į KPST_GRP_MENU_FNAME
      if(SUCCEEDED(retc)) retc = SaveGrpMenu();

// --------------------
      if(SUCCEEDED(retc)) if(m_pGrpKpPubDlg != NULL) m_pGrpKpPubDlg->m_bRefresh = True;


// --------------------
   if(SUCCEEDED(retc)) retc = retc_sav;

return(retc);
}
#endif


// --------------------------------------------------
HRESULT KpStApp::Login(void)
{
HRESULT retc = S_OK;
HRESULT retc_sav = S_OK;

   m_bLogin = True;

unsigned char pwd[TV_TAG_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetIniUserPwd(pwd);

   if(SUCCEEDED(retc)) if(pwd[0] == Nul) // tik jei po logoffo – logoff tiesiog išvalo slaptažodį
   {
#ifdef KPST_PRODGRP_OLD_LOGIN
      KP_ASSERT(KpstEdiDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) retc = KpstEdiDialogPtr->OpenWindow((const unsigned char *)"");
      if(SUCCEEDED(retc))
      {
         retc = KpstEdiDialogPtr->DoEdit(0);
      /* if(SUCCEEDED(retc)) retc = */ KpstEdiDialogPtr->CloseWindow();
      }
#else
// bool refresh_sav = m_bGrpRefreshFlg;
//     m_bGrpRefreshFlg = False;

// ----------------------- išvalom lango rėmą
#  if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(m_pGrpKpPubDlg != NULL)
      {
#     if FALSE // mygtukai kažko nesusikuria antrą kartą (bitmapas nesiselektina į HDC?); bet neištrynus antrą kartą išėjus į loginą, būna dvigubas m_ButMinimize
         if(m_pGrpKpPubDlg->m_ButExit != NULL) ::DestroyWindow(m_pGrpKpPubDlg->m_ButExit);
         m_pGrpKpPubDlg->m_ButExit = NULL;

         if(m_pGrpKpPubDlg->m_ButMinimize != NULL) ::DestroyWindow(m_pGrpKpPubDlg->m_ButMinimize);
         m_pGrpKpPubDlg->m_ButMinimize = NULL;
#     endif
         if(m_pGrpKpPubDlg->m_hBackGround != NULL) ::DestroyWindow(m_pGrpKpPubDlg->m_hBackGround);
         m_pGrpKpPubDlg->m_hBackGround = NULL;

         if(m_pGrpKpPubDlg->m_BgrBmpData.m_hBitMap != NULL) DeleteObject(m_pGrpKpPubDlg->m_BgrBmpData.m_hBitMap);
         m_pGrpKpPubDlg->m_BgrBmpData.m_hBitMap = NULL;

         m_pGrpKpPubDlg->m_iWndSoftHorBorderWdt = m_pGrpKpPubDlg->m_iWndSoftTopBorderWdt = m_pGrpKpPubDlg->m_iWndSoftBotBorderWdt = IBSH_WND_SOFT_BORDER_WDT;
         m_pGrpKpPubDlg->m_iWndSoftCaptHgt = IBSH_WND_SOFT_CAPTION_HGT;

         m_pGrpKpPubDlg->CreateBackground();
      }
#  endif

// --------------------
      if(SUCCEEDED(retc)) retc_sav = GenLoginDlg();

// ----------------- logino dialogas
      if(SUCCEEDED(retc)) retc = ProcStartMenu();
      if(retc == KP_S_LOGOFF) retc = KP_E_CANCEL; // Paspaustas mygtukas „Atšaukti“
      if(m_pGrpKpPubDlg != NULL)
      {
         if(m_pGrpKpPubDlg->m_bLogoff && SUCCEEDED(retc)) retc = KP_E_CANCEL; // Paspaustas mygtukas „Atšaukti“ // ne, jau konvertavosi į retc == KP_S_LOGOFF
         m_pGrpKpPubDlg->m_bLogoff = m_pGrpKpPubDlg->m_bClose = False; // iš ProcStartMenu() išeina per m_bClose, programą reikia tęsti
      }

//    m_bGrpRefreshFlg = (m_bGrpRefreshGlobalFlg?refresh_sav:False);
#endif

      if(SUCCEEDED(retc)) retc = SaveIni();
   }

   m_bLogin = False;

   if(SUCCEEDED(retc)) retc = retc_sav;

return(retc);
}


// --------------------------------------------------
HRESULT KpStApp::ProcDoLogin(const unsigned char *lpszGetPars) // lpszGetPars: "?cmd=1&user=vardas&pwd=slaptazodis"
{
HRESULT retc = S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;

   KP_ASSERT(lpszGetPars != null, E_INVALIDARG, null, True);

int cmd = 0;
unsigned char par_val[KP_MAX_FILE_LIN_WDT + TV_TAG_LEN + 1];

   if(SUCCEEDED(retc))
   {
      pnts = strstr(lpszGetPars, "cmd=");
      KP_ASSERT(pnts != null, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc))
      {
         pnts += strlen("cmd=");
         sscanf((const char *)pnts, "%d", &cmd);
      }
   }

   if(SUCCEEDED(retc)) switch(cmd)
   {
   case 1:
      pnts = strstr(lpszGetPars, "user=");
      KP_ASSERT(pnts != null, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc))
      {
         pnts += strlen("user=");
         strncpy(par_val, pnts, KP_MAX_FILE_LIN_WDT);
         par_val[KP_MAX_FILE_LIN_WDT] = Nul;
         pntd = strchr(par_val, '&');
         if(pntd != null) *pntd = Nul;

         retc = SetIniUserData(par_val);
      }

      if(SUCCEEDED(retc))
      {
         pnts = strstr(lpszGetPars, "pwd=");
         KP_ASSERT(pnts != null, E_INVALIDARG, null, True);
      }
      if(SUCCEEDED(retc))
      {
         pnts += strlen("pwd=");
         strncpy(par_val, pnts, TV_TAG_LEN);
         par_val[TV_TAG_LEN] = Nul;
         pntd = strchr(par_val, '&');
         if(pntd != null) *pntd = Nul;

         retc = SetIniUserPwd(par_val);
      }

      break;

   case 2:
      retc = KP_E_CANCEL;
      break;

   default:
      KP_ERROR(E_INVALIDARG, null);
      break;
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpStApp::OpenShowHtml(void)
{
HRESULT retc = S_OK;

// ------------------------
KpFileSys *lzdsh_search = NULL;
   KP_NEWO(lzdsh_search /* m_pGrpKpFileSys */, iBshFileSys);

// ------------------------
   if(SUCCEEDED(retc)) retc = lzdsh_search /* m_pGrpKpFileSys */->OpenFiles(null, XM_VERS_XHTML,
#ifdef IBSHT_ENCODED
      CreateNewUniBFile);
#else
      CreateNewUniFile);
#endif

// ------------------------
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   KP_NEWO(m_pGrpKpPubDlg, iBshDlg(lzdsh_search /* m_pGrpKpFileSys */, IBSH_OUT_VERS, UC_PlainText, prod_name));

// ------------------------
   if(SUCCEEDED(retc)) retc = m_pGrpKpPubDlg->OpenWindow(hKpInstance, False);

return(retc);
}


// --------------------------------------------------
HRESULT KpStApp::CloseShowHtml(void)
{
HRESULT retc = S_OK;

   KP_DELETE(m_pGrpKpPubDlg);
// KP_DELETE(m_pGrpKpFileSys);

return(retc);
}


// --------------------------------------------------
HRESULT KpStApp::ProcStartMenu(void)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_pGrpKpPubDlg != NULL, KP_E_OUTOFMEM, null, True);
   KP_ASSERT(m_pGrpKpPubDlg->m_pKpFileSys != NULL, KP_E_OUTOFMEM, null, True);

// --------------------
   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();
   if(m_pGrpKpPubDlg != NULL) m_pGrpKpPubDlg->WaitForXGecko();

// nustatyti galimai pasikeitusį m_pGrpKpPubDlg->m_pKpFileSys->m_lpszCurSearchKwd

// if(SUCCEEDED(retc)) m_pGrpKpPubDlg->m_pKpFileSys->m_lCurEntryId = (-1L);
   if(SUCCEEDED(retc)) // if(m_pGrpKpPubDlg->m_pKpFileSys->m_lThreadId == 0)
       retc = m_pGrpKpPubDlg->m_pKpFileSys->SearchForEntry(m_pGrpKpPubDlg, KPST_GRP_MENU_FNAME);

// semaforą išlaisvins besibaigiantis XKpGeckoStream::read()
// taip neveikia
   if(m_pGrpKpPubDlg != NULL) if(m_pGrpKpPubDlg->m_pKpFileSys != NULL)
      m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

// --------------------
// if(SUCCEEDED(retc)) retc = m_pGrpKpPubDlg->ShowDialog();
   if(SUCCEEDED(retc)) retc = m_pGrpKpPubDlg->DoEdit();
// if(SUCCEEDED(retc)) retc = m_pGrpKpPubDlg->HideDialog();

// PutLogMessage_("KpStApp::ProcStartMenu() 1 retc %x  KP_S_LOGOFF %x  m_bLogoff %d  m_bClose %d", retc, KP_S_LOGOFF, m_pGrpKpPubDlg->m_bLogoff, m_pGrpKpPubDlg->m_bClose);

// --------------------
// Iš meniu grįžo komanda Logoff/Login
   if(SUCCEEDED(retc)) if(m_pGrpKpPubDlg->m_bLogoff)
   {
      if(SUCCEEDED(retc)) m_pGrpKpPubDlg->m_bLogoff = False;
      if(SUCCEEDED(retc)) retc = GrpLogoff();
      retc = KP_S_LOGOFF;
   }

// PutLogMessage_("KpStApp::ProcStartMenu() 2 retc %x  KP_S_LOGOFF %x  m_bLogoff %d  m_bClose %d", retc, KP_S_LOGOFF, m_pGrpKpPubDlg->m_bLogoff, m_pGrpKpPubDlg->m_bClose);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GrpLogoff(void)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc)) retc = SetIniUserPwd((const unsigned char *)"");
   if(SUCCEEDED(retc)) retc = SaveIni();

// if(SUCCEEDED(retc)) retc = InitGrpCfg();
// if(SUCCEEDED(retc)) retc = SaveGrpCfg();

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CheckUpdateSvrRequest(const unsigned char *lpszChkUpdCmd, bool bOutMsg)
{
HRESULT retc = S_OK;
unsigned char *out_buf = null;
bool skip_file = False;
KpString dat_str;
   dat_str = "";
int num_of_lics = 0;
bool bound;
unsigned char *msg_buf = null;
unsigned char str_buf[100];
long /* DWORD */ /* int */ prod_var = -1L; // 0L;
KpSocket *sock_ptr = NULL;

PutLogMessage_("KpStApp::CheckUpdateSvrRequest() 1");

// ---------------------
   KP_NEWA(out_buf, unsigned char, KP_MAX_FILE_LIN_LEN*3 + 1);

// ---------------------
   if(SUCCEEDED(retc))
   {

   if(lpszChkUpdCmd != null) // atnaujinimas nuotolinis, atėjęs per POST į kpstisvr.exe
   {
const unsigned char *pnts = strstr(lpszChkUpdCmd, KPST_CHK_UPDATE_CMD); // "PI="
      KP_ASSERTE(pnts != null, E_INVALIDARG, lpszChkUpdCmd, bOutMsg);
      KP_ASSERTE(strlen(pnts) < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, lpszChkUpdCmd, bOutMsg);
      if(SUCCEEDED(retc)) strcpy(out_buf, pnts);
   }
   else // lokalus atnaujinimas – traukiam visus reikalingus parametrus
   {
// -----------------------------------
      if(SUCCEEDED(retc)) retc = GetIniBound(&bound);
//    if(SUCCEEDED(retc)) retc = GetIniProdVer(&iProdVerGlob);
      if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics);

// ---------------------------------- ProdVar iš registro "Installed"
      if(SUCCEEDED(retc)) retc = GetProdVarReg();
      if(SUCCEEDED(retc)) prod_var = m_ProdVar;

// -----------------------------------
      KP_NEWA(msg_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

// #ifdef KPST_UPDATE_OLD_INTERFACE
      if(SUCCEEDED(retc))
      {
         retc = GetSavedKeyDat(&dat_str);
         if(FAILED(retc))
         {
            retc = KpErrorProc.OutputErrorMessage(retc, null, (num_of_lics == 0) && bound, __FILE__, __LINE__, 0L, NULL);
            skip_file = True;
         }
      }

// PI=73R2-LL54-3UUR-1UJ3  722G-89UU-LLA7-LR8E  0  [dBI+9,+B]:1505+*,=*/,BZ/;)190*+B   0  0  1  33650 RRqlniqQk   ]:1505+*,=*/,  32 0  2  6  0     6000  0&ProdVer=2010&ProdVar=7
// dat_str = "73R2-LL54-3UUR-1UJ3\t722G-89UU-LLA7-LR8E\t0\t[dBI+9,+B]:1505+*,=*/,BZ/;)190*+B\t0\t0\t1\t33650\tRRqlniqQk\t]:1505+*,=*/,\t32\t0\t2\t6\t0\t\t6000\t0";
// dat_str = "XXX !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~XXX";

// GGG11-12:
// PI=JJJJ-JJJJ-JJJJ-JJJJ%09JJJJ-JJJJ-JJJJ-JJJJ%090%09%5bdBI%2b9%2c%2bB150%3a%3d%297%3d%2bBZ%2f%3b%29190*%2bB%090%090%091%090%09RRqmnkqQj%09150%3a%3d%297%3d%2b%0932%090%092%096%091%09%097600%090&ProdVer=1072&ProdVar=0
// atsakymas tuščias:
//
// HTTP/1.1 302 Found
// Date: Tue, 13 Mar 2012 16:25:20 GMT
// Server: Apache
// Location: http://new.tev.lt/
// Transfer-Encoding: chunked
// Content-Type: text/html
//
// 0
//

// WinLED:
// PI=R5LG-J135-AJ9A-E8J6%09LJ88-23JJ-A2J5-JAU1%090%09%5bdBI%2b9%2c%2bB150%3a%3d%297%3d%2bBZ%2f%3b%29190*%2bB%090%090%091%0943627%09RRqmnkqQj%09150%3a%3d%297%3d%2b%0940%090%092%096%091%09%097600%090&ProdVer=3012&ProdVar=0
// atsakymas:
//
// HTTP/1.1 200 OK
// Date: Tue, 13 Mar 2012 16:34:00 GMT
// Server: Apache
// Transfer-Encoding: chunked
// Content-Type: application/vnd.fdf
//
// 4bd
//
// %FDF-1.2
// 1 0 obj
// <<
//   /FDF
//   <<
//     /JavaScript
//     <<
//      /After (var versija1  =
//  {
//      initialize: function(dialog)
//     {
//       dialog.load(
//         {
//           "miau": 'Rastas programos atnaujinimas. Ar norite eiti \\u012F siuntini\\u0173 puslap\\u012F?',
//          }
//       );
//     },
//     commit: function(dialog) {
//     app.doc.getURL("http://updates.tev.lt/check.php?ProdVer=3012&ProdVar=-1",false);
//     app.doc.getURL("http://updates.tev.lt/check.php?ProdVer=3012&ProdVar=-1",false);
//     },
//
//
//     description:
//     {
//         name: "Nauja versija!",
//         elements:
//         [
//            {
//               type: "view",
//               width: 60,
//               heigth: 52,
//               elements:
//               [
//                  {
//                     item_id: "miau",
//                     type: "static_text",
//                     width: 350,
//                  },
//                  {
//                   type: "ok_cancel",
//                   ok_name: "Taip",
//                   cancel_name: "Ne",
//
//                   },
//               ]
//            },
//
//          ]
//       }
// };
//
// app.execDialog(versija1);
//
//
//
// 	     )
//     >>
//
//   >>
// >>
// endobj
// trailer
// <<
// /Root 1 0 R
// >>
// %%EOF
//

// -----------------------------------
      if((!skip_file) && SUCCEEDED(retc))
      {
         strcpy(out_buf, "PI=");
         if((strlen(out_buf) + dat_str.length()) >= KP_MAX_FILE_LIN_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if((!skip_file) && SUCCEEDED(retc))
      {
         strcpy(msg_buf, dat_str.ExtractUnsignedValueA());

#if FALSE
char str_buf[100];
sprintf(str_buf, "%d", dat_str.length());
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif

         retc = EncodePostMsg(out_buf + 3, msg_buf); // nuo "PI=" pabaigos
      }

// #else // #ifdef KPST_UPDATE_OLD_INTERFACE
//    if(SUCCEEDED(retc)) strcpy(out_buf, KPST_CHK_UPDATE_URL); // "http://updates.tev.lt/versija_n.php" // kodėl ne "/versija_n.php" ?
// #endif

      if((!skip_file) && SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, KPST_CHK_UPDATE_FORMAT, /* 2010 */ iProdVerGlob, prod_var);
         if((strlen(out_buf) + strlen(str_buf)) >= KP_MAX_FILE_LIN_LEN*3)
            retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if((!skip_file) && SUCCEEDED(retc))
      {
         strcat(out_buf, str_buf);

#if FALSE
fstream out_file("rcv.txt", ios::out);
out_file << out_buf;
out_file.close();
#endif
      }
PutLogMessage_("KpStApp::CheckUpdateSvrRequest(): %s skip_file: %d retc: %x", out_buf, skip_file, retc);

// ---------------------
   } // else // if(lpszChkUpdCmd != null)

   } // if(SUCCEEDED(retc))


// -----------------------------------
   if((!skip_file) && SUCCEEDED(retc))
   {
// ----------------------- siunciam requestą
      KP_NEWO(sock_ptr, KpSocket);

      if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_CHK_UPDATE_URL, bOutMsg); // "http://updates.tev.lt/versija.php" // kodėl ne "http://updates.tev.lt"?
PutLogMessage((const unsigned char *)"CheckUpdate()", null);
      if(SUCCEEDED(retc)) retc = sock_ptr->Connect(bOutMsg);

// #ifdef KPST_UPDATE_OLD_INTERFACE
      if(SUCCEEDED(retc))
         retc = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD, // "POST"
            KPST_CHK_UPDATE_URL, // "http://updates.tev.lt/versija.php" // kodėl ne "/versija.php" ?
            bOutMsg, strlen(out_buf));
      if(SUCCEEDED(retc)) retc = sock_ptr->SendMsg(out_buf, strlen(out_buf), bOutMsg);
PutLogMessage_("KpStApp::CheckUpdateSvrRequest(): out_buf: %s", out_buf);
// #else
//    if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, out_buf, bOutMsg);
// #endif

// gaudom atsakymą
      out_buf[0] = Nul;

long ll = KP_MAX_FILE_LIN_LEN;
      if(SUCCEEDED(retc)) retc=sock_ptr->RcvHttpMsg(out_buf, &ll, bOutMsg);
      if(((ll < 0) || (ll > KP_MAX_FILE_LIN_LEN)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef KPST_PRODGRP_STATIC_CFG
// if(FAILED(retc))
   {
      if(lpszChkUpdCmd != null)
      {
         if(strstr(lpszChkUpdCmd, "&ProdVer=3012&") != null)
         {
            retc = S_OK;
            KP_ASSERT(strlen(lpszUpdCfgDefLzdshp) < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)){ strcpy(out_buf, lpszUpdCfgDefLzdshp); ll = strlen(out_buf); }
         }
         if(strstr(lpszChkUpdCmd, "&ProdVer=1072&") != null)
         {
            retc = S_OK;
            KP_ASSERT(strlen(lpszUpdCfgDefGGG11_12) < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)){ strcpy(out_buf, lpszUpdCfgDefGGG11_12); ll = strlen(out_buf); }
         }
      }
   }
#endif

      if(SUCCEEDED(retc)) out_buf[ll] = Nul;

#if FALSE // #if TRUE //
// KpMsgOut(msg_buf, IDI_ASTERISK, KP_MB_TESTI);
{
fstream out_file("vnd.fdf", ios::out);
out_file << out_buf;
out_file.close();
}
#endif

      KP_DELETE(sock_ptr);

   } // if((!skip_file) && SUCCEEDED(retc))

// atnaujinam m_lpszGrpCfgBuf[]
   if(SUCCEEDED(retc))
   {
      KP_DELETEA(m_lpszGrpCfgBuf);
      m_lpszGrpCfgBuf = out_buf;
      out_buf = null;
   }
   else KP_DELETEA(out_buf);

   KP_DELETEA(msg_buf);

return(retc);
}


#ifdef KPST_UPDATE_OLD_INTERFACE
// -------------------------------------------
HRESULT KpStApp::ParseUpdFdf(bool bOutMsg) // parsina m_lpszGrpCfgBuf[] esantį update FDF failą, permeta į atsisiuntimo puslapį, jeigu yra atnaujinimas
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char *url_buf = NULL;
unsigned char *msg_buf = NULL;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

// -----------------------------------
   KP_NEWA(msg_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);
   KP_NEWA(url_buf, unsigned char, KP_MAX_FNAME_LEN + 1);

   url_buf[0] = Nul; // atnaujinimo nėra

// --------------------- parsinam gauta .fdf su javascriptu
// ------------ dialog.load
   if(SUCCEEDED(retc))
   {
      pnts = strstr(m_lpszGrpCfgBuf, "dialog.load");
      if(pnts == NULL)
      {
         retc = KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }
   if(SUCCEEDED(retc))
   {
      while((*pnts != ':') && *pnts) pnts++;
      if(*pnts == Nul)
      {
         retc = KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }
   if(SUCCEEDED(retc))
   {
      pnts++; // ':'
      while(strchr(lpszSpcEol, *pnts)) pnts++;
      if(*pnts == '\'') pnts++;
      else
      {
         retc = KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }
   if(SUCCEEDED(retc))
   {
      pntd = msg_buf;
      while((*pnts != '\'') && *pnts && SUCCEEDED(retc))
      {
         if(pntd - msg_buf >= KP_MAX_FILE_LIN_LEN)
            retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) *pntd++ = *pnts++;
      }
   }
   if(SUCCEEDED(retc))
   {
      *pntd = Nul;
      if(*pnts == Nul)
      {
         retc = KP_E_MSG_FORMAT;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }
   if(SUCCEEDED(retc)) retc = DecodePdfParText(msg_buf, msg_buf);

// ----------- app.doc.getURL
   if(SUCCEEDED(retc))
   {
      pnts = strstr(m_lpszGrpCfgBuf, "app.doc.getURL");
      if(pnts != NULL)
      {
         while((*pnts != '\"') && *pnts) pnts++;
         if(*pnts == Nul)
         {
            retc = KP_E_MSG_FORMAT;
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            pnts++; // '\"'

            pntd = url_buf;
            while((*pnts != '\"') && *pnts && SUCCEEDED(retc))
            {
               if(pntd - url_buf >= KP_MAX_FNAME_LEN)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc)) *pntd++ = *pnts++;
            }
         }
         if(SUCCEEDED(retc))
         {
            *pntd = Nul;
            if(*pnts == Nul)
            {
               retc = KP_E_MSG_FORMAT;
               KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
         }

      } // if(pnts != NULL) // pnts = strstr(m_lpszGrpCfgBuf, "app.doc.getURL");

   } // if(SUCCEEDED(retc))

// if(SUCCEEDED(retc)) retc = DecodePdfParText(msg_buf, msg_buf);


// --------------------
   if(FAILED(retc))
   {
      url_buf[0] = Nul;
      retc = S_OK; // po klaidų - nėra atnaujinimo ir tiek
   }

// ----------------------------- dialogas - parsisiuntimo puslapio atidarymas
// KpMsgOut("Rastas programos atnaujinimas. Ar norite eiti į siuntinių puslapį?", IDI_ASTERISK, KP_MB_GERAI_ATSAUKTI);

   if(SUCCEEDED(retc))
   {

      if(url_buf[0] != Nul)
      {
         retc0 = KpMsgOut(msg_buf, IDI_ASTERISK, KP_MB_GERAI_ATSAUKTI);
         if(SUCCEEDED(retc0))
         /* retc = */ StartCmdProcess(url_buf, KPST_CUR_DIR, NULL, NULL, True /* bOutMsg */, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
      }
      else if(bOutMsg) KpMsgOut(msg_buf, IDI_ASTERISK, KP_MB_TESTI);
   }

// -----------------------------
   KP_DELETEA(url_buf);
   KP_DELETEA(msg_buf);

return(retc);
}
#endif // #ifdef KPST_UPDATE_OLD_INTERFACE


// -------------------------------------------
HRESULT KpStApp::CheckUpdate(const unsigned char *lpszChkUpdCmd, bool bForced, bool bOutMsg)
{
HRESULT retc = S_OK;
bool test_updates = True;
bool lic_flash = False;

PutLogMessage_("KpStApp::CheckUpdate() 1");

   KP_DELETE(m_aGrpDownLoads);

// ---------------------- ProdVer
int prod_ver = 0;
#ifndef KPST_UPDATE_OLD_INTERFACE
      if(SUCCEEDED(retc)) if(lpszChkUpdCmd != null)
      {
const unsigned char *pnts = null;
         pnts = strstr(lpszChkUpdCmd, KPST_CHK_UPDATE_PRODVER_CMD); // "ProdVer="
         if(pnts != null) sscanf((const char *)pnts + strlen(KPST_CHK_UPDATE_PRODVER_CMD), "%d", &prod_ver); // "ProdVer="
      }
#endif

// ---------------------- in_fname
unsigned char *ini_fname = null;
#ifndef KPST_UPDATE_OLD_INTERFACE
      if(SUCCEEDED(retc)) if(lpszChkUpdCmd != null)
      {
const unsigned char *pnts = null;
         pnts = strstr(lpszChkUpdCmd, KPSTIP_INI_FNAME_CMD); // "IF="
         if(pnts != null)
         {
            pnts += strlen(KPSTIP_INI_FNAME_CMD); // "IF="
            KP_NEWA(ini_fname, unsigned char, strlen(pnts) + 1);
            if(SUCCEEDED(retc)) strcpy(ini_fname, pnts);
unsigned char *pntd = null;
            if(SUCCEEDED(retc))
            {
               pntd = strstr(ini_fname, "&");
               if(pntd != null) *pntd = Nul;
            }
         }
      }
#endif

// -------------------------- TestUpdates
PutLogMessage_("KpStApp::CheckUpdate() 3: %x", retc);
   if(SUCCEEDED(retc)) retc = GetTestUpdates(&test_updates, prod_ver, ini_fname);
PutLogMessage_("KpStApp::CheckUpdate() 4: %x", retc);
   if(SUCCEEDED(retc)) retc = GetIniLicFlash(&lic_flash);
PutLogMessage_("KpStApp::CheckUpdate() 5: %x", retc);

// ----------------------------------
   if((test_updates || lic_flash || bForced || (lpszChkUpdCmd != null)) /* && (prod_var >= 0L) */ && SUCCEEDED(retc))
   {
PutLogMessage_("KpStApp::CheckUpdate() 6: %x", retc);
      
      retc = CheckUpdateSvrRequest(lpszChkUpdCmd, bOutMsg);

#ifdef KPST_UPDATE_OLD_INTERFACE
      if(SUCCEEDED(retc)) retc = ParseUpdFdf(bOutMsg);
#else
unsigned char *prod_name = null;
      if(SUCCEEDED(retc)) if(lpszChkUpdCmd != null)
      {
// ---------------------- ProdName
const unsigned char *pnts = null;
         pnts = strstr(lpszChkUpdCmd, KPSTIP_CHK_UPDATE_CMD); // "CU="
         if(pnts != null)
         {
            pnts += strlen(KPSTIP_CHK_UPDATE_CMD); // "CU="
            KP_NEWA(prod_name, unsigned char, strlen(pnts) + 1);
            if(SUCCEEDED(retc)) strcpy(prod_name, pnts);
unsigned char *pntd = null;
            if(SUCCEEDED(retc))
            {
               pntd = strstr(prod_name, "&");
               if(pntd != null) *pntd = Nul;
            }
         }
      }

// ---------------------- WndName
unsigned char *wnd_name = null;
      if(SUCCEEDED(retc)) if(lpszChkUpdCmd != null)
      {
const unsigned char *pnts = null;
         pnts = strstr(lpszChkUpdCmd, KPSTIP_CLOSE_WND_CMD); // "WN="
         if(pnts != null)
         {
            pnts += strlen(KPSTIP_CLOSE_WND_CMD); // "WN="
            KP_NEWA(wnd_name, unsigned char, strlen(pnts) + 1);
            if(SUCCEEDED(retc)) strcpy(wnd_name, pnts);
unsigned char *pntd = null;
            if(SUCCEEDED(retc))
            {
               pntd = strstr(wnd_name, "&");
               if(pntd != null) *pntd = Nul;
            }
         }
      }

// ---------------------- parsinam, selektinam, siunčiam updeitų sąrašą
      if(SUCCEEDED(retc)) retc = ParseGrpCfgBuf();
      if(SUCCEEDED(retc)) retc = CheckGrpResponce();
      if(SUCCEEDED(retc)) retc = SelectSetupDownload(prod_ver, prod_name, True);
      if(SUCCEEDED(retc)) retc = GrpDownLoad(True, wnd_name, prod_name);

      KP_DELETEA(prod_name);
      KP_DELETEA(wnd_name);
      KP_DELETEA(ini_fname);
#endif // #else // #ifdef KPST_UPDATE_OLD_INTERFACE

// -----------------------------
   } // if((test_updates || bForced) && SUCCEEDED(retc))

   KP_DELETE(m_aGrpDownLoads);

// -----------------------------
   if((retc == KP_E_REFUSED) || (retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR) ||
      (retc == KP_E_CANCEL)) // CheckGrpResponce() atsakymas KpReg-NoNews – tiesiog nieko nedarom
         retc = S_OK;

return(retc);
}


// -------------------------
DWORD WINAPI CheckUpdateThreadProc(LPVOID /* const unsigned char * */ lpszChkUpdCmd /* lpParameter */)
{
HRESULT retc = S_OK;
unsigned char *upd_cmd = (unsigned char *)lpszChkUpdCmd;

   if((theKpStAppPtr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_UNEXPECTED, null, True, __FILE__, __LINE__, 0L, NULL);

DWORD cur_thread = GetCurrentThreadId();

PutLogMessage_("CheckUpdateThreadProc() thread: %d pradžia", cur_thread);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->CheckUpdate(upd_cmd, False, False);

   /* if(SUCCEEDED(retc)) */ if(theKpStAppPtr != NULL) theKpStAppPtr->m_bCheckUpdPending = False;

PutLogMessage_("CheckUpdateThreadProc() pabaiga: %d [%s]", theKpStAppPtr->m_bCheckUpdPending, lpszChkUpdCmd);

   KP_DELETEA(upd_cmd); // sukurtas KpStApp::StartCheckUpdateThread(), naikinti reikia čia

PutLogMessage_("CheckUpdateThreadProc() thread: %d fin", cur_thread);

return(RET_CODE_MAIN(retc));
}


// -------------------------------------------
HRESULT KpStApp::StartCheckUpdateThread(const unsigned char *lpszChkUpdCmd)
{
HRESULT retc = S_OK;
HANDLE h_chk_thread;
DWORD chk_thread;
unsigned char *upd_cmd = null;

   if(m_bCheckUpdPending) KP_WARNING(KP_E_DOUBLE_CALL, null)
   else
   {
      m_bCheckUpdPending = True;

      if(lpszChkUpdCmd != null)
      {
         KP_NEWA(upd_cmd, unsigned char, strlen(lpszChkUpdCmd) + 1); // bus panaikintas  CheckUpdateThreadProc()
         if(SUCCEEDED(retc)) strcpy(upd_cmd, lpszChkUpdCmd);
      }

      if(SUCCEEDED(retc))
      {
         h_chk_thread = CreateThread
         (
            NULL,                   // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
            0L,                     // DWORD dwStackSize,                         // initial thread stack size
            CheckUpdateThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
            (LPVOID)upd_cmd, // lpszChkUpdCmd,          // LPVOID lpParameter,                        // argument for new thread
            0L,                     // DWORD dwCreationFlags,                     // creation flags
            (LPDWORD)&chk_thread    // LPDWORD lpThreadId                         // pointer to receive thread ID
         );
         KP_ASSERT(h_chk_thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

PutLogMessage_("KpStApp::StartCheckUpdateThread() thread: %d pradžia [%s]", chk_thread, upd_cmd);
   }

return(retc);
}


#ifndef KPST_UPDATE_OLD_LAUNCH
HRESULT KpStApp::SendCheckUpdateMsg(void) // IP pranešimą "CU=" siuntimas į kpstisvr.exe
{
HRESULT retc = S_OK;
KpSocket *sock_ptr = NULL;
static unsigned char out_buf[KP_MAX_FILE_LIN_WDT + 3 * KP_MAX_FNAME_LEN + 1000];
int prod_ver;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
unsigned char wnd_name[KP_MAX_FNAME_LEN + 1];
unsigned char ini_fname[KP_MAX_FNAME_LEN + 1];
unsigned char dat_buf[KP_MAX_FILE_LIN_WDT + 1];
long ll = KP_MAX_FILE_LIN_WDT;

PutLogMessage_("KpStApp::SendCheckUpdateMsg() 1");

// ------------------------ susirenkam duomenis
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc = GetProdVarReg();
   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc = GetIniWndName(wnd_name);
   if(SUCCEEDED(retc)) retc = GetFlashIniFname(ini_fname);
   if(SUCCEEDED(retc)) retc = GetDataDatParStr(dat_buf, False);

// ----------------- atidarom socketą
   KP_NEWO(sock_ptr, KpSocket);

   if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_IP_CMD_URL, False); // "http://127.0.0.1:49494/"
   if(SUCCEEDED(retc)) retc = sock_ptr->Connect(False);

// ------------------ formuojam pranešimą
   if(SUCCEEDED(retc))
   {
      strcpy(out_buf, KPSTIP_CHK_UPDATE_CMD); // "CU="
      strcat(out_buf, prod_name);
      strcat(out_buf, "&");
      strcat(out_buf, KPSTIP_CLOSE_WND_CMD); // "WN="
      strcat(out_buf, wnd_name);
      strcat(out_buf, "&");
      strcat(out_buf, KPSTIP_INI_FNAME_CMD); // "IF="
      strcat(out_buf, ini_fname);
      strcat(out_buf, "&");
      strcat(out_buf, KPST_CHK_UPDATE_CMD); // "PI="
      strcat(out_buf, dat_buf);
      sprintf((char *)out_buf + strlen(out_buf), KPST_CHK_UPDATE_FORMAT, prod_ver, m_ProdVar);
   }

// ---------------- siunčiam
   if(SUCCEEDED(retc))
      retc = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD, // "POST"
            (const unsigned char *)"/", // failo vardas // KPST_IP_CMD_URL, // "http://127.0.0.1:49494/"
            False, strlen(out_buf));
   if(SUCCEEDED(retc)) retc = sock_ptr->SendMsg(out_buf, strlen(out_buf), False);

// --------------- laukiam atsakymo
   if(SUCCEEDED(retc))
   {
      ll = KP_MAX_FILE_LIN_WDT;
      retc = sock_ptr->RcvHttpMsg(out_buf, &ll, False);
      if(retc == KP_E_EOF) retc = S_OK;
      if(SUCCEEDED(retc)) out_buf[ll] = Nul;
   }

   KP_DELETE(sock_ptr);

return(retc);
}
#endif


// -----------------------------------
HRESULT KpStApp::GrpSendDiagMsg(const unsigned char *lpszDiagMsgPars)
{
HRESULT retc = S_OK;
static unsigned char full_log_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char action_buf_tmp[KP_MAX_FILE_LIN_LEN + 1]; // darbinė action_buf_exp kopija sudėtinių dalių skaidymui // ilgesnis dėl m_alpszActions // [KP_MAX_FNAME_LEN + 1];
unsigned char *rest_ptr = NULL;
unsigned char *file_buf = null;
unsigned char *src_ptr = NULL;
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
fstream out_file;
long file_len = 0L;

// -----------------
bool refresh_sav = m_bGrpRefreshFlg;
   m_bGrpRefreshFlg = False;

// -----------------
   KP_ASSERT(lpszDiagMsgPars != null, E_INVALIDARG, null, True);

// ------------ log failų vardai
   if(SUCCEEDED(retc)) retc = GetLogFileName(full_log_fname);

// ------------ skanuojam parametrus - prijungiam papildomus logus
   KP_ASSERT(strlen(lpszDiagMsgPars) <= KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(action_buf_tmp, lpszDiagMsgPars);
      rest_ptr = action_buf_tmp;
   }

   if(SUCCEEDED(retc))
   {
static unsigned char *str_buf = null;
      KP_NEWA(str_buf, unsigned char, /* KP_MAX_FNAME_LEN + 100 */ 10000);

      do
      {
// ------- analizuojam komandos parametrų grupes (skirtukai ';')
         if(SUCCEEDED(retc))
         {
            src_ptr = rest_ptr;

            rest_ptr = strchr(rest_ptr, ';');
            if(rest_ptr) *rest_ptr++ = Nul;
         }

         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            KP_ASSERT(strlen(src_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc))
            {
               strncpy(fname, src_ptr, KP_MAX_FNAME_LEN);
               fname[KP_MAX_FNAME_LEN] = Nul;
            }

// -------------------------------------- prikabinam nurodytą failą prie logo
            if(SUCCEEDED(retc))
            {
               out_file.open((const char *)full_log_fname, ios_base::out | ios_base::app);
               KP_ASSERTE(!out_file.fail(), KP_E_DIR_ERROR, full_log_fname, True);

               if(SUCCEEDED(retc))
               {
                  sprintf((char *)str_buf, "------------------ >>> %s\n", fname); PutEncodedLogMsg(str_buf, &out_file);

#ifndef ENCODE_LOG
                  if(strstr(fname, KP_XFS_LOG_FNAME) != null)
                     retc = DecodeXfsLog(fname, &out_file, False);
                  else
#endif
                  {
                     if(IsPlainTextFile(fname))
                     {
                        if(SUCCEEDED(retc)) retc = ReadFileContents(fname, &file_buf, &file_len, False, False);
#ifdef ENCODE_LOG
                        if((strstr(fname, ".log") == null) && SUCCEEDED(retc)) retc = EncodeLogBuf(file_buf, file_len);
#endif
                        if(SUCCEEDED(retc)) out_file.write((const char *)file_buf, file_len);
                        KP_DELETEA(file_buf);
                     }
                     else retc = EncodeLogBase64(fname, &out_file);
                  }

                  sprintf((char *)str_buf, "------------------ <<< %s\n", fname); PutEncodedLogMsg(str_buf, &out_file);

//                KP_ASSERT(!out_file.fail(), KP_E_FERROR, full_log_fname, True);

               } // if(SUCCEEDED(retc))

//             if(SUCCEEDED(retc))
               {
                  out_file.close();
                  KP_ASSERT(!out_file.fail(), KP_E_FERROR, full_log_fname, True);
               }

               if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;

            } // if(SUCCEEDED(retc))

         } // if(SUCCEEDED(retc)) if(src_ptr[0])

      } while(rest_ptr && SUCCEEDED(retc));

      KP_DELETEA(str_buf);
   }

// --------------------- diag. pranešimas
#ifdef KP_ERR_SENDDIAGMSG
   KP_ERROR(KP_S_DIAG_MSG, null);
#else
   KP_ERROR(E_NOTIMPL, null);
#endif
   KpErrorProc.lhLastRetc = S_OK; // numušam apsaugą nuo pasikartojimo – kad būtų galima siųsti pakartotinai

// -----------------------
   m_bGrpRefreshFlg = (m_bGrpRefreshGlobalFlg?refresh_sav:False);

return(retc);
}
