@ECHO off
cmd /k "reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f"
timeout 1 >nul
exit