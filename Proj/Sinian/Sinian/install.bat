@echo off

:: ���뵽��ǰĿ¼��
cd /d %~dp0

echo "���ƿ��ļ�"
copy "%cd%\..\x64\Release\SINIAN.dll" "%cd%\..\..\bin" /y
copy "%cd%\..\x64\Release\SINIAN.lib" "%cd%\..\..\lib" /y

pause