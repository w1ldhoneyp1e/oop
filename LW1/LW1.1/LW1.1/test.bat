@echo off
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров проверяем ввод данных
%PROGRAM% > nul
if ERRORLEVEL 1 goto input

rem Test 1: Проверка на замену символа
%PROGRAM% test-data\fox.txt "%TEMP%\bird-cat.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\bird-cat.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

rem Test 3: Проверка на замену символа
%PROGRAM% test-data\fox.txt "%TEMP%\dog-cat.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\dog-cat.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem Test 4: Проверка на замену символа
%PROGRAM% test-data\fox.txt "%TEMP%\replace-a-@.txt" a @
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-a-@.txt" test-data\fox-replace-a-@.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem Test 5: Проверка на пустой поиск
%PROGRAM% test-data\empty-search.txt "%TEMP%\empty-search.txt"
if not ERRORLEVEL 1 goto err
echo Test 5 passed

rem Test 6: Проверка на замену символа
%PROGRAM% test-data\hard-test.txt "%TEMP%\result-for-hard-test.txt" 1231234 some
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\result-for-hard-test.txt" test-data\result-for-hard-test.txt >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

echo OK
exit 0

:input
%PROGRAM% < test-data\input.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\expected-output.txt >nul
if ERRORLEVEL 1 goto err

:err
echo Program testing failed
exit 1