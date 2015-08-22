// -----------------------------------------
// kpmsg_en.h
// programos paleidimo aplikaciju pranesimai
// anglø kalba
//

#ifndef kpmsg_en_included
#define kpmsg_en_included

// --------------------------------------- common kp messages

#if TRUE // ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#define KP_MSG_TITLE_EN             ((const unsigned char *)"Message")
#define KP_INPUT_TITLE_EN           ((const unsigned char *)"Input")

#define KP_MSG_YES_EN               ((const unsigned char *)"Yes")
#define KP_MSG_TAIP_EN              KP_MSG_YES_EN
#define KP_MSG_NO_EN                ((const unsigned char *)"No")
#define KP_MSG_NE_EN                KP_MSG_NO_EN
#define KP_MSG_OK_EN                ((const unsigned char *)"OK")
#define KP_MSG_GERAI_EN             KP_MSG_OK_EN
#define KP_MSG_CANCEL_EN            ((const unsigned char *)"Cancel")
#define KP_MSG_ATSAUKTI_EN          KP_MSG_CANCEL_EN
#define KP_MSG_TESTI_EN             ((const unsigned char *)"Continue")
#define KP_MSG_BAIGTI_EN            ((const unsigned char *)"Finish")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_EN ((const unsigned char *)"Forgot password")

#define KP_MSG_ERROR_EN             ((const unsigned char *)"Error")
#define KP_MSG_WARNING_EN           ((const unsigned char *)"Warning")
#define KP_MSG_FILE_LINE_EN         ((const unsigned char *)", error: %lx, file: %s, line: %d")
#define KP_MSG_ENTRY_ID_EN          ((const unsigned char *)", Entry Id:%ld")
#define KP_MSG_ENTRY_EN             ((const unsigned char *)", Entry: %s")

#define KP_MSG_NO_STANDARD_PROG_EN  ((const unsigned char *)"Standard program not set to open given file type")
#define KP_MSG_WND_NOT_FOUND_EN     ((const unsigned char *)"Window not found")
#define KP_MSG_PID_NOT_FOUND_EN     ((const unsigned char *)"PID not found")
#define KP_MSG_NO_SOCKET_EN         ((const unsigned char *)"Socket not created yet")
#define KP_MSG_SOCK_UNRESOLVED_EN   ((const unsigned char *)"Server address not resolved yet")

#define KP_MSG_ERR_OK_EN            ((const unsigned char *)"Operation ended successfully")
#define KP_MSG_INVALIDARG_EN        ((const unsigned char *)"Invalid parameter")
#define KP_MSG_NOTIMPL_EN           ((const unsigned char *)"Feature not implemented yet")
#define KP_MSG_UNEXPECTED_EN        ((const unsigned char *)"Unexpected interface call") // Interface call result: Unexpected error
#define KP_MSG_FERROR_EN            ((const unsigned char *)"File I/O error")
#define KP_MSG_SYSTEM_ERROR_EN      ((const unsigned char *)"Internal error")
#define KP_MSG_EOF_EN               ((const unsigned char *)"Unexpected end of input file")
#define KP_MSG_FILE_FORMAT_EN       ((const unsigned char *)"Unexpected input file format")
#define KP_MSG_FILE_NOT_FOUND_EN    ((const unsigned char *)"File not found")
#define KP_MSG_DIR_ERROR_EN         ((const unsigned char *)"Unable to create file")
#define KP_MSG_OUTOFMEM_EN          ((const unsigned char *)"Out of memory")
#define KP_MSG_NO_FILE_EN           ((const unsigned char *)"No file open")
#define KP_MSG_DOUBLE_UNGET_EN      ((const unsigned char *)"Double unget")
#define KP_MSG_UNKN_CHR_EN          ((const unsigned char *)"Unknown character")
#define KP_MSG_COMMAND_ERROR_EN     ((const unsigned char *)"External error")
#define KP_MSG_BUFFER_OVERFLOW_EN   ((const unsigned char *)"Buffer overflow")
#define KP_MSG_FONT_UNDEF_EN        ((const unsigned char *)"Font undefined")
#define KP_MSG_KWD_NOT_FOUND_EN     ((const unsigned char *)"Keyword not found")
#define KP_MSG_UNKNOWN_SYSTEM_EN    ((const unsigned char *)"Unknown OS version")
// #define KP_MSG_ILL_CODE_EN          ((const unsigned char *)"Illegal registration code")
#define KP_MSG_ILL_CODE_EN          ((const unsigned char *)"Illegal activation code")
#define KP_MSG_CANCELLED_EN         ((const unsigned char *)"Job cancelled")
#define KP_MSG_DOUBLE_CALL_EN       ((const unsigned char *)"Double call")
#define KP_MSG_TIMEOUT_EN           ((const unsigned char *)"Timeout")
#define KP_MSG_OBJ_NOT_FOUND_EN     ((const unsigned char *)"Object not found")
#define KP_MSG_NO_CONN_EN           ((const unsigned char *)"No connection")

