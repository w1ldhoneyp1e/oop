@echo off

set PROGRAM="%~1"

call :RunTest 1 "16 10 1F" "test1.txt" "From 16 to 10"
call :RunTest 2 "10 2 -42" "test2.txt" "Negative number"
call :RunTest 3 "10 16 2147483647" "test3.txt" "MAX_INT"
call :RunTest 4 "37 10 42" "test4.txt" "Incorrect source" true
call :RunTest 5 "5 37 42" "test5.txt" "Incorrect destination" true
call :RunTest 6 "10 16 2147483648" "test6.txt" "Overflow positiive" true
call :RunTest 7 "10 16 j0" "test7.txt" "Incorrect input" true
call :RunTest 8 "-10 16 20" "test8.txt" "Negative source" true
call :RunTest 9 "10 16 -2147483649" "test9.txt" "Overflow negative" true
call :RunTest 10 "10 16 -2147483648" "test10.txt" "MIN_INT"
call :RunTest 11 "36 16 G2" "test11.txt" "Boundary values"
call :RunTest 12 "2 10 110011" "test12.txt" "Boundary values"

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