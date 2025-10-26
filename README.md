## 🧩 Full Setup: Install, Compile, and Run the Minecraft Bot

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