#define KP_MSG_TRANS_ERR_EN         ((const unsigned char *)"Transfer error")
#define KP_MSG_TRANS_ERR_1_EN       ((const unsigned char *)"Transfer error, repeat the download procedure, please")

// #define KP_MSG_REFUSED_EN           ((const unsigned char *)"Registration refused")
#define KP_MSG_REFUSED_EN           ((const unsigned char *)"Activation refused")
#define KP_MSG_ACCESS_DENIED_EN     ((const unsigned char *)"Access denied")
#define KP_MSG_ILLEGAL_CHARACTER_EN ((const unsigned char *)"Unexpected character")
#define KP_MSG_DIV_ZERO_EN          ((const unsigned char *)"Division by zero")
#define KP_MSG_ILLMATHARG_EN        ((const unsigned char *)"Illegal math argument")
#define KP_MSG_ILLFUNC_EN           ((const unsigned char *)"Illegal function call")
                                    
// #define KP_MSG_NOTINST_EN        ((const unsigned char *)"Program not yet installed or installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_EN           ((const unsigned char *)"Product not yet installed or its installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_S_EN         ((const unsigned char *)"Product “%s” not yet installed or its installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_DELETE_EN    ((const unsigned char *)"Product not yet installed or its installation is damaged. Delete the product and repeat the installation procedure again, please.")

#define KP_MSG_MSG_FORMAT_EN        ((const unsigned char *)"Illegal message format")
#define KP_MSG_OBSOLETE_EN          ((const unsigned char *)"Obsolete function call")

// #define KP_MSG_ERROR_HELP_EN     ((const unsigned char *)".  Technical support by e-mail tech@tev.lt   For further information look file %s")
#define KP_MSG_ERROR_HELP_EN        ((const unsigned char *)".  Ask for technical support by e-mail at address pagalba@tev.lt")
#define KP_MSG_ERROR_HELP_REST_EN   ((const unsigned char *)"   Attach file %s from your desktop to the message.")

