@echo off

::::::::::::::::::::::::::::::::::::: COLOUR CONSOLE :::::::::::::::::::::::::::::::::::::

rem Get ESC
FOR /F %%a in ('ECHO PROMPT $E^| CMD') do SET "ESC=%%a"

SET "PB=%ESC%["
SET "AF=38;5;"
SET "AB=48;5;"

SET "CLR=%PB%0m"

SET "BOLD=%PB%1m"
SET "UNDL=%PB%4m"
SET "INVT=%PB%7m"

SET "_RED_=%PB%31m"
SET "GREEN=%PB%32m"
SET "YELOW=%PB%33m"
SET "REGAL=%PB%35m"
SET "BROWN=%PB%%AF%88m"

SET "BARSEN=%PB%%AB%234m"

:::::::::::::::::::::::::::::::::::::::::: MAIN ::::::::::::::::::::::::::::::::::::::::::

rem custom clear
SET "ACLR=%CLR%%BARSEN%"

rem preset vars
SET "baum=baum_std"
SET "prog=output\main"

:PLAQUE

ECHO %ACLR%
CLS
ECHO Welcome to %BROWN%%UNDL%Baumeister%ACLR%!
ECHO.
ECHO Choose Your action:%GREEN%
ECHO.	[r] run
ECHO.	[f] fused (comp ^& run)
ECHO.	[c] compile%YELOW%
ECHO.	[e] edit configuration%REGAL%
ECHO.	[h] help
ECHO.	[q] quit
ECHO %ACLR%
ECHO Configuration:%YELOW%
ECHO.	build script = [%ACLR%%baum%%YELOW%];
ECHO.	program = [%ACLR%%prog%%YELOW%]
ECHO.

ECHO | SET "/p=%_RED_%"
CHOICE /c rfcehq /n /m "Your choice:"
SET "ans=%errorlevel%"
ECHO | SET "/p=%CLR%"

IF "%ans%"=="1" (
	CALL :run
) ELSE IF "%ans%"=="2" (
	rem fused
	CALL :compile
	IF NOT ERRORLEVEL 1 (
		CALL :run
	)
) ELSE IF "%ans%"=="3" (
	CALL :compile
) ELSE IF "%ans%"=="4" (
	rem edit
) ELSE IF "%ans%"=="5" (
	rem help
) ELSE IF "%ans%"=="6" (
	GOTO :QUIT
) ELSE IF "%ans%"=="0" (
	rem ctrlC
) ELSE IF "%ans%"=="255" (
	rem err
) 

GOTO PLAQUE

:::::::::::::::::::::::::::::::::::::::::: FUNC ::::::::::::::::::::::::::::::::::::::::::

:screenReset
	ECHO %CLR%
	CLS
goto:eof

::: COMPS :::

:run

	CALL :screenReset

	%prog%
	SET "run_ans=%errorlevel%"
	
	ECHO.
	ECHO Execution ended, program returned %run_ans%.
	PAUSE

goto:eof

:compile

	CALL :screenReset

	CALL %baum%
	SET "compile_ans=%errorlevel%"

	ECHO.
	IF "%compile_ans%"=="1" (
		ECHO Compilation failed; aborting any further scheduled tasks.
	) ELSE (
		ECHO Compilation ended.
	)
	PAUSE
	exit /b %compile_ans%

goto:eof

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:QUIT
CLS

REM possible optimisation todo?
