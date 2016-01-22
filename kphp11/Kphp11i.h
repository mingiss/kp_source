// ------------------------------
// kphp11i.h, former kphp11s.h
// kphp11 sisteminiai apibrezimai vidinems aplikacijoms ir rysiams per kphp11rc
//


#ifndef Kphp11i
#define Kphp11i

// application level

#define HP11_SYSTEM_START              00000000 // power on start address

#define HP11_STACK_PTR                 00001000 // initial stack pointer
#define HP11_IDDLE_LOOP                00001000 // default iddle loop entry point

#define HP11_TT_IN_INT_RTN             00001200 // keyboard interrupt routine
#define HP11_TT_INIT                   00001240 // terminal initialisation routine

#define HP11_RC_INIT                   00001300 // remote call device initialisation routine
#define HP11_RC_INT_RTN                00001400 // remote call interrupt routine, call dispatcher
#define HP11_RC_GET_PARS               00001600 // get RC parameter block
//                                                    [177304, 177302] - remote par. block address
#define HP11_RY_GET_ARR                00001700 // get data from Win32,
//                                                    R3 - num. of 4-byte words, R2 - local address
//                                                    [177314, 177312] - remote address
//                                                    destroys R3, increments R2 and [177314, 177312]


// ------------------- blok of variables 1
#define HP11_RC_PAR_BLK                00002000 // !!! RC parameter block
#define HP11_RC_PAR_BLK_END            00002100
#define HP11_RC_MAX_PAR_BLK_SIZE       (HP11_RC_PAR_BLK_END-HP11_RC_PAR_BLK)
// ---------------------------

// ------------------- static data
#define HP11_RC_DISP_TABLE             00002100 // table of entry points to routines of remote calls
#define HP11_RC_DISP_TABLE_END         00002400 // RC dispatcher table end
// ---------------------------

#define HP11_RC_ENCT_RTN               00002400 // RC KP_RC_ENCT remote memory block encryption routine
                                                //    parameter block in HP11_RC_PAR_BLK
                                                //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)
#define HP11_RND                       00002700 // get random number, R0 - previous chain member, 0 - first
                                                //     returns R0 - next random chain member
#define HP11_RC_RND                    00003000 // RC KP_RC_RAND remote call to HP11_RND,
                                                //    input value HP11_RC_PAR_BLK+010
                                                //    output value to remote RC par. block,
                                                //    address in [177304, 177302]
                                    // 00003200 // empty
#define HP11_RY_GET_PAR_ARR            00003400 // get data from Win32, length and adress from
                                                //    RC par. block at HP11_RC_PAR_BLK+010,
                                                //    destination in R2, increments R2
#define HP11_RY_LOCAL_BUFFER           00003600 // common local buffer for receiving of remote Win32 data
#define HP11_RY_LOCAL_BUFFER_END       00004000 // end address of HP11_RY_LOCAL_BUFFER

#define HP11_RY_PUT_ANSW               00004000 // put answer from R0 to Win32, par. block address in [177304, 177302]

#define HP11_RC_KEY_CHECK              00004200 // obsolete RC KP_RC_KEY_CHECK remote check of installation key

#define HP11_RC_KEY_CHECK_1            00004600 // obsolete RC KP_RC_KEY_CHECK remote check of installation key

#define HP11_RC_REC_INI                00005200 // KP_RC_REC_INI transfer .ini file data Win32 --> HP11

#define HP11_RC_GET_INI_ELEM           00005300 // KP_RC_GET_INI_ELEM handler - get element of .ini file data HP11 --> Win32

#define HP11_ENC_INI_BUF               00005400 // toggles encoding of HP11_RC_INI_BUF

#define HP11_RC_SET_INI_ELEM           00005500 // KP_RC_SET_INI_ELEM handler - set element of .ini file data Win32 --> HP11

#define HP11_RC_SEND_INI               00005600 // KP_RC_SEND_INI transfer .ini file data HP11 --> Win32

#define HP11_RY_SEND_PAR_ARR           00005700 // send data to Win32, length and adress from
                                                //    RC par. block at HP11_RC_PAR_BLK+010,
                                                //    source in R2, increments R2

