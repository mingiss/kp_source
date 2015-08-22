// -------------------------------------
// xmle2p.cpp
// converts sgm to plain text
// simply ignoring tags
//

#include <iostream>
#include <fstream>
#include <windows.h>


int main(int /* argc */, char **argv)
{
char ch;
bool inside_tag = FALSE;
bool inside_entity = FALSE;
bool last_char_space = FALSE;
bool last_char_eol = FALSE;
bool control_char = FALSE;
bool first_char = TRUE;

fstream in_file(argv[1], ios::in);
fstream out_file(argv[2], ios::out);

   while(!in_file.eof())
   {
      if(in_file.bad())
      {
         cout << argv[1] << " skaitymo klaida." << endl;
         break;
      }
      if(out_file.bad())
      {
         cout << argv[2] << " raðymo klaida." << endl;
         break;
      }

      in_file.get(ch);
      if(!in_file.eof())
      {
         if(ch == '<') inside_tag = TRUE;
         if(ch == '&') inside_entity = TRUE;
         if(ch == '$') control_char = TRUE;

         if((!inside_tag) && (!inside_entity) && (ch != '$'))
         { 
            if((ch == ' ') || (ch == '\t')) last_char_space = TRUE;
            else if((ch == '\n') || (ch == '\r')) last_char_eol = TRUE;
            else
            {
               if(!first_char)
               {
                  if(last_char_eol) out_file << endl;
                  else if(last_char_space) out_file << ' ';
               }
               
               out_file << (control_char?'?':ch);
               
               first_char = control_char = last_char_space = last_char_eol = FALSE;
            }
         }

         if(inside_entity && (ch == ';'))
         {
            out_file << '?';
            inside_entity = FALSE;
         }
         if(ch == '>') inside_tag = FALSE;
      }
   }

   out_file << endl;

   out_file.close();
   in_file.close();

return(0);
}

