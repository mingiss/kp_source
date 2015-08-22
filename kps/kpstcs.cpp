// -----------------
// kpstcs.cpp
// body of TestCompilerSettings()
//


// ==============================================
// HRESULT TestCompilerSettingsLocal(void)
// HRESULT TestCompilerSettings(void)
{
HRESULT retc=S_OK;
int sl;
int si;
int ss;
int sc;
int st;
enum
{
   first_val,
   secon_val,
   third_val
} test_enum = first_val;
struct
{
   char char_val[1];
   int int_val;
} test_struct;
union
{
   int int_val;
   unsigned char char_vals[4];
} endian_test;

// ---------------------- int = long = 4 bytes?
   sl=sizeof(long);
   si=sizeof(int);
   ss=sizeof(short);
   sc=sizeof(char);
   if(
      ((sl!=4) || (si!=4) || (ss!=2) || (sc!=1)) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (unsigned char const*) "Bad size of integer types", True, __FILE__, __LINE__, 0L, NULL);
      
// ---------------------- enum size
   st=sizeof(test_enum);
   if((st!=4) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (unsigned char const*) "Bad enum size", TRUE, __FILE__, __LINE__, 0L);

// ---------------------- struct allocation
   if(SUCCEEDED(retc))
      if((sizeof(test_struct)!=8) || (((long)test_struct.char_val % 4)!=0L) || 
         ((long)&test_struct.int_val-(long)test_struct.char_val!=4))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (unsigned char const*) "Bad structure alignment", TRUE, __FILE__, __LINE__, 0L);


// ---------------------- endian test
   if(SUCCEEDED(retc))
   {
      endian_test.char_vals[0]=0x01;
      endian_test.char_vals[1]=0x02;
      endian_test.char_vals[2]=0x03;
      endian_test.char_vals[3]=0x04;
      if(endian_test.int_val!=0x04030201)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (unsigned char const*) "Big endian", TRUE, __FILE__, __LINE__, 0L);
   }
   
#if FALSE // CompilerGr!=Msvc
char ch1 = '\x7F';
char ch2 = '\x80';
   if((ch1 > ch2) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (unsigned char const*) "signed char", TRUE, __FILE__, __LINE__, 0L);
#endif

return(retc);
}
