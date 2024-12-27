#include <Windows.h>
#include <errhandlingapi.h>
#include <handleapi.h>
#include <processthreadsapi.h>
#include <wchar.h>
#include <winnt.h>
#include <winuser.h>


VOID ShowFailureResponse(DWORD errorCode)
{
    LPVOID lpMsgBuf;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpMsgBuf,
        0, NULL);

    wprintf(L"%s\n", (LPWSTR)lpMsgBuf);

    LocalFree(lpMsgBuf);
}

int wmain(int argc, WCHAR* argv[]){
    for(unsigned long long i = 0; i < ((unsigned long long)~0); i += 4){
        if(i == GetCurrentThreadId()){
            continue;
        }
        
        HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, i);
        
        if(!hThread){
            ShowFailureResponse(GetLastError());
            continue;
        }
        
        BOOL result = TerminateThread(hThread, -1);
        
        if(!result){
            ShowFailureResponse(GetLastError());
        }
        
        CloseHandle(hThread);
    }
    return 0;
}
