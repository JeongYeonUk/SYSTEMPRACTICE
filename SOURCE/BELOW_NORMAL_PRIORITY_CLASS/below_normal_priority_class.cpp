#pragma warning (disable : 4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
  SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

  while (1) {
    for (DWORD i = 0; i < 10000; ++i)
      for (DWORD i = 0; i < 100000; ++i);

    _fputts(_T("BELOW_NORMAL_PRIORITY_CLASS Process \n"), stdout);
  }

  return 0;
}
