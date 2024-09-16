@echo off
set folder_path="Project\keil\Objects"

REM 检查文件夹是否存在
if exist %folder_path% (
    echo Deleting contents of %folder_path%
    
    REM 删除文件夹中的所有文件和子文件夹
    del /f /q %folder_path%\* >nul 2>&1
    rmdir /s /q %folder_path% >nul 2>&1
    
    REM 重新创建文件夹（如果需要）
    mkdir %folder_path%

    echo Successfully deleted all contents in %folder_path%
) else (
    echo The folder %folder_path% does not exist.
)

