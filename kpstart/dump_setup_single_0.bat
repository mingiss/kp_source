echo extern unsigned char setup_%2_%3[%5]; > setup_%2_%3.h

echo extern unsigned char setup_%2_%3[%5]={ > setup_%2_%3.cpp
kpsdmp2.exe %1\setup\setup_%2.exe 16 n b c %4 %5>> setup_%2_%3.cpp
echo }; >> setup_%2_%3.cpp
