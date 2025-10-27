#include <windows.h>
#include <stdio.h>

#define MAX_EVENTS 1024

typedef struct {
    DWORD vk;
    UINT msg;
} KeyEvent;

static KeyEvent events[MAX_EVENTS];
static size_t count = 0;
int running = 1;



// takes a hex integer representing a key e.g w = 0x57
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
//same function as press_key but has duration feature
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




//callback function that hooks the windows keyboard input stream 
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (!running)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    if (nCode == HC_ACTION && count < MAX_EVENTS) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        
        //cheks if key pressed = VK_ESCAPE = ESC && its a key down event
        if (p->vkCode == VK_ESCAPE && (wParam == WM_KEYDOWN)){
             PostQuitMessage(0);
             running = 0;
             printf("Escape pressed - stopping cature.\n");
             return CallNextHookEx(NULL, nCode, wParam, lParam);

        }
           
        //load event array/recorder
        printf("[HOOK] vk=0x%02lX %s\n",(unsigned long)p->vkCode,(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? "DOWN" : "UP");

        events[count++] = (KeyEvent){ .vk = p->vkCode, .msg = (UINT)wParam };
        if (wParam == WM_KEYDOWN)
            printf("Key down: vk=0x%02lX\n", (unsigned long)p->vkCode);
        else if (wParam == WM_KEYUP)
            printf("Key up: vk=0x%02lX\n", p->vkCode);
        
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
  //installs winEvent hook to the windows event subsystem
  //begins the win key event hook
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0); 
    MSG msg;
    HWND hwnd = find_minecraft_window();
    if (!hwnd) {
        printf("Minecraft window not found!\n");
        return 1;
    }

  //watches msg for msg to become a filled structure by the event hook    
    while (GetMessage(&msg, NULL, 0, 0)) {}
    printf("Replaying Recorded Events\n");
    Sleep(5000);
    for (size_t i = 0; i < count; i++){
        int is_down = (events[i].msg == WM_KEYDOWN || events[i].msg == WM_SYSKEYDOWN);
        //GetMessage(&msg, NULL, 0, 0);
    
         printf("[REPLAY] vk=0x%02lX %s\n", (unsigned long)events[i].vk, is_down ? "DOWN" : "UP");
    
        //INPUT input = {0};
        //input.type = INPUT_KEYBOARD;
        //input.ki.wVk -(WORD)events[i].vk;
        if (is_down){
            press_key((WORD)events[i].vk);
        }
          
        //SendInput(1,&input,sizeof(INPUT));
    }


    return 0;
}

