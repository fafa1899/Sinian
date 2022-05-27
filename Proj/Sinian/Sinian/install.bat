@echo off

:: 进入到当前目录下
cd /d %~dp0

echo "复制库文件"
copy "%cd%\..\x64\Release\SINIAN.dll" "%cd%\..\..\bin" /y
copy "%cd%\..\x64\Release\SINIAN.lib" "%cd%\..\..\lib" /y

pause