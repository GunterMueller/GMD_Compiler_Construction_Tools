@echo off
set lalr_args=
set bnf_args=
set use_bnf=false
set in_file=
set bnf_file=\temp\lalr

:loop

if "%1"==""             goto endloop
if not "%1"=="-b"       goto label1
   set use_bnf=true
   shift
   goto loop
:label1
if not "%1"=="-c"       goto label2
   set lalr_args=%lalr_args% %1
   set bnf_args=%bnf_args% %1
   shift
   goto loop
:label2
if not "%1"=="-l"       goto label3
   set lalr_args=%lalr_args% %1
   set bnf_args=%bnf_args% %1
   shift
   goto loop
:label3
if not "%1"=="-m"       goto label4
   set lalr_args=%lalr_args% %1
   set bnf_args=%bnf_args% %1
   shift
   goto loop
:label4
if not "%1"=="-NoAction" goto label5
   set bnf_args=%bnf_args% %1
   shift
   goto loop
:label5
if not "%1"=="-a"       goto label6
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label6
if not "%1"=="-d"       goto label7
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label7
if not "%1"=="-e"       goto label8
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label8
if not "%1"=="-p"       goto label9
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label9
if not "%1"=="-s"       goto label10
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label10
if not "%1"=="-g"       goto label11
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label11
if not "%1"=="-v"       goto label12
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label12
if not "%1"=="-cs"      goto label13
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label13
if not "%1"=="-h"       goto label14
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label14
if exist %1             goto label15
   set lalr_args=%lalr_args% %1
   shift
   goto loop
:label15
   set in_file=%1
   shift
   goto loop

:endloop

if %use_bnf%==false goto lalr
   go32 %lib%\lalr\bnf %in_file% %bnf_args% > %bnf_file%
   if errorlevel 1 goto end
   go32 %lib%\lalr\lalr %bnf_file% %lalr_args%
   del %bnf_file%
   goto end

:lalr
   go32 %lib%\lalr\lalr %in_file% %lalr_args%

:end
set lalr_args=
set bnf_args=
set use_bnf=
set in_file=
set bnf_file=
