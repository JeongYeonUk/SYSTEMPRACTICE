#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
  STARTUPINFO si = { 0, };
  PROCESS_INFORMATION pi;
  si.cb = sizeof(si);
  TCHAR command[] = _T("Operation2.exe");

  CreateProcess(
    NULL, command, NULL, NULL,
    TRUE, 0, NULL, NULL, &si, &pi
  );

  while (1) {
    // Busy Waiting !!
    for (DWORD i = 0; i < 10000; ++i)
      for (DWORD i = 0; i < 10000; ++i);

    _fputts(_T("Operation1.exe\n"), stdout);
  }

  return 0;
}
