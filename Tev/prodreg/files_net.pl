#!/usr/bin/perl -w
#

while(<STDIN>)
{
   @file_comps=split /\./;
   @file_cmap = split /Cmap\\/;
   @file_cmapp = split /CMap\\/;
   @file_acro_vers_dir = split /Reader\\7.0.0/;
   @file_acro_vers_dir_en_US = split /Reader\\7.0.0\\en_US/;
   @file_xipa_acro_pdf_dll = split /xipa.bin.local/;
   @file_tux_ipa_acro_pdf_dll = split /tux_ipa.bin.local/;
   if((defined($file_comps[1]) || defined($file_cmap[1]) || defined($file_cmapp[1])) && ((!defined($file_acro_vers_dir[1])) || (defined($file_acro_vers_dir[1]) && (substr($file_acro_vers_dir[1], 0, 1) eq '\\'))) && ((!defined($file_acro_vers_dir_en_US[1])) || (defined($file_acro_vers_dir_en_US[1]) && (substr($file_acro_vers_dir_en_US[1], 0, 1) eq '\\'))) && ((!defined($file_xipa_acro_pdf_dll[1])) || (defined($file_xipa_acro_pdf_dll[1]) && (substr($file_xipa_acro_pdf_dll[1], 0, 1) eq '\\'))) && ((!defined($file_tux_ipa_acro_pdf_dll[1])) || (defined($file_tux_ipa_acro_pdf_dll[1]) && (substr($file_tux_ipa_acro_pdf_dll[1], 0, 1) eq '\\'))))
   {
      @rest=split /F:\\kp\\source\\Tev\\prodreg\\files_net/;
      $_=$rest[1];

      @src_path=split /\n/;
      $_=$src_path[0];

      @common_files = split /\\CommonFiles/;
      if(defined($common_files[1]) && ($common_files[0] eq "")) { $_ = $common_files[1]; }

      @windows = split /\\Windows/;
      if(defined($windows[1]) && ($windows[0] eq "")) { $_ = $windows[1]; }

      @dest_path=split /\\/;
      pop @dest_path;

      print("Source: \"files_net");
      print($src_path[0]);
      print("\"; DestDir: \"");

      if(defined($common_files[1]) && ($common_files[0] eq "")) { print("{cf}"); }
      else
      {
         if(defined($windows[1]) && ($windows[0] eq "")) { print("{win}"); }
         else { print("{code:GetAppPathStr}"); }
      }

      if($#dest_path>=0)
      {
         print(join("\\", @dest_path));
      }

      print("\"; Flags: ignoreversion overwritereadonly;\n");
   }
}