#define KP_MSG_WSAEACCES_EN         ((const unsigned char *)"Permission denied")
#define KP_MSG_WSAEADDRINUSE_EN     ((const unsigned char *)"Address already in use")
#define KP_MSG_WSAEADDRNOTAVAIL_EN  ((const unsigned char *)"Cannot assign requested address")
#define KP_MSG_WSAEAFNOSUPPORT_EN   ((const unsigned char *)"Address family not supported by protocol family")
#define KP_MSG_WSAEALREADY_EN       ((const unsigned char *)"Operation already in progress")
#define KP_MSG_WSAECONNABORTED_EN   ((const unsigned char *)"Software caused connection abort")
#define KP_MSG_WSAECONNREFUSED_EN   ((const unsigned char *)"Connection refused")
#define KP_MSG_WSAECONNRESET_EN     ((const unsigned char *)"Connection reset by peer")
#define KP_MSG_WSAEDESTADDRREQ_EN   ((const unsigned char *)"Destination address required")
#define KP_MSG_WSAEFAULT_EN         ((const unsigned char *)"Bad address")
#define KP_MSG_WSAEHOSTDOWN_EN      ((const unsigned char *)"Host is down")
#define KP_MSG_WSAEHOSTUNREACH_EN   ((const unsigned char *)"No route to host")
#define KP_MSG_WSAEINPROGRESS_EN    ((const unsigned char *)"Operation now in progress")
#define KP_MSG_WSAEINTR_EN          ((const unsigned char *)"Interrupted function call")
#define KP_MSG_WSAEINVAL_EN         ((const unsigned char *)"Invalid argument")
#define KP_MSG_WSAEISCONN_EN        ((const unsigned char *)"Socket is already connected")
#define KP_MSG_WSAEMFILE_EN         ((const unsigned char *)"Too many open files")
#define KP_MSG_WSAEMSGSIZE_EN       ((const unsigned char *)"Message too long")
#define KP_MSG_WSAENETDOWN_EN       ((const unsigned char *)"Network is down")
#define KP_MSG_WSAENETRESET_EN      ((const unsigned char *)"Network dropped connection on reset")
#define KP_MSG_WSAENETUNREACH_EN    ((const unsigned char *)"Network is unreachable")
#define KP_MSG_WSAENOBUFS_EN        ((const unsigned char *)"No buffer space available")
#define KP_MSG_WSAENOPROTOOPT_EN    ((const unsigned char *)"Bad protocol option")
#define KP_MSG_WSAENOTCONN_EN       ((const unsigned char *)"Socket is not connected")
#define KP_MSG_WSAENOTSOCK_EN       ((const unsigned char *)"Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_EN     ((const unsigned char *)"Operation not supported")
#define KP_MSG_WSAEPFNOSUPPORT_EN   ((const unsigned char *)"Protocol family not supported")
#define KP_MSG_WSAEPROCLIM_EN             ((const unsigned char *)"Too many processes")
#define KP_MSG_WSAEPROTONOSUPPORT_EN      ((const unsigned char *)"Protocol not supported")
#define KP_MSG_WSAEPROTOTYPE_EN           ((const unsigned char *)"Protocol wrong type for socket")
#define KP_MSG_WSAESHUTDOWN_EN            ((const unsigned char *)"Cannot send after socket shutdown")
#define KP_MSG_WSAESOCKTNOSUPPORT_EN      ((const unsigned char *)"Socket type not supported")
#define KP_MSG_WSAETIMEDOUT_EN            ((const unsigned char *)"Connection timed out")
#define KP_MSG_WSATYPE_NOT_FOUND_EN       ((const unsigned char *)"Class type not found")
#define KP_MSG_WSAEWOULDBLOCK_EN          ((const unsigned char *)"Resource temporarily unavailable")
#define KP_MSG_WSAHOST_NOT_FOUND_EN       ((const unsigned char *)"Host not found")
#define KP_MSG_WSA_INVALID_HANDLE_EN      ((const unsigned char *)"Specified event object handle is invalid")
#define KP_MSG_WSA_INVALID_PARAMETER_EN   ((const unsigned char *)"One or more parameters are invalid")
#define KP_MSG_WSAINVALIDPROCTABLE_EN     ((const unsigned char *)"Invalid procedure table from service provider")
#define KP_MSG_WSAINVALIDPROVIDER_EN      ((const unsigned char *)"Invalid service provider version number")
#define KP_MSG_WSA_IO_INCOMPLETE_EN       ((const unsigned char *)"Overlapped I/O event object not in signaled state")
#define KP_MSG_WSA_IO_PENDING_EN          ((const unsigned char *)"Overlapped operations will complete later")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_EN   ((const unsigned char *)"Insufficient memory available")
#define KP_MSG_WSANOTINITIALISED_EN       ((const unsigned char *)"Successful WSAStartup not yet performed")
#define KP_MSG_WSANO_DATA_EN              ((const unsigned char *)"Valid name, no data record of requested type")
#define KP_MSG_WSANO_RECOVERY_EN          ((const unsigned char *)"this is a non-recoverable error")
#define KP_MSG_WSAPROVIDERFAILEDINIT_EN   ((const unsigned char *)"Unable to initialize a service provider")
#define KP_MSG_WSASYSCALLFAILURE_EN       ((const unsigned char *)"System call failure")
#define KP_MSG_WSASYSNOTREADY_EN          ((const unsigned char *)"Network subsystem is unavailable")
#define KP_MSG_WSATRY_AGAIN_EN            ((const unsigned char *)"Non-authoritative host not found")
#define KP_MSG_WSAVERNOTSUPPORTED_EN      ((const unsigned char *)"WINSOCK.DLL version out of range")
#define KP_MSG_WSAEDISCON_EN              ((const unsigned char *)"Graceful shutdown in progress")
#define KP_MSG_WSA_OPERATION_ABORTED_EN   ((const unsigned char *)"Overlapped operation aborted")

