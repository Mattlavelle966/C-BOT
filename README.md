# KeyHook Macro Recorder & Runner

A lightweight **macro recorder and playback tool** built in pure C `(keyhook.c)` using the Windows API (via Wine on Arch).  
It hooks into the global keyboard input stream, records every key press/release event, and can later replay them **exactly 1:1** using our `key_press(WORD)` function built on Windows API `SendInput()`.

I built this project for fun one day while playing Minecraft. I wanted a bot that could play for me in the background. I’ve experimented with similar ideas before using higher-level languages, but I always wanted to write something lower-level something that as few games as possible could escape.

This bot is intended purely for personal and recreational use. I do not condone or support any misuse of this project.


---

## Features

- Global low-level keyboard hook (`WH_KEYBOARD_LL`)
- Records **raw virtual key events** as they happen  
- Replays macros with 1:1 key timing and order  
- Press **ESC** to stop recording and trigger playback  
- In-memory event buffer (`KeyEvent` array) no external files needed  

---

##  Work in Progress

This project is still in **early development**.  
Current functionality focuses on accurate keyboard event logging and 1:1 playback, but several improvements are planned:

> **Note:**  
> This project was designed and tested on **Linux** (Arch-based) specifically for **Wayland users** who want to run lightweight Windows automation or macro tools in the background of a **Wayland** environment.  
>  
> Its native Linux workflow, combined with Wine-based background and unfocused window macro automation, allows Windows applications to execute macros without requiring a visible or focused window.
This enables Wayland users to run background macros on unfocused Wine windows while continuing to use their system normally.

Expect minor bugs or inefficiencies or inconsistencies as this was some rather rapid prototyping, this build is mainly for testing core input hooks and replay accuracy really i just scrambled this together specifically `keyhook.c` but the other files show my learning process.

## Plans

**Keyboard Integration:**  *Complete*  
Core keyboard hook, event logging, and replay functionality are fully implemented and tested.

**Mouse Integration:**  *Planned*  
Next milestone: add low level mouse hook support to record and replay mouse input (clicks, moves, scrolls), completing full input automation.

**CLI Interface:**  *In Progress*  
A command line interface will allow users to record, save, load, and replay macros directly from the terminal including arguments for prefix selection, background mode, and macro management, the hope is a program like similar to Btop.

**Library Packages:**  *Planned*  
create a macro system as a lightweight C library for integration into other automation or Wine based scripting tools.  
Future bindings (Lua) are being considered for cross-language support.

---

## How It Works

1. The program installs a **global keyboard hook** using `SetWindowsHookEx`.  
2. Each key press/release event (`WM_KEYDOWN`, `WM_KEYUP`) is captured and stored in an array.  
3. When the **ESC key** is pressed, logging stops and the hook is uninstalled.  
4. The recorded sequence is then **replayed** exactly in the same order using the `press_key()` function.  

Each key-down and key-up event is faithfully reproduced, ensuring your macro behaves exactly as recorded whether for testing, automation, or accessibility.


---
## Contributing

Contributions are welcome! and appreciated  


If you’d like to contribute:
1. **Fork** the repository  
2. **Create a new branch** for your feature or fix(recommended)  
3. **Commit** your changes with clear, descriptive messages  
4. **Open a pull request** describing what you’ve added or improved  

### Areas of Interest
- Improving input accuracy and event timing  
- Expanding mouse integration  
- Building a cross-platform CLI front-end  
- Developing a modular library interface for other applications(Currently Underway)  
- Implement `<stdbool.h>` and replace `int runnning`  

All contributions should follow a clean, minimal C style keep dependencies light and the project portable ideally using the currently included headers if possible.  

Please test any changes under both **Windows** and **Wine** enviroments but atleast **Wine** at the minumum if you expect your PR to be merged.


---

## Build Instructions

```bash
# Compile (Arch / MinGW)
x86_64-w64-mingw32-gcc keyhook.c -o keyhook.exe -luser32

# Run under Wine
WINEPREFIX=~/.wine-mc wine keyhook.exe

 

## Full Setup: Install, Compile, and Run the macro recorder and the press esc and let the bot do its work.

```bash
# 1 Install required packages (Arch Linux)
sudo pacman -S mingw-w64-gcc wine winetricks unzip wget

# 2 Create and initialize a new Wine prefix for Minecraft
WINEPREFIX=~/.wine-mc wineboot --init

# 3 Optional) Verify Wine is working
WINEPREFIX=~/.wine-mc winecfg

# 4 Compile the bot (from your repo folder, e.g. ~/repos/cbot)
x86_64-w64-mingw32-gcc mc_testbot.c -o mc_bot.exe -luser32

# 5 Run the bot inside your Wine prefix (Minecraft must already be running)
WINEPREFIX=~/.wine-mc wine mc_bot.exe


