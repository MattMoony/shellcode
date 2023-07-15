#include <iostream>
#include <Windows.h>

#define PAUSE_BEFORE	true
#define NEW_THREAD		false
#define PAYLOAD \
		"\x90\x90\xc3"

int main()
{
	HANDLE hProcess = GetCurrentProcess(), 
		hThread;
	UCHAR uchShc[] = PAYLOAD;
	LPVOID lpAllocation;
	SIZE_T szAllocation = sizeof(uchShc),
		szWritten;
	BOOL bSuccess;
	DWORD dwWaitRet;

	printf("[*] Allocating memory ... \n");
	lpAllocation = VirtualAllocEx(hProcess, NULL, szAllocation, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (lpAllocation == NULL) {
		printf("[-] Failed to allocate memory! (%lx)\n", GetLastError());
		return 1;
	}
	printf("[+] Got memory of size %llx @ %p\n", szAllocation, lpAllocation);

	printf("[*] Writing shellcode to memory ...\n");
	bSuccess = WriteProcessMemory(hProcess, lpAllocation, uchShc, szAllocation, &szWritten);
	if (!bSuccess) {
		printf("[-] Failed to write to process memory! (%lx)\n", GetLastError());
		return 1;
	}

#if PAUSE_BEFORE
	printf("[!] Press <ENTER> to launch shellcode ...\n");
	getchar();
#endif

#if NEW_THREAD
	printf("[*] Launching thread ...\n");
	hThread = CreateRemoteThreadEx(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpAllocation, NULL, NULL, NULL, NULL);
	if (hThread == NULL) {
		printf("[-] Failed to launch thread running shellcode! (%lx)\n", GetLastError());
		return 1;
	}

	printf("[*] Waiting for thread to finish ...\n");
	dwWaitRet = WaitForSingleObject(hThread, INFINITE);
	if (dwWaitRet != 0) {
		printf("[-] Thread seems to have failed along the way! (%lx)\n", GetLastError());
		return 1;
	}
#else
	printf("[*] Jumping to shellcode ...\n");
	((void (*)()) lpAllocation)();
#endif

	printf("[+] Success! Exiting now ... \n");
	return ERROR_SUCCESS;
}
