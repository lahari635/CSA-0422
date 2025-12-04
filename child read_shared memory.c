#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCSTR pBuf;

    // Open the same shared memory created by parent
    hMapFile = OpenFileMapping(
                 FILE_MAP_READ,
                 FALSE,
                 "MySharedMemory");

    if (hMapFile == NULL) {
        printf("Could not open file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map to address space
    pBuf = (LPCSTR) MapViewOfFile(
                        hMapFile,
                        FILE_MAP_READ,
                        0,
                        0,
                        256);

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Read from shared memory
    printf("\nChild: Message read from shared memory:\n");
    printf("%s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
