#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <netlistmgr.h>
#pragma comment(lib, "ole32.lib")
#include <processthreadsapi.h>
LPWSTR  p;
LPWSTR p2;
LPWSTR name;
int index;
int jj = 0;
DWORD start_time, end_time;
STARTUPINFOW si;
PROCESS_INFORMATION pi;

DWORD k;
NLM_CONNECTIVITY con;
INetworkListManager* pNetworkListManager = NULL;
HRESULT hr;
HANDLE hUserToken;

void input_name() {
	int i;
	p[0] = p2[0] = 0;
	wcscat(p, L"netsh wlan set hostednetwork mode=allow ssid=");
	wcscat(p2, L"netsh wlan connect ssid=\"");
	printf("Program to connect and restor lost password\nEnter your wifi name: ");
	fgetws(name,34,stdin);
	for (i = 0; i < name[i]; i++);
	i--;
	name[i] = 0;
	wcscat(p2,name);
	wcscat(p2, L"\"");
	wcscat(p2, L" name=\"");
	wcscat(p2, name);
	wcscat(p2, L"\"");
	wcscat(p, name);
	index = wcslen(p) + 5;
	wcscat(p, L" key=                      ");
}
void print_time() {
	end_time -= start_time;
	end_time /= 1000;
	printf("\ntime elapsed\nhours: %ld ,minutes: %ld\n", end_time/60,end_time%60);
}
void run(int start,int amount_digits) {
	int i;
	for (i = 0; i < 10; i++) {
		p[index + start] = '0'+i;
		if (start < amount_digits)
			run(start + 1, amount_digits);
		memset(&si, 0, sizeof(si));
		memset(&pi, 0, sizeof(pi));
		si.cb = sizeof(si);
		//CreateProcessAsUserA(hUserToken, (LPCSTR)"C:\\Windows\\System32\\netsh.exe",p,0,0,0, CREATE_NO_WINDOW,0,0,&si,&pi);
		//CreateProcessAsUserA(hUserToken, (LPCSTR)"C:\\Windows\\System32\\netsh.exe", p2, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi);
		CreateProcessW(L"C:\\Windows\\System32\\netsh.exe", p, 0, 0, 1,CREATE_NO_WINDOW , 0,  0,&si,&pi);
		memset(&si, 0, sizeof(si));
		memset(&pi, 0, sizeof(pi));
		si.cb = sizeof(si);
		Sleep(20);
		CreateProcessW(L"C:\\Windows\\System32\\netsh.exe", p2, 0,0,1, CREATE_NO_WINDOW,0,0,&si,&pi);
		Sleep(20);
		con = NLM_CONNECTIVITY_DISCONNECTED;
		hr = CoCreateInstance(CLSID_NetworkListManager, NULL,
			CLSCTX_ALL, IID_INetworkListManager,
			(LPVOID*)&pNetworkListManager);
		if (SUCCEEDED(hr)) {
			hr = pNetworkListManager->GetConnectivity(&con);
			if (SUCCEEDED(hr) && con) {
				end_time = GetTickCount();
				printf("Succeded connect password: ");
				for (i = 0; i < amount_digits; i++)
					printf("%c", p[index + i]);
				print_time();
				system("pause>0");
				exit(0);
			}
		}
	}
}
void main() {
	int i;
	p = (wchar_t*)malloc(sizeof(wchar_t) * 200);
	p2 = (wchar_t*)malloc(sizeof(wchar_t) * 200);
	name = (wchar_t*)malloc(sizeof(wchar_t) * 35);
	input_name();
	start_time = GetTickCount();
	for(i=8;i<=15;i++)
		run(1,i);
	printf("Can not connect to wifi or you was not connected before\n"
		"or the password contains letters or to big\n");
	system("pause>0");
}
