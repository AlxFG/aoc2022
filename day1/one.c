#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct list_t {
	struct list_t *next;
	int32_t data;
} list_t;

int32_t get_calories(FILE *input);
list_t *list_init();
void list_add(list_t *node, int32_t data);
void list_destroy(list_t *node);
void list_output(list_t *node);
int32_t get_largest(list_t *node);

int main()
{
	FILE *input = fopen("input", "r");
	if (!input) {
		fprintf(stderr, "failed to read file\n");
		return 1;
	}
	list_t *list = list_init();
	int32_t buffer = 0;
	while ((buffer = get_calories(input)) != -1) {
		list_add(list, buffer);
	}
	printf("%d\n", get_largest(list));
	list_destroy(list);
	fclose(input);
	return 0;
}

list_t
*list_init()
{
	list_t *tmp = calloc(sizeof(list_t), 1);
	tmp->data = 0;
	return tmp;
}

void
list_add(list_t *node, int32_t data)
{
	if (node->data == 0) {
		node->data = data;
	} else {
		while (node->next)
			node = node->next;
		node->next = calloc(sizeof(list_t), 1);
		node->next->data = data;
	}
}

void
list_destroy(list_t *node)
{
	list_t *curr, *next;
	for (curr = node; curr; curr = next) {
		next = curr->next;
		free(curr);
	}
}

void
list_output(list_t *node)
{
	while (node) {
		printf("%u\n", node->data);
		node = node->next;
	}
}

int32_t
get_calories(FILE *input)
{
	char *currentline = NULL;
	size_t n, size;
	int32_t total = 0;
	size = 0;
	while ((size = getline(&currentline, &n, input)) != 1) {
		if (size == -1) {
			free(currentline);
			return -1;
		}
		total += atoi(currentline);
	}
	free(currentline);
	return total;
}

int32_t
get_largest(list_t *node)
{
	int32_t largest = node->data;
	while (node) {
		if (node->data > largest)
			largest = node->data;
		node = node->next;
	}
	return largest;
}
