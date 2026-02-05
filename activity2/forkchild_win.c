#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize memory
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Path to mspaint.exe
    // Usually located in C:\Windows\System32\mspaint.exe
    // Adjust if your system path differs
    LPCSTR programPath = "C:\\Windows\\System32\\mspaint.exe";

    // Create child process
    if (!CreateProcess(
        programPath,   // Application name
        NULL,          // Command line arguments
        NULL,          // Process handle not inheritable
        NULL,          // Thread handle not inheritable
        FALSE,         // Set handle inheritance to FALSE
        0,             // No creation flags
        NULL,          // Use parent's environment block
        NULL,          // Use parent's starting directory 
        &si,           // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    printf("Child process created: MSPaint is running.\n");

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Child process finished.\n");
    return 0;
}
