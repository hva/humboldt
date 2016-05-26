#include <stdio.h>
#include <stdlib.h>

/* types */
typedef struct list_node {
	int val;
	struct list_node *next;
} list_node_t;

typedef struct {
	struct list_node *head;
} list_t;

/* functions */
list_t * list_new();
void list_push(list_t *, int);
int list_pop(list_t *);
int list_len(list_t *);
void list_print(list_t *);
void list_destroy(list_t *);

int main(int argc, char** argv)
{
	/* check input args */
	if (argc < 2)
	{
		fprintf(stderr, "no input files\n");
		return 1;
	}

	/* open file */
	FILE * fi;
	if ((fi = fopen(argv[1], "rt")) == 0) {
		fprintf(stderr, "%s: No such file or directory\n", argv[1]);
		return 1;
	}

	/* read from file */
	int a, b, v;
	int x;

	x = fscanf(fi, "%d", &v);

	if (x == EOF || x == 0) {
		fprintf(stderr, "invalid input\n");
		return 1;
	}

	list_t **adj = malloc(v * sizeof(list_t *));
	int i;
	for (i = 0; i < v; i++) {
		adj[i] = list_new();
	}

	while ((x = fscanf(fi, "%d %d", &a, &b)) != EOF) {
		if (x == 0) {
			fprintf(stderr, "invalid input\n");
			return 1;
		}
		list_push(adj[a], b);
		list_push(adj[b], a);
	}

	/* close file */
	fclose(fi);

	/* check is eulerian path exists */
	int odd = 0;
	for (i = 0; i < v; i++)	{
		if (list_len(adj[i]) & 1) {
			odd++;
		}
	}

	if (odd != 0 && odd != 2) {
		fprintf(stderr, "eulerian path does not exist\n");
		return 1;
	}

	/* cleanup */
	for (i = 0; i < v; i++)	{
		list_destroy(adj[i]);
	}
	free(adj);
}

list_t * list_new() {
	list_t *list;
	list = malloc(sizeof(list_t));
	list->head = NULL;
	return list;
}

void list_push(list_t *list, int val) {
	if (list == NULL) {
		return;
	}

	list_node_t *node = malloc(sizeof(list_node_t));
	node->val = val;
	node->next = NULL;

	if (list->head == NULL) {
		list->head = node;
		return;
	}

	list_node_t *current = list->head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = node;
}

int list_pop(list_t *list) {
	list_node_t *current = list->head,
	            *last = current->next;
	int val;

	if (last == NULL) {
		last = current;
		list->head = NULL;
	} else {
		while (last->next != NULL) {
			current = last;
			last = last->next;
		}
		current->next = NULL;
	}

	val = last->val;
	free(last);
	return val;
}

int list_len(list_t *list) {
	int len = 0;
	list_node_t *current = list->head;
	while(current != NULL) {
		current = current->next;
		len++;
	}
	return len;
}

void list_print(list_t *list) {
	list_node_t *current = list->head;
	while(current != NULL) {
		printf(" %d", current->val);
		current = current->next;
	}
	printf("\n");
}

void list_destroy(list_t *list) {
	if (list == NULL) {
		return;
	}

	list_node_t *current = list->head, *tmp;
	while (current != NULL) {
		tmp = current;
		current = current->next;
		free(tmp);
	}

	free(list);
}