#define HP11_INI_ELEM_BUF              00006000 // buffer for receiving of .ini data element for HP11_RC_SET_INI_ELEM
#define HP11_INI_ELEM_BUF_END          00007000 // HP11_INI_ELEM_BUF end
#define HP11_INI_ELEM_BUF_LEN (HP11_INI_ELEM_BUF_END-HP11_INI_ELEM_BUF)

#define HP11_ENC_BUF                   00007000 // encodes local buffer: R2 start 2-byte word address, R3 - num of bytes
                                                // destroys R3, increments R2, rounds length to upper multiple of 2

#define HP11_RY_SEND_ARR               00007100 // send data to Win32,
//                                                    R3 - num. of 4-byte words, R2 - local address
//                                                    [177314, 177312] - remote address
//                                                    destroys R3, increments R2 and [177314, 177312]

#define KP_RC_ENCODE_ENTRY_RTN         00007200 // RC KP_RC_ENCODE_ENTRY remote dictionary entry encryption routine
                                                //    parameter block in HP11_RC_PAR_BLK
                                                //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)
// -----------
// block of variables 2
#define KP11_COMPID                    00007300 // KpStApp::m_iCompId
                                   //  00007302 // upper word of KP11_COMPID
#define KP11_PRODVER                   00007304 // decoded value of HP11_RC_INI_BUF.iProdVer
                                   //  00007306 // upper word of KP11_PRODVER
                                                // du zodziai, kad butu maziau problemu kilnojant i int
#define KP11_BLOCK_PROCESSING          00007310 // <>0 - block further secure processing (KP_RC_ENCODE_ENTRY)
                                                // is pradziu <>0, po to kai kurios funkcijos
                                                // (KP_RC_KEY_CHECK, KP_RC_KEY_CHECK_INTERN, CheckRequest()) sekmes atveju isvalo
                                   //  00007312 // upper word of KP11_BLOCK_PROCESSING
#define KP11_LICID                     00007314 // KpStApp::m_iLicID
                                   //  00007316 // upper word of KP11_LICID
#define KP11_LIC_CODE1                 00007320 // KpStApp::m_iLicCode1
                                   //  00007322 // upper word of KP11_LIC_CODE1
#define KP11_LIC_CODE2                 00007324 // KpStApp::m_iLicCode2
                                   //  00007326 // upper word of KP11_LIC_CODE2
#define KP11_LIC_CODE3                 00007330 // KpStApp::m_iLicCode3
                                   //  00007332 // upper word of KP11_LIC_CODE3

#define KP11_INST_CODE1                00007334 // KpStApp::m_iInstCode1
                                   //  00007336 // upper word of KP11_INST_CODE1
#define KP11_INST_CODE2                00007340 // KpStApp::m_iInstCode2
                                   //  00007342 // upper word of KP11_INST_CODE2
#define KP11_INST_CODE3                00007344 // KpStApp::m_iInstCode3
                                   //  00007346 // upper word of KP11_INST_CODE3
#define KP11_INST_CODE4                00007350 // KpStApp::m_iInstCode4
                                   //  00007352 // upper word of KP11_INST_CODE4

#define KP11_REM_LICID                 00007354 // KpStApp::m_iRemLicID
                                   //  00007356 // upper word of KP11_REM_LICID
#define KP11_REM_PRODVER               00007360 // KpStApp::m_iRemProdVer
                                   //  00007362 // upper word of KP11_REM_PRODVER
#define KP11_REM_SESID                 00007364 // KpStApp::m_iRemSesID
                                   //  00007366 // upper word of KP11_REM_SESID

#define KP11_BLOCK_TERM                00007370 // <>0 - block further secure processing (KP_RC_ENCODE_ENTRY)
                                                // is pradziu <>0, iðvalomas, kai licencija neterminuota ar terminas dar nesibaigë
                                   //  00007372 // upper word of KP11_BLOCK_TERM

// -----------

#define HP11_ENC_REM_ARR               0007400  // encodes remote buffer, R0 - initial seed for HP11_RND
                                                //    parameter block in HP11_RC_PAR_BLK
                                                //    ima domën tik 18 jaunesniøjø KpRcPars.iDataLen bitø, perkoduoja tik (Maxuint + 1) * 4 baitø, galas lieka neperkoduotas

#define KP_RC_ENCODE_ENTRY_AND_CALLBACK_RTN 0007600 // RC KP_RC_ENCODE_ENTRY_AND_CALLBACK event routine
                                                //    parameter block in HP11_RC_PAR_BLK
                                                //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)

