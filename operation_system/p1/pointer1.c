#include <stdio.h>

int* get_int() {
	int x = 2;
	return &x;
}

int do_something() {
	int i = 33, j = 5, k = 73;
	return i + j * k;
}

int main() {
	int* p = get_int();
	int  i = do_something();
	printf("i -> %d, *p -> %d\n", i, *p);
	return 0;
}