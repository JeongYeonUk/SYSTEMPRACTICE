#pragma warning (disable : 4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[])
{
  TCHAR fileName[] = _T("calc.exe");
  SetCurrentDirectory(_T("C:\\WINDOWS\\system32"));

  _tprintf(_T("Original file attributes \n"));
  DWORD attrib = GetFileAttributes(_T("calc.exe"));
  ShowAttributes(attrib);

  attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
  SetFileAttributes(_T("calc.exe"), attrib);

  _tprintf(_T("Changed file attributes \n"));
  attrib = GetFileAttributes(_T("calc.exe"));
  ShowAttributes(attrib);

  return 0;
}

void ShowAttributes(DWORD attrib)
{
  if (attrib & FILE_ATTRIBUTE_NORMAL)
  {
    _tprintf(_T("Normal \n"));
  }
  else
  {
    if (attrib & FILE_ATTRIBUTE_READONLY)
    {
      _tprintf(_T("Read Only \n"));
    }

    if (attrib & FILE_ATTRIBUTE_HIDDEN)
    {
      _tprintf(_T("Hidden \n"));
    }
  }
  _tprintf(_T("\n"));
}
