@echo off
setlocal

pushd "%~dp0"

call _version.cmd

call _make_readme.cmd

"%WIX%bin\candle.exe" installer-x86.wxs -nologo -out "%TARGETDIR%\x86.wixobj"
"%WIX%bin\light.exe" "%TARGETDIR%\x86.wixobj" -nologo -out "%TARGETDIR%\x86.msi" -sw1056 -sw1076

popd

endlocal
