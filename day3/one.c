#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

uint16_t get_bagvalue(FILE *input);
uint16_t get_priority(char item);

int main()
{
	FILE *input = fopen("input", "r");
	uint16_t tmp, total = 0;
	if (!input) {
		return 1;
	}
	while ((tmp = get_bagvalue(input)) != 0)
		total += tmp;
	printf("%hu\n", total);
	fclose(input);
	return 0;
}

uint16_t
get_bagvalue(FILE *input)
{
	size_t size, n, bagsize, compsize;
	char *curr = NULL;
	char pchar;
	size = getline(&curr, &n, input);
	if (size == -1) {
		free(curr);
		return 0;
	}
	bagsize = strlen(curr);
	compsize = bagsize / 2;
	for (int i = 0; i < compsize; i++) {
		for (int j = compsize; j < bagsize; j++) {
			if (curr[i] == curr[j]) {
				pchar = curr[j];
			}
		}
	}
	free(curr);
	return get_priority(pchar);
}

uint16_t
get_priority(char item)
{
	if (isupper(item))
		item -= 38;
	else
		item -= 96;
	return item;
}
