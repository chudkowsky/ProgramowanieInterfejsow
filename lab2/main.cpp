#include <iostream>
#include <windows.h>

using namespace std;

void get_comm_timeout(HANDLE hCommDev,COMMTIMEOUTS CommTimeouts){
    BOOL if_correct = GetCommTimeouts(hCommDev,&CommTimeouts);
    cout<<"Read Interval Timeout: "<<CommTimeouts.ReadIntervalTimeout<<"\n";
    cout<<"Read Total Timeout Constant: "<<CommTimeouts.ReadTotalTimeoutConstant<<"\n";
    cout<<"Read Total Timeout Multiplier: "<<CommTimeouts.ReadTotalTimeoutMultiplier<<"\n";
    cout<<"Write Total Timeout Constant: "<<CommTimeouts.WriteTotalTimeoutConstant<<"\n";
    cout<<"Write Total Timeout Multiplier: "<<CommTimeouts.WriteTotalTimeoutMultiplier<<"\n";
}

void get_comm_state(HANDLE hCommDev, DCB dcb){
    BOOL if_correct = GetCommState(hCommDev,&dcb);
    cout<<"Baud Rate: "<<dcb.BaudRate<<"\n";
    cout<<"Byte Size: "<<dcb.ByteSize<<"\n";
    cout<<"fParity : "<<dcb.fParity<<"\n";
    cout<<"fDtrControl: "<<dcb.fDtrControl<<"\n";
    cout<<"StopBits: "<<dcb.StopBits<<"\n";
}

bool writeSerialPort(HANDLE hCommDev,int buffer)
{
 unsigned long numberOfBytesWritten = 0;
 unsigned long numberOfBytesToWrite = 1;
 if(WriteFile(hCommDev, &buffer, numberOfBytesToWrite,&numberOfBytesWritten, NULL)==0)
    return false;
 else
    return true;
}
bool readSerialPort(HANDLE hCommDev,int numberOfBytesRead)
{
 int bytesRead;
 numberOfBytesRead=0;
 unsigned long numberOfBytesToRead=0;
 if (ReadFile (hCommDev, &bytesRead, 1, &numberOfBytesToRead, 0)){
 if (numberOfBytesToRead == 1){
 numberOfBytesRead = bytesRead;
 cout <<"Odczytano: "<< (char)numberOfBytesRead << endl;
 return true;
 }
 }
 return false;
}



int main()
{
    LPCTSTR portName = "COM3";
    DWORD ShareMode = 0;
    LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL;
    DWORD dwFlagAndAttributes = 0 ;
    HANDLE hTemplateFile = NULL;
    DCB dcb;
    COMMTIMEOUTS CommTimeouts;

    HANDLE hCommDev = CreateFile(portName,GENERIC_READ | GENERIC_WRITE,ShareMode,lpSecurityAttributes,OPEN_EXISTING,dwFlagAndAttributes,hTemplateFile);
    get_comm_state(hCommDev,dcb);
    cout<<"\n";
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
    get_comm_state(hCommDev,dcb);
    cout<<"\n";
    get_comm_timeout(hCommDev,CommTimeouts);
    writeSerialPort(hCommDev,'l');
    readSerialPort(hCommDev,1);
    return 0;
}



