#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Zero out the memory for these structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // The path to Paint (Standard on most Windows systems)
    // If this fails, use "C:\\Windows\\System32\\mspaint.exe"
    char command[] = "mspaint.exe";

    printf("Starting Child Process: mspaint.exe\n");

    // Create the process
    if (!CreateProcess(
            NULL,           // No module name (use command line)
            command,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi)            // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    printf("Paint is now running! Check Task Manager.\n");

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}