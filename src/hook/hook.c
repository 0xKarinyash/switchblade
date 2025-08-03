#include "hook.h"
#include <windows.h>

static BOOL s_enabled = FALSE;
static HHOOK s_hHook;

static BOOL s_ksCapsProcessed = FALSE;
static BOOL s_ksShiftProcessed = FALSE;

static BOOL s_winPressed = FALSE;

static LRESULT CALLBACK LLKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

void EnableHook(void) {
    s_hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LLKeyboardProc, 0, 0);
    s_enabled = TRUE;
}

void DisableHook(void) {
    UnhookWindowsHookEx(s_hHook);
    s_enabled = FALSE;
}

// Original Switchy uses keybd_event(), but it has been superseded
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-keybd_event
static void SimulateKeyUp(int keyCode) {
    INPUT inputs[1] = {0};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = keyCode;
    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, inputs, sizeof(INPUT));
}

static void SimulateKeyPress(int keyCode) {
    INPUT inputs[2] = {0};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = keyCode;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = keyCode;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
}

static void ChangeLayout(void) {
    INPUT inputs[4] = {0};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_MENU;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_LSHIFT;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_MENU;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_LSHIFT;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, inputs, sizeof(INPUT));
}

static void ToggleCapsLockState(void) {
    SimulateKeyPress(VK_CAPITAL);
}

static LRESULT CALLBACK LLKeyboardProc(const int nCode, const WPARAM wParam, const LPARAM lParam) {
    const KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
    if (key == NULL || nCode != HC_ACTION || key->flags & LLKHF_INJECTED) {
        return CallNextHookEx(s_hHook, nCode, wParam, lParam);
    }

    switch (key->vkCode) {
        case VK_CAPITAL:
            if (wParam == WM_SYSKEYDOWN && !s_ksCapsProcessed) {
                s_ksCapsProcessed = TRUE;
                s_enabled = !s_enabled;
                return 1;
            }
            if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                s_ksCapsProcessed = FALSE;
                if (s_winPressed) {
                    s_winPressed = FALSE;
                    SimulateKeyUp(VK_LWIN);
                }
                if (s_enabled) {
                    if (!s_ksShiftProcessed) {
                        ChangeLayout();
                    } else {
                        s_ksShiftProcessed = FALSE;
                    }
                }
            }

            if (!s_enabled) break;
            if (wParam == WM_KEYDOWN && !s_ksCapsProcessed) {
                s_ksCapsProcessed = TRUE;
                if (s_ksShiftProcessed) {
                    ToggleCapsLockState();
                }
            }

            return 1;

        case VK_LSHIFT:
            if ((wParam == WM_KEYUP || wParam == WM_SYSKEYUP) && !s_ksCapsProcessed) {
                s_ksShiftProcessed = FALSE;
            }
            if (!s_enabled) {
                break;
            }
            if (wParam == WM_KEYDOWN && !s_ksShiftProcessed) {
                s_ksShiftProcessed = TRUE;
                if (s_ksCapsProcessed) {
                    ToggleCapsLockState();
                }
            }
            break;

        default:
            break;
    }

    return CallNextHookEx(s_hHook, nCode, wParam, lParam);
}