#define KP_MSG_OUT_OF_MEM_RES_EN          ((const unsigned char *)"The operating system is out of memory or resources")
#define KP_MSG_ERROR_FILE_NOT_FOUND_EN    ((const unsigned char *)"The file specified was not found")
#define KP_MSG_ERROR_PATH_NOT_FOUND_EN    ((const unsigned char *)"The path specified was not found")
#define KP_MSG_ERROR_BAD_FORMAT_EN        ((const unsigned char *)"The .exe file is invalid (non-Win32(r) .exe or error in .exe image)")
#define KP_MSG_SE_ERR_ACCESSDENIED_EN     ((const unsigned char *)"The operating system denied access to the specified file")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_EN  ((const unsigned char *)"The file name association is incomplete or invalid")
#define KP_MSG_SE_ERR_DDEBUSY_EN          ((const unsigned char *)"The DDE transaction could not be completed because other DDE transactions were being processed")
#define KP_MSG_SE_ERR_DDEFAIL_EN          ((const unsigned char *)"The DDE transaction failed")
#define KP_MSG_SE_ERR_DDETIMEOUT_EN       ((const unsigned char *)"The DDE transaction could not be completed because the request timed out")
#define KP_MSG_SE_ERR_DLLNOTFOUND_EN      ((const unsigned char *)"The specified dynamic-link library was not found")
#define KP_MSG_SE_ERR_FNF_EN              ((const unsigned char *)"The specified file was not found")
#define KP_MSG_SE_ERR_NOASSOC_EN          ((const unsigned char *)"There is no application associated with the given file name extension")
#define KP_MSG_SE_ERR_OOM_EN              ((const unsigned char *)"There was not enough memory to complete the operation")
#define KP_MSG_SE_ERR_PNF_EN              ((const unsigned char *)"The specified path was not found")
#define KP_MSG_SE_ERR_SHARE_EN            ((const unsigned char *)"A sharing violation occurred")

#define KP_MSG_FIRST_TIME_ADMIN_EN        ((const unsigned char *)"Starting the program first time administrator\n rights are necessary. Run the program again as privileged user.")
#define KP_MSG_NOW_NOT_ADMIN_EN           KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN_EN               ((const unsigned char *)"Run the program again as ordinary user")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_EN ((const unsigned char *)"Unsuccessfull file copy operation, run the program again as privileged user")

#define KP_PROGRESS_TITLE_EN              ((const unsigned char *)"Wait...")
#define KP_MSG_DELETING_FILE_EN           ((const unsigned char *)"Deleting file %s.%s...")
#define KP_MSG_COPYING_EN                 ((const unsigned char *)"Copying file...")
#define KP_MSG_COPYING_FILE_EN            ((const unsigned char *)"Copying file %s.%s...")
#define KP_MSG_COPYING_DIR_EN             ((const unsigned char *)"Copying folder %s.%s...")

