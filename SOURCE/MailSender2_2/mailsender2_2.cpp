#pragma warning(disable:4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
  HANDLE hMailSlot;
  TCHAR message[50];
  DWORD bytesWritten;

  /**************** get Handle code *****************/
  FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
  _ftscanf(file, _T("%d"), &hMailSlot);
  fclose(file);
  _tprintf(_T("Inheritable Handle : %d \n"), hMailSlot);
  /**************** get Handle code *****************/

  while (1) {
    _fputts(_T("CHILD MY CMD > "), stdout);
    _fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

    if (!WriteFile(hMailSlot, message, _tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL)) {
      _fputts(_T("Unable to write!"), stdout);
      _gettchar();
      CloseHandle(hMailSlot);
      return 1;
    }

    if (!_tcscmp(message, _T("exit"))) {
      _fputts(_T("Good Bye!"), stdout);
       break;
    }
  }

  CloseHandle(hMailSlot);

  return 0;
}
