echo off
set BIN=..\gdbk-n\bin
set OBJ=obj

if "%1"=="clean" (
	if exist %OBJ% rd /s/q %OBJ%
	if exist print.gb del print.gb
	goto end
)

if not exist %OBJ% mkdir %OBJ%
call %BIN%\gbdk-n-compile.bat print.c -o %OBJ%\print.rel
call %BIN%\gbdk-n-link.bat %OBJ%\print.rel -o %OBJ%\print.ihx
call %BIN%\gbdk-n-make-rom.bat %OBJ%\print.ihx print.gb

:end
