# build.ps1 - PowerShell script to compile the Zephyr application
# This script sets up the local environment and triggers west build.

# 1. Define Paths (Adjust if paths change)
$VENV_DIR = "C:\Users\kerem\Documents\Zephyr\zephyr-env"
$ZEPHYR_DIR = "C:\Users\kerem\Documents\Zephyr\zephyrproject\zephyr"
$BOARD_DIR = "C:\Users\kerem\Documents\Zephyr\st.win.box"
$COMPILER_DIR = "C:\ST\STM32CubeIDE_1.19.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.win32_1.0.0.202411081344\tools"

# 2. Configure environment variables for Zephyr
$env:ZEPHYR_BASE = $ZEPHYR_DIR
$env:ZEPHYR_TOOLCHAIN_VARIANT = "gnuarmemb"
$env:GNUARMEMB_TOOLCHAIN_PATH = $COMPILER_DIR

# 3. Add virtual environment Scripts folder to PATH
$env:PATH = "$VENV_DIR\Scripts;" + $env:PATH

# 4. Check if tools are working
Write-Host "--- Verifying Build Tools ---"
west --version
cmake --version
ninja --version
Write-Host "-----------------------------"

# 5. Execute west build
# We build for board "steval_stwinbx1" (which is built into Zephyr!)
Write-Host "Starting west build..."
west build -b steval_stwinbx1
