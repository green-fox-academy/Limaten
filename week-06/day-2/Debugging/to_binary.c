#include <stdio.h>

void int_to_bin_digit(int in, int count)
{
	int mask = 1 << count - 1;
	int i;
	for (i = 0; i < count; i++) {
		int result = (in & mask) ? 1 : 0;
		printf("%d", result);
		mask = 1 << (count - i - 2);
	}
}

int main()
{
	int_to_bin_digit(16, 32);
	return 0;
}
