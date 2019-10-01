#pragma warning (disable : 4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//CRITICAL_SECTION hCriticalSection;
HANDLE hMutex;

void IncreaseCount()
{
  //EnterCriticalSection(&hCriticalSection);
  WaitForSingleObject(hMutex, INFINITE);
  gTotalCount++;
  //LeaveCriticalSection(&hCriticalSection);
  ReleaseMutex(hMutex);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
  for (DWORD i = 0; i < 1000; ++i)
  {
    IncreaseCount();
  }
  return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
  DWORD dwThreadIds[NUM_OF_GATE];
  HANDLE hThreads[NUM_OF_GATE];

  //InitializeCriticalSection(&hCriticalSection);
  hMutex = CreateMutex(
    NULL,
    FALSE,
    NULL
  );

  if (hMutex == NULL)
  {
    _tprintf(_T("CreateMutex error: %d\n"), GetLastError());
  }

  for (DWORD i = 0; i < NUM_OF_GATE; ++i)
  {
    hThreads[i] = (HANDLE)
      _beginthreadex(
        NULL, 0,
        ThreadProc, NULL,
        CREATE_SUSPENDED,
        (unsigned*)& dwThreadIds[i]
      );

    if (hThreads[i] == NULL)
    {
      _tprintf(_T("Thread creation fault! \n"));
      return -1;
    }
  }

  for (DWORD i = 0; i < NUM_OF_GATE; ++i)
  {
    ResumeThread(hThreads[i]);
  }

  WaitForMultipleObjects(
    NUM_OF_GATE, hThreads, TRUE, INFINITE
  );

  _tprintf(_T("total count: %d \n"), gTotalCount);

  for (DWORD i = 0; i < NUM_OF_GATE; ++i)
  {
    CloseHandle(hThreads[i]);
  }

  //DeleteCriticalSection(&hCriticalSection);
  CloseHandle(hMutex);

  return 0;
}
