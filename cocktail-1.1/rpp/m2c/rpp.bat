@echo off
if not "%3"=="" goto threeargs
   go32 %lib%\rpp\rpp %lib%\rpp\scanner.tab < %1 > %2
   goto end
:threeargs
   go32 %lib%\rpp\rpp %lib%\rpp\scanner.tab %1 < %2 > %3
:end
