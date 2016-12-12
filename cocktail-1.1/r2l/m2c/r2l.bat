@echo off
go32 %lib%\r2l\r2l -l%lib%\r2l < %1 > %2

rem sed -e '
rem s/<>//
rem s/<,/</
rem s/yyStart/BEGIN/g
rem s;yyPrevious;/*** sorry - cannot translate yyPrevious ***/;g
rem s/yyEcho/ECHO/g
rem s/STD/INITIAL/g
rem '
