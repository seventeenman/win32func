#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include<TlHelp32.h>

#define ERROR -1

int GetIdByName(const char* pName) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == snapshot){
		return ERROR;
	}
	PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };

	if (Process32First(snapshot, &processEntry)) {
		while (strcmp(processEntry.szExeFile, pName) != 0) {
			if (!Process32Next(snapshot, &processEntry)) {
				CloseHandle(snapshot);
				return ERROR;
			}
			Process32Next(snapshot, &processEntry);
		}
	}
	CloseHandle(snapshot);
	return processEntry.th32ProcessID;
}

int main() {
	std::cout << GetIdByName("notepad.exe");
}