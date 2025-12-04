// mutex_sync.c
#include <stdio.h>
#include <windows.h>

volatile long counter = 0;
CRITICAL_SECTION cs;

DWORD WINAPI inc_func(LPVOID arg) {
    for (int i=0;i<100000;i++){
        EnterCriticalSection(&cs);
        counter++;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main(){
    InitializeCriticalSection(&cs);
    HANDLE t1 = CreateThread(NULL,0,inc_func,NULL,0,NULL);
    HANDLE t2 = CreateThread(NULL,0,inc_func,NULL,0,NULL);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    printf("Final counter = %ld (expected 200000)\n", counter);
    DeleteCriticalSection(&cs);
    CloseHandle(t1); CloseHandle(t2);
    return 0;
}
