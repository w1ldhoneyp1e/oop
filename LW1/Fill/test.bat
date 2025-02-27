@echo off

set PROGRAM="%~1"

call :RunTest 1 "test-data\input1.txt" "test-data\output1.txt" "Simple fill inside borders" 0
call :RunTest 2 "test-data\input2.txt" "test-data\output2.txt" "Fill leaking outside" 0
call :RunTest 3 "test-data\input3.txt" "test-data\output3.txt" "Multiple start points" 0
call :RunTest 4 "test-data\input4.txt" "test-data\output4.txt" "Empty" 0
call :RunTest 5 "test-data\input5.txt" "test-data\output5.txt" "Two start points" 0

call :RunTest 6 "test-data\nonexistent.txt" "test-data\error.txt" "Nonexistent file" 1
call :RunTest 7 "test-data\empty.txt" "test-data\empty.txt" "Empty file" 0
call :RunTest 8 "test-data\input8.txt" "test-data\empty.txt" "Incorrect symbol" 0
call :RunTest 9 "test-data\input9.txt" "test-data\empty.txt" "more than 100 symbols" 0
call :RunTest 10 "test-data\input10.txt" "test-data\output10.txt" "100 symbols" 0
call :RunTest 11 "test-data\input11.txt" "test-data\empty.txt" "more than 100 lines" 0
call :RunTest 12 "test-data\input12.txt" "test-data\output12.txt" "100 lines" 0

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
%PROGRAM% %INPUT% "%TEMP%\output.txt"
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