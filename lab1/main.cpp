#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    LPCTSTR portName = "COM3";
    DWORD ShareMode = 0;
    LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL;
    DWORD dwFlagAndAttributes = 0 ;
    HANDLE hTemplateFile = NULL;
    DCB dcb;
    HANDLE hCommDev = CreateFile(portName,GENERIC_READ | GENERIC_WRITE,ShareMode,lpSecurityAttributes,OPEN_EXISTING,dwFlagAndAttributes,hTemplateFile);
     if (hCommDev != INVALID_HANDLE_VALUE){
        dcb.DCBlength = sizeof(dcb);
        GetCommState(hCommDev, &dcb);
        dcb.BaudRate = CBR_1200;
         dcb.fParity = TRUE;
         dcb.Parity = NOPARITY;
         dcb.StopBits = TWOSTOPBITS;
         dcb.ByteSize = 8;
         dcb.fDtrControl = 1;
         SetCommState(hCommDev, &dcb);
     }else{
        return 1;
     }
    BOOL if_correct = GetCommState(hCommDev,&dcb);
    printf("%d\n",dcb.BaudRate);
    printf("%d\n",dcb.ByteSize);
    printf("%d\n",dcb.fParity);
    printf("%d\n",dcb.fDtrControl);
    printf("%d\n",dcb.StopBits);
    return 0;
}



