#include <windows.h>
#include <stdio.h>

// small helper to simulate a key press
void press_key(WORD vk) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;

    // key down
    SendInput(1, &input, sizeof(INPUT));

    // short delay
    Sleep(50);

    // key up
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void hold_key(WORD vk, int duration_ms) {
    INPUT input = {0};

    // key down
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;
    SendInput(1, &input, sizeof(INPUT));
    printf("Key down\n");

    // hold the key
    Sleep(duration_ms);

    // key up
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    printf("Key up\n");
}

HWND find_minecraft_window(void) {
    HWND hwnd = GetTopWindow(NULL);
    char title[512];

    while (hwnd) {
        GetWindowTextA(hwnd, title, sizeof(title));
        if (IsWindowVisible(hwnd) && strstr(title, "Minecraft")) {
            return hwnd;
        }
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }
    return NULL;
}

int main(void) {
    // find the Minecraft window by title
    HWND hwnd = find_minecraft_window();
    if (!hwnd) {
        printf("Minecraft window not found!\n");
        return 1;
    }

    printf("Found Minecraft window: %p\n", hwnd);

    // optional: bring window to front (not required for SendInput)
    SetForegroundWindow(hwnd);
    Sleep(500);

    // example: press the 'W' key
    printf("Sending W key...\n");
    hold_key(0x57, 40000); // 0x57 = 'W'

    printf("Done.\n");
    return 0;
}

