@echo off
if not "%3"=="" goto threeargs
   go32 %lib%\y2l\y2l < %1 > %2
   goto end
:threeargs
   go32 %lib%\y2l\y2l %1 < %2 > %3
:end