#define KP_RC_CALLBACK_RTN             0007610  // RC KP_RC_CALLBACK event routine
                                                //    parameter block in HP11_RC_PAR_BLK

#define KP_RC_CALLBACK_AND_STORE_RETC_RTN 0007700 // KP_RC_CALLBACK_AND_STORE_RETC event routine
                                                //    parameter block in HP11_RC_PAR_BLK

// ---------------------------- .ini buffer
#define HP11_RC_INI_BUF                00010000 // buffer of .ini file data
#define HP11_RC_INI_BUF_END            00030000 // .ini buffer end
#define HP11_RC_INI_BUF_MAX_LEN (HP11_RC_INI_BUF_END-HP11_RC_INI_BUF-1)
// ----------------------------

#define KP_RC_GET_VARIABLE_RTN         00030000 // KP_RC_GET_VARIABLE handler - get variable from local kphp11 memory; HP11 --> Win32
#define KP_RC_SET_VARIABLE_RTN         00030100 // KP_RC_SET_VARIABLE handler - set variable in local kphp11 memory; Win32 --> HP11

#define KP_RC_INIT_LICID_RTN           00030200 // KP_RC_INIT_LICID handler - init KP11_LICID

#define KP_RC_CALC_LIC_CODE_RTN        00030400 // KP_RC_CALC_LIC_CODE handler

#define KP_RC_RECALC_LIC_CODE_RTN      00030500 // KP_RC_RECALC_LIC_CODE handler

#define KP_RC_CALC_INST_CODE_RTN       00030600 // KP_RC_CALC_INST_CODE handler

#define KP_RC_UNPACK_INST_CODE_RTN     00031000 // KP_RC_UNPACK_INST_CODE handler

#define KP_RC_CALC_INST_KEY_RTN        00031100 // KP_RC_CALC_INST_KEY handler
                                                // tesinys END_CALC_INST_KEY

#define KP_RC_CALC_REM_CODE_RTN        00031200 // KP_RC_CALC_REM_CODE handler

#define KP_RC_UNPACK_REM_CODE_RTN      00031400 // KP_RC_UNPACK_REM_CODE handler

#define KP_RC_INC_COMPID_RTN           00031500 // KP_RC_INC_COMPID handler

#define END_CALC_INST_KEY              00031540 // KP_RC_CALC_INST_KEY_RTN pabaiga

#define KP_RC_KEY_CHECK_INTERN_RTN     00031600 // KP_RC_KEY_CHECK_INTERN handler
#define KP_RC_KEY_CHECK_INTERN_RTN_CONTINUE_1  00031610 // KP_RC_KEY_CHECK_INTERN_RTN tesinys grizus is KP_RC_KEY_CHECK_INTERN_RTN_START
#define KP_RC_KEY_CHECK_INTERN_RTN_CONTINUE_2  00031742 // KP_RC_KEY_CHECK_INTERN_RTN pabaiga su KP11_BLOCK_PROCESSING nustatymu
#define KP_RC_KEY_CHECK_INTERN_RTN_END 00031754 // KP_RC_KEY_CHECK_INTERN_RTN pabaiga – teigiamas atsakymas su su KP11_BLOCK_PROCESSING iðvalymu

#define END_UNPACK_INST_CODE           00032000 // KP_RC_UNPACK_INST_CODE_RTN pabaiga

#define KP_RC_KEY_CHECK_INTERN_RTN_START  00032100 // KP_RC_KEY_CHECK_INTERN_RTN pradþia - KpStIniData.bBound tikrinimas

#define KP_RC_GET_INI_ELEM_IF_NOT_STOPPED_RTN 00032200 // KP_RC_GET_INI_ELEM_IF_NOT_STOPPED handler - get element of .ini file data HP11 --> Win32, only if KP11_BLOCK_PROCESSING == 0

#define HP11_RC_NULL_BUF               00032300 // nulinis buferis fiktyviam siuntimui KP_RC_GET_INI_ELEM_IF_NOT_STOPPED_RTN
                                                // buferio dydis - max parametrø bloko elemento ilgis + 1 + 4 =
                                                // max(KP_MAX_FILE_LIN_WDT, KP_MAX_FNAME_LEN, KP_KWD_LEN, KP_MAX_FTYPE_LEN, KPST_TXTCD_CHARS_PER_VAL_TID) + 1 + 4 =
                                                // max(255, 260, 400, 260, 4) + 1 + 4 =
                                                // 405 = 0625
