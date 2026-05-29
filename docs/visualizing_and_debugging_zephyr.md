# 🔍 Visualizing and Debugging Zephyr RTOS

If you are coming from **STM32CubeIDE**, command-line tools can feel like working in a dark room. 

This guide explains how to bring back **100% visual clarity** to your development. You will learn how to edit code with autocomplete inside **VS Code**, step through your code line-by-line with **breakpoints**, and even use **STM32CubeIDE**'s graphical debugger to analyze your Zephyr firmware!

---

## 💻 1. The Visual Editor: VS Code Setup

To get a beautiful visual source tree, autocomplete, and error highlighting, open your repository folder `C:\Users\kerem\Documents\Zephyr\Zephyr_2go` in **VS Code (Visual Studio Code)**.

### Recommended Extensions:
Open the Extensions tab (`Ctrl+Shift+X`) in VS Code and install:
1. **C/C++** (by Microsoft) — Provides autocomplete, syntax highlighting, and code navigation.
2. **Cortex-Debug** (by marus25) — Provides the step-by-step graphical debugger interface for ARM Cortex-M microcontrollers.
3. **DeviceTree** (by twxs) — Provides syntax coloring for `.dts` and `.overlay` files.

---

## 🐞 2. Debugging in VS Code (Breakpoints & Variables)

Because our compilation generates a **`zephyr.elf`** file containing full debugging symbols, we can connect our **ST-LINK** debugger and step through the code visually.

### The configuration file (`.vscode/launch.json`):
Inside your project folder, create a folder named `.vscode` and a file named `launch.json`. Paste the following configuration:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Zephyr (ST-Link)",
            "cwd": "${workspaceRoot}",
            "executable": "${workspaceRoot}/stwinbx1_producer_consumer/build/zephyr/zephyr.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "openocd",
            "configFiles": [
                "interface/stlink.cfg",
                "target/stm32u5x.cfg"
            ]
        }
    ]
}
```

### How to use it:
1. Connect your **STEVAL-STWINBX1** board to your PC via USB.
2. Open [main.c](file:///C:/Users/kerem/Documents/Zephyr/Zephyr_2go/stwinbx1_producer_consumer/src/main.c) in VS Code.
3. Click to the left of any line number to set a **Red Dot Breakpoint**.
4. Press **F5** (or click the "Run & Debug" tab and click the green arrow).
5. VS Code will flash the board, halt execution at `main()`, and let you:
   * **Step Over** (`F10`) or **Step Into** (`F11`) functions.
   * Watch variables change values in the **Variables Panel** on the left.
   * View the call stack to see which thread is currently active.

---

## 🛠️ 3. Debugging in STM32CubeIDE (Best of Both Worlds!)

If you prefer the familiar STM32CubeIDE interface for debugging registers, memory pools, and peripherals, you can use it to debug your Zephyr project!

```mermaid
graph LR
    A[Zephyr Build System] -- Generates --> B(zephyr.elf)
    B -- Imported into --> C[STM32CubeIDE Debugger]
    C -- Connects via ST-LINK to --> D[Microcontroller Hardware]
```

### How to Import and Debug `zephyr.elf`:
1. Open **STM32CubeIDE**.
2. Click **File -> Import...**
3. Select **C/C++ -> Launch Groups / Executable** (or *C/C++ Executable*) and click **Next**.
4. Browse and select the compiled executable:
   📂 `C:\Users\kerem\Documents\Zephyr\Zephyr_2go\stwinbx1_producer_consumer\build\zephyr\zephyr.elf`
5. Click **Finish**. STM32CubeIDE will import the binary.
6. Right-click the imported executable in your project explorer and select **Debug As -> STM32 Cortex-M C/C++ Application**.
7. In the debug configuration:
   * Under the **Debugger** tab, verify **ST-LINK** is selected as the debug probe.
   * Under the **Startup** tab, verify that it points to your source files in `Zephyr_2go/stwinbx1_producer_consumer/src`.
8. Click **Debug**.

STM32CubeIDE will launch its full graphical debug perspective. You get:
* **The SFRs (Special Function Registers) Watcher** to see physical STM32 registers changing.
* **The Expressions tab** to monitor variables.
* **Line-by-line stepping** through your Zephyr threads!

---

## 💡 The Takeaway
Zephyr is **not** a black box. The command line is just the engine under the hood. For your daily work, you can use the rich, graphical interfaces of **VS Code** or **STM32CubeIDE** to write, run, and debug your code seamlessly!
