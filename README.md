# KeyHook Macro Tracker & Runner

A lightweight **macro recorder and playback tool** built in pure C using the Windows API (via Wine on Linux).  
It hooks into the global keyboard input stream, records every key press/release event, and can later replay them **exactly 1:1** using our `key_press(WORD)` function built on `SendInput()`.

---

## Features

- Global low-level keyboard hook (`WH_KEYBOARD_LL`)
- Records **raw virtual-key events** as they happen  
- Replays macros with 1:1 key timing and order  
- Press **ESC** to stop recording and trigger playback  
- In-memory event buffer (`KeyEvent` array) no external files needed  

---

##  Work in Progress

This project is still in **early development**.  
Current functionality focuses on accurate keyboard event logging and 1:1 playback, but several improvements are planned:

- Dynamic memory handling (linked list instead of fixed array)
- File-based macro saving and loading
- Optional delay preservation for realistic playback
- GUI or command-line macro manager
- Multi-macro session support

> **Note:**  
> This project was designed and tested on **Linux** (Arch-based) specifically for **Wine users** who want to run lightweight Windows automation or macro tools in the background of a **Wayland** environment.  
>  
> Its native Linux workflow with Wine based background/unfocused window macro automation, allows for unfocused windows to run macro executions for Win applications without requiring a visible or focused window, this allows Wayland users to have unfocused windows run input macros while the users does something else.


Expect minor bugs and inconsistencies during rapid prototyping this build is mainly for testing core input hooks and replay accuracy.

## Plans

**Keyboard Integration:**  *Complete*  
Core keyboard hook, event logging, and replay functionality are fully implemented and tested.

**Mouse Integration:**  *Planned*  
Next milestone: add low-level mouse hook support to record and replay mouse input (clicks, moves, scrolls), completing full input automation.

**CLI Interface:**  *In Progress*  
A command line interface will allow users to record, save, load, and replay macros directly from the terminal including arguments for prefix selection, background mode, and macro management.

**Library Packages:**  *Planned*  
Expose the macro system as a lightweight C library for integration into other automation or Wine based scripting tools.  
Future bindings (Lua) are being considered for cross-language support.

---

## How It Works

1. The program installs a **global keyboard hook** using `SetWindowsHookEx`.  
2. Each key press/release event (`WM_KEYDOWN`, `WM_KEYUP`) is captured and stored in an array.  
3. When the **ESC key** is pressed, logging stops and the hook is uninstalled.  
4. The recorded sequence is then **replayed** exactly in the same order using our `press_key()` function.  

Each key-down and key-up event is faithfully reproduced, ensuring your macro behaves exactly as recorded — whether for testing, automation, or accessibility.

---

## Build Instructions

```bash
# Compile (Arch / MinGW)
x86_64-w64-mingw32-gcc keyhook.c -o keyhook.exe -luser32

# Run under Wine
WINEPREFIX=~/.wine-mc wine keyhook.exe




## 🧩Full Setup: Install, Compile, and Run the macro recorder and the press esc and let the bot do its work.

```bash
# 1️⃣ Install required packages (Arch Linux)
sudo pacman -S mingw-w64-gcc wine winetricks unzip wget

# 2️⃣ Create and initialize a new Wine prefix for Minecraft
WINEPREFIX=~/.wine-mc wineboot --init

# 3️⃣ (Optional) Verify Wine is working
WINEPREFIX=~/.wine-mc winecfg

# 4️⃣ Compile the bot (from your repo folder, e.g. ~/repos/cbot)
x86_64-w64-mingw32-gcc mc_testbot.c -o mc_bot.exe -luser32

# 5️⃣ Run the bot inside your Wine prefix (Minecraft must already be running)
WINEPREFIX=~/.wine-mc wine mc_bot.exe