#define HP11_RC_NULL_BUF_END           00033200

#define KP_RC_TUX_DECODE_RTN           00033200 // KP_RC_TUX_DECODE handler

#define KP_RC_TUX_HASH_RTN             00033600 // KP_RC_TUX_HASH handler
#define KP_RC_TUX_HASH_FUN             00033710 // suskaiciuoja hash nuo R0 reiksmes, grazina i R0

#define KP_RC_PUT_ANSW_VAL             00034000 // siuncia atsakyma per RcParBuf.value, is hp11 i Win

#define KP_RC_UNPACK_LIC_RTN           00034100 // KP_RC_UNPACK_LIC handler
#define END_UNPACK_LIC                 00034266 // KP_RC_UNPACK_LIC_RTN pabaiga ir 
                                                // KP_RC_UNPACK_INST_CODE_RTN pabaiga (END_UNPACK_INST_CODE tæsinys)

#define KP_RC_RID_ELEM_BUF             00034330 // ilgis KPST_RID_ELEM_LEN + 1
#define KP_RC_UNPACK_RID_RTN           00034400 // KP_RC_UNPACK_RID handler 

#define KP_RC_NUM_BUF                  00034630 // ilgis MAX_INT_DIGITS + 1
#define KP_RC_PACK_DECIMAL             00034650 // supakuoja deðimtainá skaièiø ið teksto eilutës, adresas R2 (KP_RC_NUM_BUF), null terminated, rezultatas -> R0, inkrementuoja R2 
#define KP_RC_PACK_DECIMAL_LOOP        00034660
#define KP_RC_PACK_DECIMAL_END         00034706

#define HP11_TO_UCASE                  00035000 // verèia á upper case, R2 – null terminated eilutës pradþia, inkrementuoja R2
#define HP11_TO_UCASE_LOOP             00035000
#define HP11_TO_UCASE_CONTINUE         00035026
#define HP11_TO_UCASE_END              00035034

#define KP_RC_SAVE_REST_DAYS_RTN       00035100 // KP_RC_SAVE_REST_DAYS handler
                                                // KpRcPars::enc.pData iðskaido á RestDaysInit ir ChSum, ChSum patikrina, o RestDaysInit áraðo á KP11_REST_DAYS_INIT
                                                // former: apskaièiuoja ir áraðo KP11_REST_DAYS_INIT = KpRcPars::enc.pData ^ KP11_LIC_HIGH  
#define KP_RC_SAVE_REST_DAYS_AND_RC_RTN   00035300 // KP_RC_SAVE_REST_DAYS ir KP_RC_CALLBACK  

#define KP_RC_GET_REST_DAYS_RTN        00035400 // gràþina KP11_REST_DAYS_INIT + ChSum
                                                // former: gràþina KP11_REST_DAYS_INIT ^ KP11_LIC_HIGH á KpRcPars::enc.pData                

#define KP_RC_SAVE_LIC_HIGH_RTN        00035500 // KP_RC_SAVE_LIC_HIGH handler
                                                // atskiria ChSum nuo KpRcPars::enc.pData, patikrina ir áraðo á KP11_LIC_HIGH 

#define CALC_CHSUM_XOR                 00035700 // skaièiuoja XOR-inæ keturbièiø kontrolinæ sumà
                                                // argumentas - R2, sugadina
                                                // keturbiciu skaicius - R0, sugadina
                                                // rezultatas --> R3
                                                
#define KP_RC_GET_LIC_HIGH_RTN         00036000 // iðtraukia KP11_LIC_HIGH ir prilipdo ChSum

#define KP_RC_UNPACK_LIC_TMP_RTN       00036200 // iðtraukia LicID ir ProdVer ið senojo LicCode* 

#define HP11_RC_XRND                   00036400 // RC KP_RC_XRAND remote call to HP11_RND,
                                                //    input value HP11_RC_PAR_BLK+010
                                                //    output value to remote RC par. block,
                                                //    address in [177304, 177302]

