#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "wininet")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wininet.h>
char* p;
char* p2;
char* name;
int index = 79;
int jj = 0;
DWORD start_time, end_time;
DWORD k;
LPWSTR  k2;
DWORD k3;
void input_name() {
	int i;
	p[0] = p2[0] = 0;
	strcat(p, "netsh wlan set hostednetwork mode=allow ssid=");
	strcat(p2, "netsh wlan connect ssid=");
	printf("Program to connect and restor lost password\nEnter your wifi name: ");
	gets(name);
	strcat(p2,name);
	strcat(p2, " name=");
	strcat(p2, name);
	strcat(p2, " >0");
	for (i = strlen(name); i < 30; i++)
		name[i] = ' ';
	name[i] = 0;
	strcat(p, name);
	strcat(p, "key=                      >0");
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
		system(p);
		system(p2);
		Sleep(1000);
		if (InternetGetConnectedState(&k, 0)) {
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
void main() {
	int i;
	p = malloc(200);
	p2 = malloc(200);
	name = malloc(35);
	input_name();
	start_time = GetTickCount();
	
	for(i=8;i<=15;i++)
		run(1,i);
	printf("Can not connect to wifi or you was not connected before\n"
		"or the password contains letters or to big\n");
	system("pause>0");
}
