#include <stdio.h>
#include <stdlib.h>

/* types */
typedef struct list_node {
	int val;
	struct list_node *next;
} list_node_t;

typedef struct {
	int len;
	struct list_node *head;
} list_t;

/* functions */
list_t * list_new();
void list_destroy(list_t *);
void list_push(list_t *, int);

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

	/* cleanup */
	for (i = 0; i < v; i++)	{
		printf("[%d] -> %d\n", i, adj[i]->len);
		list_destroy(adj[i]);
	}
	free(adj);
}

list_t * list_new() {
	list_t *list;
	list = malloc(sizeof(list_t));
	list->len = 0;
	list->head = NULL;
	return list;
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

void list_push(list_t *list, int val) {
	if (list == NULL) {
		return;
	}

	list_node_t *node = malloc(sizeof(list_node_t));
	node->val = val;
	node->next = NULL;

	list->len++;

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
