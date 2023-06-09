#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int16_t get_ranges(FILE *input);
int16_t in_range(int16_t sections[]);

int main()
{
	FILE *input = fopen("input", "r");
	int16_t tmp, total = 0;
	if (!input) {
		fprintf(stderr, "File could not be opened\n");
		return 1;
	}
	while ((tmp = get_ranges(input)) != -1) {
		printf("%d\n", tmp);
		total += tmp;
	}
	printf("%d\n", total);
	fclose(input);
}

int16_t
get_ranges(FILE *input)
{
	int16_t sections[4], index = 0;
	size_t size, n;
	char *token, *curr = NULL;
	char delims[] = "-,\n";
	size = getline(&curr, &n, input);
	if (size == -1) {
		free(curr);
		return -1;
	}
	token = strtok(curr, delims);
	while (token) {
		sections[index++] = atoi(token);
		token = strtok(NULL, delims);
	}
	/*
	 * for (size_t i = 0; i < sizeof(sections) / sizeof(int16_t); i++) {
	 * 	printf("%d\n", sections[i]);
	 * }
	 */
	free(curr);
	return in_range(sections);
}

int16_t
in_range(int16_t sections[])
{
	if (sections[0] <= sections[2] && sections[1] >= sections[3])
		return 1;
	else if (sections[2] <= sections[0] && sections[3] >= sections[1])
		return 1;
	else
		return 0;
}
