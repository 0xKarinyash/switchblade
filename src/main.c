#include "config.h"
#include "hook/hook.h"

#include <windows.h>

DWORD main(void) {
    HANDLE hMutex = CreateMutexExW(NULL, MUTEX_GUID, 0, (DWORD)NULL);
    if (hMutex == NULL) {
        const DWORD err = GetLastError();
        if (err == ERROR_ALREADY_EXISTS || err == ERROR_ACCESS_DENIED) {
            MessageBoxExW(NULL,"Another instance of "NAME" is already running!", NULL, MB_OK | MB_ICONERROR, LANG_ENGLISH);
        } else {
            MessageBoxExW(NULL,L"Something went wrong :C", NULL, MB_OK | MB_ICONERROR, LANG_ENGLISH);
        }
        
        return err;
    }

    EnableHook();

    MSG messages;
    while (GetMessageW(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessageW(&messages);
    }

    DisableHook();
    CloseHandle(hMutex);
    return 0;
}

