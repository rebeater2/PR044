@echo off

call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" AMD64


call  "\\DESKTOP-G8SJ8BG\D$\Program Files\MATLAB\R2017a\bin\win64\checkMATLABRootForDriveMap.exe" "\\DESKTOP-G8SJ8BG\D$\Program Files\MATLAB\R2017a"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
cd .

if "%1"=="" (nmake  -f music_angle_rtw.mk all) else (nmake  -f music_angle_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