#define KP_MSG_DOWNLOADING_EN             ((const unsigned char *)"Downloading file...")
#define KP_MSG_DOWNLOADING_FILE_EN        ((const unsigned char *)"Downloading file %s.%s...")

#define KP_MSG_NEG_ANSW_EN                ((const unsigned char *)"Negative responce")

#define KP_MSG_UNABLE_TO_EXECUTE_EN       ((const unsigned char *)"Unable to execute command %s - check installed components of the system")

#define KP_MSG_FLASH_PLAYER_INSTALL_EN    ((const unsigned char *)"Macromedia Flash player will be installed. Follow setup instructions.")

#define KP_MSG_FILE_CHANGED_EN            ((const unsigned char *)"File has been changed")

#define KP_MSG_ALL_FILES_EN               ((const unsigned char *)"All files (*.*)") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_EN                 ((const unsigned char *)"Save As") // "Áraðyti kaip"

#define KP_MSG_FILE_EXISTS_EN             ((const unsigned char *)"File %s already exists, overwrite?") // "Failas %s jau yra, perraðyti?"

#define KP_MSG_DIAG_MSG_EN                ((const unsigned char *)"Error report preparation")
#define KP_MSG_DIAG_MSG_TITLE_EN          ((const unsigned char *)"Error report")

#if FALSE
#define KP_MSG_DIAG_MSG_EXPL_EN           ((const unsigned char *)"To send error report to the producer, fill following fields and press " \
                                                                  "button \"Continue\". The message about computer configuration, product " \
                                                                  "and the error will be sent by internet to the server of the product " \
                                                                  "manufacturer. If you will not be contacted in certain period of time, " \
                                                                  "ask for assistance by e-mail pagalba@tev.lt")
#endif
// #define KP_MSG_DIAG_MSG_EXPL_EN        ((const unsigned char *)"In order to send error report to the producer, you could fill following fields.")
#define KP_MSG_DIAG_MSG_EXPL_EN           ((const unsigned char *)"In case you have problems by using this produkt, you can send error report to the producer. Fill in following fields.")
#define KP_MSG_DIAG_MSG_EXPL1_EN          ((const unsigned char *)"If you are agreed to send the error report, click the button “Send”, otherwise – “Cancel”.")
#define KP_MSG_DIAG_MSG_EXPL2_EN          ((const unsigned char *)"In order to send error report to the producer, fill the field with your e-mail address and click the button “Send”.")

#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_EN   ((const unsigned char *)"Your e-mail address:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_EN ((const unsigned char *)"Your comments about circumstances when the error is appearing:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_EN    ((const unsigned char *)"Additional file to send to the producer\n(copy of the display picture, for example):")

#define KP_MSG_BAD_EMAIL_ADDRESS_EN       ((const unsigned char *)"E-mail address incorrect")

#define KP_MSG_DIAG_MSG_SEL_FILE_EN       ((const unsigned char *)"Choose file to send")

#define KP_MSG_DIAG_MSG_SUCCEEDED_EN      ((const unsigned char *)"Error report sent successfully")

#define KP_MSG_SIUSTI_EN                  ((const unsigned char *)"Send")

#define KP_MSG_FIREWALL_EN                ((const unsigned char *)"Access to the internet rejected. Check your firewall settings – try to add %s to the list of programs with allowed internet access.")

#define KP_MSG_POINTER_EN                 ((const unsigned char *)"Bad pointer")

#define KP_MSG_LOG_STARTED_EN             ((const unsigned char *)"Start logging to file %s")
#define KP_MSG_CONS_TITLE_EN              ((const unsigned char *)"%s: Console")

#endif // #if ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef kpmsg_en_included
