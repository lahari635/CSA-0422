// producer_consumer.c
#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE emptySlots, fullSlots, mutex;

DWORD WINAPI producer(LPVOID id) {
    int pid = (int)(intptr_t)id;
    for (int i = 0; i < 10; ++i) {
        WaitForSingleObject(emptySlots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = pid*100 + i;
        printf("Producer %d produced %d at index %d\n", pid, buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(fullSlots, 1, NULL);
        Sleep(100 + (pid*50));
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID id) {
    int cid = (int)(intptr_t)id;
    for (int i = 0; i < 10; ++i) {
        WaitForSingleObject(fullSlots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        int val = buffer[out];
        printf("Consumer %d consumed %d from index %d\n", cid, val, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(emptySlots, 1, NULL);
        Sleep(150 + (cid*30));
    }
    return 0;
}

int main(){
    emptySlots = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    fullSlots  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    HANDLE p1 = CreateThread(NULL,0,producer,(LPVOID)1,0,NULL);
    HANDLE p2 = CreateThread(NULL,0,producer,(LPVOID)2,0,NULL);
    HANDLE c1 = CreateThread(NULL,0,consumer,(LPVOID)1,0,NULL);

    WaitForSingleObject(p1, INFINITE);
    WaitForSingleObject(p2, INFINITE);
    WaitForSingleObject(c1, INFINITE);

    CloseHandle(p1); CloseHandle(p2); CloseHandle(c1);
    CloseHandle(emptySlots); CloseHandle(fullSlots); CloseHandle(mutex);

    printf("Producer-Consumer demo finished.\n");
    return 0;
}
