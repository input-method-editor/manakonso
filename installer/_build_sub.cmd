@echo off
setlocal

pushd "%~dp0"

call _version.cmd

if not exist "%TARGETDIR%" mkdir "%TARGETDIR%"

pushd ..

set DESCRIPTION=���ɓ��v

"%LocalAppData%\Pandoc\pandoc.exe" -s -f markdown_github-ascii_identifiers -t html5 -V lang:"ja" -V title-prefix:"%DESCRIPTION%" -V pagetitle:"�g�p������" -V title:"%DESCRIPTION% �g�p������" --self-contained -c "installer\resource-md\markdown.css" --columns=1024 --toc -o "installer\%TARGETDIR%\README.html" README.md

popd

copy /y /b "..\LICENSE.TXT" "%TARGETDIR%\LICENSE.txt" > nul
copy /y /b "config-share\config.xml" "%TARGETDIR%\config.xml" > nul

pushd "%TARGETDIR%"

copy /b LICENSE.txt + > nul
copy /b config.xml + > nul

popd

popd

endlocal
