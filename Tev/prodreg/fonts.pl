#!/usr/bin/perl -w
#

while(<STDIN>)
{
   @file_comps=split /\./;
   @ttf_comps=split /\.ttf/;
   @ttf_up_comps=split /\.TTF/;
   if(defined($file_comps[1]))
   {
      @rest=split /F:\\kp\\source\\Tev\\prodreg\\fonts\\/;
      $_=$rest[1];

      @src_path=split /\n/;
      $_=$src_path[0];

      @dest_path=split /\\/;
      pop @dest_path;

      print("Source: \"fonts\\");
      print($src_path[0]);
      print("\"; DestDir: \"{fonts}\"; FontInstall: \"");
      print(join(" ", @dest_path));
      print("\"; Flags: onlyifdoesntexist uninsneveruninstall");
      if((!defined($ttf_comps[1])) && (!defined($ttf_up_comps[1])))
      {
         print(" fontisnttruetype");
      }
      print(";\n");
   }
}
