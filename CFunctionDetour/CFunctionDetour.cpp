#include "stdafx.h"
#include <Windows.h>

void foo() {
	printf("Foo");
}

void bar() {
	printf("Bar");
}


void detour(void* sourceAddress, void* targetAddress) {
	DWORD oldProtect;
	char* source = (char*)sourceAddress;
	char* target = (char*)targetAddress;

	int offset = target - source - 5;
	VirtualProtect(source, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

	*(char*)(source) = 0xE9;
	*(int*)(source + 1) = offset;

	VirtualProtect(source, 5, oldProtect, &oldProtect);
}

int main()
{
	detour(foo, bar);

	foo();

	getchar();
}

