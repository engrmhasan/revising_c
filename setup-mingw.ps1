# Add MinGW to PowerShell PATH permanently

# replace this path with the actual path to your MinGW bin directory
$mingwPath = "C:\ProgramData\mingw64\mingw64\bin"

# Ensure profile exists
if (!(Test-Path $PROFILE)) { New-Item -ItemType File -Path $PROFILE -Force }

# Check if already in profile to avoid duplicates
$profileContent = Get-Content $PROFILE -ErrorAction SilentlyContinue
if ($profileContent -notmatch [regex]::Escape($mingwPath)) {
    Add-Content $PROFILE "`$env:Path += `";$mingwPath`""
    Write-Host "MinGW path added to PowerShell profile."
} else {
    Write-Host "MinGW path already exists in PowerShell profile."
}

# Add to current session immediately
$env:Path += ";$mingwPath"
Write-Host "MinGW path added to current session."

# Test GCC
if (Get-Command gcc -ErrorAction SilentlyContinue) {
    gcc --version
} else {
    Write-Host "gcc not found. Check MinGW installation."
}

# Run with:
# run as administrator:
# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
# .\setup-mingw.ps1
