@echo off

set PROGRAM="%~1"

call :RunTest 1 "16 10 1F" "test1.txt" "From 16 to 10"
call :RunTest 2 "10 2 -42" "test2.txt" "Negative number"
call :RunTest 3 "10 16 2147483647" "test3.txt" "Max int number"
call :RunTest 4 "37 10 42" "test4.txt" "Invalid notation" true
call :RunTest 5 "5 37 42" "test5.txt" "Invalid notation" true
call :RunTest 6 "10 16 2147483648" "test6.txt" "Overflow" true
call :RunTest 7 "10 16 j0" "test7.txt" "Incorrect input" true

echo All tests passed
exit /B 0

:RunTest
set TEST_NUM=%1
set PARAMS=%~2
set EXPECTED=%~3
set DESCRIPTION=%~4
set EXPECT_ERROR=%5

echo Running Test %TEST_NUM%: %DESCRIPTION%
%PROGRAM% %PARAMS% > "%TEMP%\output.txt"

if "%EXPECT_ERROR%"=="true" (
    if not ERRORLEVEL 1 goto :TestFailed
) else (
    if ERRORLEVEL 1 goto :TestFailed
    fc.exe "%TEMP%\output.txt" "test-data\%EXPECTED%" >nul
    if ERRORLEVEL 1 goto :TestFailed
)

echo Test %TEST_NUM% passed
exit /B 0

:TestFailed
echo Test %TEST_NUM% failed
endlocal
exit /B 1