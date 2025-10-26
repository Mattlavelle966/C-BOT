#include <windows.h>
#include <stdio.h>

// callback function that runs for every top-level window
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char title[512];
    // get the title text
    GetWindowTextA(hwnd, title, sizeof(title));
    // only print visible windows that have titles
    if (IsWindowVisible(hwnd) && title[0] != '\0') {
        printf("%p  %s\n", hwnd, title);
    }
    return TRUE;
}

int main() {
    printf("Listing visible Wine window titles:\n\n");
    EnumWindows(EnumWindowsProc, 0);
    return 0;
}