#define KP_RC_KEY_CHECK_INTERN_AND_CALLBACK_RTN 00036500 // RC KP_RC_KEY_CHECK_INTERN_AND_CALLBACK remote call entry point

#define KP_RC_ENCODE_PWD_RTN  00036600 // KP_RC_ENCODE_PWD remote call entry point

// --------------------------
// block of variables 3

#define KP11_INST_KEY1                 00040000
                                   //  00040002 // upper word of KP11_INST_KEY1
#define KP11_INST_KEY2                 00040004
                                   //  00040006 // upper word of KP11_INST_KEY2
#define KP11_INST_KEY3                 00040010
                                   //  00040012 // upper word of KP11_INST_KEY3
#define KP11_INST_KEY4                 00040014
                                   //  00040016 // upper word of KP11_INST_KEY4

#define KP11_REM_CODE1                 00040020
                                   //  00040022 // upper word of KP11_REM_CODE1
#define KP11_REM_CODE2                 00040024
                                   //  00040026 // upper word of KP11_REM_CODE2
#define KP11_REM_CODE3                 00040030
                                   //  00040032 // upper word of KP11_REM_CODE3
#define KP11_REM_CODE4                 00040034
                                   //  00040036 // upper word of KP11_REM_CODE4

#define KP11_LIC_HIGH                  00040040 // KpStApp::m_iLicHigh
                                   //  00040042 // upper word of KP11_LIC_HIGH

#define KP11_REST_DAYS_INIT            00040044 // KpStApp::m_iRestDaysInit
                                   //  00040046 // upper word of KP11_REST_DAYS_INIT

#define KP11_REST_MINS                 00040050 // KpStApp::m_lRestMinutes
                                   //  00040052 // upper word of KpStApp::m_lRestMinutes

// --------------------------




//                                     00070000 // ???


// common system part layout

#define HP11_OS_START                  00100000 // common system part start address
#define HP11_OS_ENTRY_POINT            00100000 // EMT interrupt handler entry point
#define HP11_OS_EMT_DISP_TABLE         00101000 // table of EMT entry points
#define HP11_OS_EMT_DISP_TABLE_END     00102000 // EMT dispatcher table end
#define HP11_OS_EMT_351_ENTRY          00102000 // EMT 351 pranesimo isvedimas i konsole, R0 - pranesimo adresas, 0200 - pranesimo pabaiga
#define HP11_OS_EMT_341_ENTRY          00102400 // EMT 341 baito isvedimas i konsole, R0 - baitas
//                                     00103000 // ???
//                                     00103400 // ???

