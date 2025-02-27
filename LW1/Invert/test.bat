@echo off

set PROGRAM="%~1"

call :RunTest 1 "test-data\matrix1.txt" "test-data\result1.txt" "Default matrix" 0
call :RunTest 2 "test-data\matrix2.txt" "test-data\result2.txt" "Identity matrix" 0
call :RunTest 3 "test-data\matrix3.txt" "test-data\result3.txt" "Degenerate matrix" 0
call :RunTest 4 "test-data\matrix4.txt" "test-data\result4.txt" "Matrix 2x3" 0
call :RunTest 5 "test-data\matrix5.txt" "test-data\result5.txt" "Empty file" 0
call :RunTest 6 "test-data\matrix6.txt" "test-data\result6.txt" "Extra number" 0
call :RunTest 7 "test-data\matrix7.txt" "test-data\result7.txt" "Lack of numbers" 0
echo Test 8: Guide
%PROGRAM% -h > "%TEMP%\output.txt"
if errorlevel 1 (
    echo Test 8 failed
    exit /B 1
)
fc.exe "%TEMP%\output.txt" "test-data\guide-response.txt" >nul
if errorlevel 1 (
    echo Test 8 failed
    exit /B 1
)
echo Test 8 passed

echo All tests completed
exit /B 0

:RunTest
set TEST_NUM=%1
set INPUT=%2
set EXPECTED=%3
set DESCRIPTION=%4
set IS_ERROR=%5

echo Test %TEST_NUM%: %DESCRIPTION%
%PROGRAM% %INPUT% > "%TEMP%\output.txt"

if %IS_ERROR%==1 (
    if not errorlevel 1 (
        echo Test %TEST_NUM% failed
        exit /B 1
    )
) else (
    fc.exe "%TEMP%\output.txt" "%EXPECTED%" >nul
    if errorlevel 1 (
        echo Test %TEST_NUM% failed
        exit /B 1
    )
)

echo Test %TEST_NUM% passed
exit /B 0 