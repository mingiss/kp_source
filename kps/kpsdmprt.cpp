// ---------------------------
// kpsdmprt.cpp 
// Partition table dump of disk image file  
//

// ---------------------------------------------------
#include "envir.h"

#include <windows.h>
#include <stdio.h>
#include <iostream.h>
// #include <iostream>
#include <fstream.h>
// #include <fstream>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpstdio.h"

// using namespace std;

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 43);
int SortMode=KP_LNG_ENG;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

// -----------------------------------------
HRESULT TestCompilerSettingsMBR(void)
{
HRESULT retc = S_OK;
MBR_Record mbr;
PartitionEntry pentry;
int ii;

   if((char *)&mbr.m_caCodeArea[0] - (char *)&mbr != 0x0000) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   ii = sizeof(mbr.m_caCodeArea); if(ii != 0x01B8) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   
   if((char *)&mbr.m_iDiskSignature - (char *)&mbr != 0x01B8) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   ii = sizeof(mbr.m_iDiskSignature); if(ii != 0x0004) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

   if((char *)&mbr.m_sNulls - (char *)&mbr != 0x01BC) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   ii = sizeof(mbr.m_sNulls); if(ii != 0x0002) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

   if((char *)&mbr.m_PartTable[0][0] - (char *)&mbr != 0x01BE) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   ii = sizeof(mbr.m_PartTable); if(ii != 0x0010 * 4) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   
      if((char *)&pentry.m_cStatus - (char *)&pentry != 0x0000) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cStatus); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      
      if((char *)&pentry.m_cStartCylinder - (char *)&pentry != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cStartCylinder); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cStartHead - (char *)&pentry != 0x0002) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cStartHead); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cStartSector - (char *)&pentry != 0x0003) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cStartSector); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cPartType - (char *)&pentry != 0x0004) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cPartType); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cLastCylinder - (char *)&pentry != 0x0005) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cLastCylinder); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cLastHead - (char *)&pentry != 0x0006) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cLastHead); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_cLastSector - (char *)&pentry != 0x0007) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_cLastSector); if(ii != 0x0001) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_iStartAbsSector - (char *)&pentry != 0x0008) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_iStartAbsSector); if(ii != 0x0004) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

      if((char *)&pentry.m_iNumOfSectors - (char *)&pentry != 0x000C) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
      ii = sizeof(pentry.m_iNumOfSectors); if(ii != 0x0004) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);

   if((char *)&mbr.m_sPTabSignature - (char *)&mbr != 0x01FE) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   ii = sizeof(mbr.m_sPTabSignature); if(ii != 0x0002) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, "Bad compiler settings", True, __FILE__, __LINE__, 0L);
   
return(retc);
}


// -----------------------------------------
int main(int argc, char **argv)
{
HRESULT retc = S_OK;
MBR_Record mbr;
fstream in_file;
PartitionEntry pentry;
int ii;

   if(SUCCEEDED(retc)) retc = KpInit();

   if(SUCCEEDED(retc)) retc = TestCompilerSettingsMBR();

   if((argc<1) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc))
   {
      in_file.open(argv[1], ios_base::in | ios_base::binary);
      if(in_file.fail()) // if(in_file.bad())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, argv[1], True, __FILE__, __LINE__, 0L);
   
      if(SUCCEEDED(retc))
      {
         in_file.read((char *)&mbr, sizeof(mbr));
         if(in_file.fail())         
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, argv[1], True, __FILE__, __LINE__, 0L);
         if(in_file.eof() && SUCCEEDED(retc))         
            retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, argv[1], True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            cout << "==========================" << endl;
            
//          cout << setw(15) << "DiskSignature:" << setw(10) << "" << setw(10) << hex << mbr.m_iDiskSignature << endl;
            cout.width(15);
            cout << "DiskSignature:";
            cout.width(10);
            cout << "";
            cout.width(10);
            cout << hex << mbr.m_iDiskSignature;
            cout << endl;
             
            cout.width(15);
            cout << "Nulls:";
            cout.width(10);
            cout << "";
            cout.width(10);
            cout << hex << mbr.m_sNulls;
            cout << endl;

            cout << endl; 

            for(ii=0; ii<4; ii++)
            {
               cout << "-------------------------" << endl;

               memcpy(&pentry, mbr.m_PartTable[ii], sizeof(PartitionEntry));            
               cout << "Partition " << dec << ii << ":" << endl; 

               cout.width(15);
               cout << "Status:";
               cout.width(10);
               cout << "";
               cout.width(10);
               cout << hex << (int)pentry.m_cStatus;
               cout << " "; 
               cout << ((pentry.m_cStatus == 0x00)?"non-bootable ":"")
                    << ((pentry.m_cStatus == 0x80)?"bootable ":"");
               cout << endl; 


               cout.width(15);
               cout << "StartCylinder:";
               cout.width(10);
               cout << dec << (int)pentry.m_cStartCylinder;  
               cout.width(10);
               cout << hex << (int)pentry.m_cStartCylinder;  
               cout << endl;
                   
               cout.width(15);
               cout << "StartHead:";
               cout.width(10);
               cout << dec << (int)pentry.m_cStartHead;
               cout.width(10);
               cout << hex << (int)pentry.m_cStartHead;      
               cout << endl;
                   
               cout.width(15);
               cout << "StartSector:";
               cout.width(10);
               cout << dec << (int)pentry.m_cStartSector;    
               cout.width(10);
               cout << hex << (int)pentry.m_cStartSector;    
               cout << endl; 


               cout.width(15);
               cout << "PartType:";
               cout.width(10);
               cout << "";
               cout.width(10);
               cout  << hex << (int)pentry.m_cPartType;
               cout << " ";
               cout << lpszaPartTypeNames[pentry.m_cPartType]; 
               cout << endl; 


               cout.width(15);
               cout << "LastCylinder:";
               cout.width(10);
               cout << dec << (int)pentry.m_cLastCylinder;  
               cout.width(10);
               cout << hex << (int)pentry.m_cLastCylinder;  
               cout << endl;
                   
               cout.width(15);
               cout << "LastHead:";
               cout.width(10);
               cout << dec << (int)pentry.m_cLastHead;      
               cout.width(10);
               cout << hex << (int)pentry.m_cLastHead;      
               cout << endl;
                   
               cout.width(15);
               cout << "LastSector:";
               cout.width(10);
               cout << dec << (int)pentry.m_cLastSector;    
               cout.width(10);
               cout << hex << (int)pentry.m_cLastSector;    
               cout << endl; 


               cout.width(15);
               cout << "StartAbsSector:";
               cout.width(10);
               cout << dec << pentry.m_iStartAbsSector;
               cout.width(10);
               cout << hex << pentry.m_iStartAbsSector;
               cout.width(10);
               cout << hex << pentry.m_iStartAbsSector * 512;
               cout << endl;
                
               cout.width(15);
               cout << "NumOfSectors:";
               cout.width(10);
               cout << dec << pentry.m_iNumOfSectors;   
               cout.width(10);
               cout << hex << pentry.m_iNumOfSectors;   
               cout.width(10);
               cout << hex << pentry.m_iNumOfSectors * 512;   
               cout << endl;
               
               cout << endl; 
            }
            
            cout << "-------------------------" << endl;
            cout.width(15);
            cout << "PTabSignature:";
            cout.width(10);
            cout << "" << hex << mbr.m_sPTabSignature << endl;
           
         } // if(SUCCEEDED(retc)) // if(!in_file.fail())

         in_file.close();
         
      } // if(SUCCEEDED(retc)) // if(!in_file.bad())

   } // if(SUCCEEDED(retc))

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_MAIN(retc));
}