typedef enum
{
   KP_RC_NOP,        // 0  // no operation
   KP_RC_ENCT,       // 1  // encrypt remote memory block; each call changes data status from unencrypted to encrypted and vice versa
                           // KpRcPars.enc.iDataLen will be rounded down to 4 bytes boundary (KpRcPars.enc.iDataLen=(KpRcPars.enc.iDataLen/4)*4)
                           //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)
   KP_RC_RAND,       // 2  // calculate rand() of KpRcPars.value, return back to KpRcPars.value
   KP_RC_KEY_CHECK,  // 3  // KpStApp::TestKey analogas, obsolete
                           // check whether 3..5 words of KpRcPars.enc.pData (installation key) correspond
                           //    to first three words (0..2) (installation code) according to installation key rules
                           //    return value KpRcPars.value == True in case of success
                           //    block further actions (KP_RC_ENCODE_ENTRY) if returned KpRcPars.value == False
   KP_RC_REC_INI,    // 4  // receive buffer with .ini file data (main app --> kphp11) --> HP11_RC_REC_INI
                           // buffer ptr in KpRcPars.enc.pData
                           // KpRcPars.enc.iDataLen must not exceed HP11_RC_INI_BUF_MAX_LEN
                           // KpRcPars.enc.iDataLen will be rounded down to multiple of 4 bytes (KpRcPars.enc.iDataLen=(KpRcPars.enc.iDataLen/4)*4)
   KP_RC_GET_INI_ELEM,
                     // 5  // get .ini file element from HP11_RC_INI_BUF
                           // whole HP11_RC_INI_BUF will be decoded, element extracted and
                           // HP11_RC_INI_BUF encoded again
                           // buffer ptr in KpRcPars.enc.pData, must be longer by 4 bytes than expected data amount
                           // KpRcPars.enc.iDataLen - exact length of data element
                           // KpRcPars.enc.lCtrl - offset of data element from beginning of .ini structure
   KP_RC_SEND_INI,   // 6  // transfer .ini data from kphp11 to Win32 buffer
                           // buffer ptr in KpRcPars.enc.pData
                           // KpRcPars.enc.iDataLen will be rounded down to multiple of 4 bytes (KpRcPars.enc.iDataLen=(KpRcPars.enc.iDataLen/4)*4)
   KP_RC_SET_INI_ELEM,
                     // 7  // set .ini file element in HP11_RC_INI_BUF
                           // whole HP11_RC_INI_BUF will be decoded, element value set and
                           // HP11_RC_INI_BUF encoded again
                           // buffer ptr in KpRcPars.enc.pData
                           // KpRcPars.enc.iDataLen - exact length of data element
                           // KpRcPars.enc.lCtrl - offset of data element from beginning of .ini structure
   KP_RC_ENCODE_ENTRY,
                     // 8  // encode dictionary entry
                           // rand seed = HP11_RC_INI_BUF.iProdVer + HP11_RC_PAR_BLK.enc.lCtrl (entry ID), lCtrl naudojami tik jaunesnieji 16 bitø
                           //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)
   KP_RC_ENCODE_ENTRY_AND_CALLBACK,
                     // 9  // encode dictionary entry (KP_RC_ENCODE_ENTRY) and call function KpHp11ExtFunTab[KpRcPars.enc.iCallBackIx] (KP_RC_CALLBACK)
                           //    iðkvieèia HP11_ENC_REM_ARR (su KpRcPars.iDataLen apribojimø pasekmëm)
   KP_RC_CALLBACK,
                     // 10 // call function KpHp11ExtFunTab[KpRcPars.enc.iCallBackIx]
   KP_RC_CALLBACK_AND_STORE_RETC,
                     // 11 // call function KpHp11ExtFunTab[KpRcPars.enc.iCallBackIx] and
                           // block further actions (KP_RC_ENCODE_ENTRY) if
                           //    returned *(HRESULT *)KpRcPars.enc.pCallBackPars!=S_OK
   KP_RC_GET_VARIABLE,
                     // 12 // get variable value from local kphp11 memory
                           // out: returned value in *KpRcPars.enc.pData
                           // in: buffer ptr in KpRcPars.enc.pData, must be longer by 4 bytes than expected data amount
                           // in: KpRcPars.enc.iDataLen - exact length of data element
                           // in: KpRcPars.enc.lCtrl - address of variable in local kphp11 memory
   KP_RC_SET_VARIABLE,
                     // 13 // set variable value in local kphp11 memory
                           // in: value to set in *KpRcPars.enc.pData
                           // in: buffer ptr in KpRcPars.enc.pData, must be longer by 4 bytes than data amount
                           // in: KpRcPars.enc.iDataLen - exact length of data element
                           // in: KpRcPars.enc.lCtrl - address of variable in local kphp11 memory
   KP_RC_INIT_LICID, // 14 // inicializuoja KP11_LICID, KpStApp::m_iLicID=KpstRand(0);


   KP_RC_UNPACK_LIC, // 15 // KpStApp::UnpackLic() analogas

   KP_RC_CALC_LIC_CODE,
                     // 16 // KpStApp::CalcLicCode() analogas
   KP_RC_RECALC_LIC_CODE,
                     // 17 // KpStApp::ReCalcLicCode() analogas
   KP_RC_CALC_INST_CODE,
                     // 18 // KpStApp::CalcInstCode() analogas
   KP_RC_UNPACK_INST_CODE,
                     // 19 // KpStApp::UnpackInstCode() analogas
   KP_RC_CALC_INST_KEY,
                     // 20 // KpStApp::CalcInstKey() analogas
   KP_RC_CALC_REM_CODE,
                     // 21 // KpStApp::CalcRemoveCode() analogas
   KP_RC_UNPACK_REM_CODE,
                     // 22 // KpStApp::UnpackRemCode() analogas
   KP_RC_INC_COMPID,
                     // 23 // KpStApp::IncCompID() analogas
   KP_RC_KEY_CHECK_INTERN,
                     // 24 // KpStApp::TestKey() analogas, nauja KP_RC_KEY_CHECK versija, grynai kphp11 vidine
                           // check whether KP11_INST_KEY* correspond to KP11_INST_CODE* according to installation key rules
                           //    return value KpRcPars.value == True in case of success
                           //    block further actions (KP_RC_ENCODE_ENTRY) if returned KpRcPars.value == False
   KP_RC_GET_INI_ELEM_IF_NOT_STOPPED,
                     // 25 // like KP_RC_GET_INI_ELEM, but only if KP11_BLOCK_PROCESSING == 0

   KP_RC_TUX_DECODE, // 26 // iðkoduoja tux pdf failo buferá, bet tik jei KP11_BLOCK_PROCESSING == 0
                           // KpRcPars.pData - buferio adresas
                           // KpRcPars.lCtrl - buferio ilgis

   KP_RC_TUX_HASH,   // 27 // skaiciuoja pseudo-32 bitu hasha nuo RcParBuf.value
   
   KP_RC_UNPACK_RID, // 28 // iðtraukia KpStIniData::m_lpszPwd, KpStIniData::m_iProdVer, KP11_INST_CODE* ir KP11_INST_KEY* ið .tev dokumento objekto R/ID
                           // KpRcPars.pData - R/ID elemento reikðmës (teksto eilutë) adresas
                           // KpRcPars.lCtrl - R/ID elemento reikðmës ilgis

   KP_RC_SAVE_REST_DAYS,   
                     // 29 // KpRcPars::enc.pData iðskaido á RestDaysInit ir ChSum, ChSum patikrina, o RestDaysInit áraðo á KP11_REST_DAYS_INIT
                           // former: apskaièiuoja ir áraðo KP11_REST_DAYS_INIT = KpRcPars::enc.pData[0] ^ KP11_LIC_HIGH
                           // in: value to set in *KpRcPars.enc.pData
                           // in: buffer ptr in KpRcPars.enc.pData, must be longer by 4 bytes than data amount
                           // in: KpRcPars.enc.iDataLen - exact length of data element (4)
   
   KP_RC_SAVE_REST_DAYS_AND_RC,  
                     // 30 // KP_RC_SAVE_REST_DAYS ir iðkvieèia KP_RC_CALLBACK
   
   KP_RC_GET_REST_DAYS,    
                     // 31 // gràþina KP11_REST_DAYS_INIT + ChSum
                           // former: gràþina KP11_REST_DAYS_INIT ^ KP11_LIC_HIGH
                           // out: returned value in *KpRcPars.enc.pData
                           // in: buffer ptr in KpRcPars.enc.pData, must be longer by 4 bytes than expected data amount
                           // in: KpRcPars.enc.iDataLen - exact length of data element (4)
                                 
   KP_RC_SAVE_LIC_HIGH,    
                     // 32 // atskiria ChSum nuo KpRcPars::enc.pData, patikrina ir áraðo á KP11_LIC_HIGH
   
   KP_RC_GET_LIC_HIGH,     
                     // 33 // iðtraukia KP11_LIC_HIGH, prilipdo ChSum ir áraðo á KpRcPars::enc.pData 
   
   KP_RC_UNPACK_LIC_TMP,
                     // 34 // kaip KP_RC_UNPACK_LIC, tik negadina KP11_LICID ir KP11_BLOCK_PROCESSING
                           // iðtrauktus LicID ir ProdVer gràþina KpRcPars.value = (LicID << 16) | ProdVer
                           // jei kodas klaidingas, gràþina 0

   KP_RC_XRAND,      // 35 // atvirkðtinë rand() funkcija, ið tikrøjø paciklina rand() 65535 kartus

   KP_RC_KEY_CHECK_INTERN_AND_CALLBACK,
                     // 36 // KpStApp::TestKey() analogas, nauja KP_RC_KEY_CHECK versija, grynai kphp11 vidine
                           // check whether KP11_INST_KEY* correspond to KP11_INST_CODE* according to installation key rules
                           //    return value KpRcPars.value == True in case of success
                           //    block further actions (KP_RC_ENCODE_ENTRY) if returned KpRcPars.value == False
                           //    jei viskas gerai, call function KpHp11ExtFunTab[KpRcPars.enc.iCallBackIx]

   KP_RC_ENCODE_PWD, // 37 // uþkoduoja CryptPwd struktûrà
                           // CryptPwd crypt_pwd;
                           // rc_pars.enc.iDataLen = sizeof(CryptPwd);
                           // rc_pars.enc.pData = &crypt_pwd;
} KpRcOpCodes;

