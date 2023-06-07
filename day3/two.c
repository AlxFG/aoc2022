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
	char *one, *two, *three;
	one = two = three = NULL;
	char pchar;
	getline(&one, &n, input);
	getline(&two, &n, input);
	size = getline(&three, &n, input);
	if (size == -1) {
		free(one);
		return 0;
	}
	for (int i = 0; i < strlen(one) - 1; i++)
		for (int j = 0; j < strlen(two) - 1; j++)
			for (int k = 0; k < strlen(three) - 1; k++)
				if (one[i] == two[j] && one[i] == three[k])
					pchar = one[i];
	free(one);
	free(two);
	free(three);
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
