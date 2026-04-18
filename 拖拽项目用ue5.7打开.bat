@echo off
chcp 65001 >nul

:: UE5.4 路径
set "UE5_PATH=C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe"

:: 检查 UE5.7
if not exist "%UE5_PATH%" (
    echo 未找到 UE5.7: %UE5_PATH%
    pause
    exit /b 1
)

:: 获取拖拽的文件路径
set "PROJECT_PATH=%~1"

:: 如果没有拖拽，提示使用方式
if "%PROJECT_PATH%"=="" (
    echo 请将 .uproject 文件拖拽到此 bat 文件上
    pause
    exit /b 1
)

:: 启动
start "" "%UE5_PATH%" "%PROJECT_PATH%"