typedef struct // parameter block of remote call to kphp11
{
   int /* KpRcOpCodes */ iOpCode;    //    +00
   int iParBlSize;         //    +04   // sizeof(KpRcPars)
   union
   {
      struct               // in/out for KP_RC_ENCT, in for KP_RC_KEY_CHECK
      {                    // in for KP_RC_REC_INI

         int iDataLen;     //    +010  // amount of bytes in pData
         void *pData;      //    +014  // pointer to data, not necessary alligned to
                                       //    word boundary, but allocated in 4-bytes clusters and
                                       //    not shorter than iDataLen
         long lCtrl;       //    +020  // additional control data
                                       //    .ini structure offset for KP_RC_GET_INI_ELEM/KP_RC_SET_INI_ELEM
                                       //    dict. entry id. for KP_RC_ENCODE_ENTRY
                                       //    m_Ini.m_iCheckSum pradinio seed KP_RC_RAND nustatymui dël KP_RC_ENCT
         int iCallBackIx;  //    +024  // callback function index in KpHp11ExtFunTab[] for KP_RC_ENCODE_ENTRY_AND_CALLBACK
         void *pCallBackPars;//  +030  // callback function parameter (pointer to parameters array) - pPars of KpHp11ExtFun

      } enc;

      int value;           //    +010  // in/out for KP_RC_RAND, KP_RC_TUX_HASH, out for KP_RC_KEY_CHECK
   };

   HRESULT m_iRetc;     // grizimo is KpHp11ExtFunTab[iCallBackIx] kodas

   int iAlignmentField; // unused field for alignment to 4-bytes cluster boundary

} KpRcPars;

