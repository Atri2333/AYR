set PREMAKE_PATH=vendor\bin\premake\premake5.exe

if not exist "%PREMAKE_PATH%" (
    echo "Premake not found. Please install Premake."
    exit /b 1
)

%PREMAKE_PATH% --file=premake5.lua vs2022
pause
