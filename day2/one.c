#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

enum value {
	rock = 1,
	paper = 2,
	scissors = 3,
	win = 6,
	loss = 0,
	draw = 3,
};

uint16_t get_score(FILE *input);

int main()
{
	FILE *input = fopen("input", "r");
	uint16_t tmp, total = 0;
	while ((tmp = get_score(input)) != 0) {
		total += tmp;
	}
	printf("%d\n", total);
	fclose(input);
}

uint16_t
get_score(FILE *input)
{
	size_t size, n, index = 0;
	char *currentline = NULL;
	size = getline(&currentline, &n, input);
	char results[2];
	if (size == -1) {
		free(currentline);
		return 0;
	}
	for (int i = 0; currentline[i] != '\n'; i++) {
		if (isalpha(currentline[i])) {
			results[index] = currentline[i];
			index++;
		}
	}
	free(currentline);
	if (strcmp(results, "AX") == 0) {
		return rock + draw;
	} else  if (strcmp(results, "AY") == 0) {
		return paper + win;
	} else  if (strcmp(results, "AZ") == 0) {
		return scissors + loss;
	} else  if (strcmp(results, "BX") == 0) {
		return rock + loss;
	} else  if (strcmp(results, "BY") == 0) {
		return paper + draw;
	} else  if (strcmp(results, "BZ") == 0) {
		return scissors + win;
	} else  if (strcmp(results, "CX") == 0) {
		return rock + win;
	} else  if (strcmp(results, "CY") == 0) {
		return paper + loss;
	} else  if (strcmp(results, "CZ") == 0) {
		return scissors + draw;
	}
	return 0;
}