typedef enum
{
   KP_RC_CBIX_GetCommonCompID, // =0
   KP_RC_CBIX_TestFlashID,
   KP_RC_CBIX_TestIniChSum,
   KP_RC_CBIX_SetIniChSum,

   KP_RC_CBIX_CheckResRequest,
   KP_RC_CBIX_CheckRelRequest,

   KP_RC_CBIX_InitRestDays,      // pradinis terminuotø licencijø laikø nustatymas 
   KP_RC_CBIX_ResumeRestDays,    // terminuotø licencijø eilinës sesijos inicializavimas – pratæsia iðsaugotà laiko skaièiavimà, ðiaip jau tas pats, kaip ir KP_RC_CBIX_InitRestDays 
   KP_RC_CBIX_ProcessRestDays,   // terminuotø licencijø taimerio procedûra – likusiø minuèiø dekrementavimas ir iðsaugojimas 
   KP_RC_CBIX_ResetRestDays,     // terminuotø licencijø expirinimas per jëgà – po neigiamo atsakymo ið serverio 

   KP_RC_CBIX_RegSert,           // sertifikato registravimas 
   KP_RC_CBIX_UnRegSert,         // sertifikato iðregistravimas 

   KP_RC_CBIX_NumOfCommonIxs

} KpCommonCallBackIxs; // standard callback procedure indexes to KpHp11ExtFunTab[]

#define KP_RC_CBIX_NumOfCommonIxs_8 KP_RC_CBIX_NumOfCommonIxs

extern KpRcPars RcParBuf; // fiktyvus RC parametru buferis poslinkiu skaiciavimui

#define HP11_RC_PAR_BL_SIZ_OFF ((unsigned char *)(&(RcParBuf.iParBlSize))-(unsigned char *)(&RcParBuf))
#define HP11_RC_PAR_DATA_LEN_OFF ((unsigned char *)(&(RcParBuf.enc.iDataLen))-(unsigned char *)(&RcParBuf))
#define HP11_RC_PAR_DATA_OFF ((unsigned char *)(&(RcParBuf.enc.pData))-(unsigned char *)(&RcParBuf))
#define HP11_RC_PAR_CTRL_OFF ((unsigned char *)(&(RcParBuf.enc.lCtrl))-(unsigned char *)(&RcParBuf))
#define HP11_RC_PAR_VALUE_OFF ((unsigned char *)(&(RcParBuf.value))-(unsigned char *)(&RcParBuf))

#endif
