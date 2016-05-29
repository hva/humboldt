#include <stdio.h>
#include <stdlib.h>

/* types */
typedef struct list_node {
	int val;
	struct list_node *next;
	struct list_node *prev;
} list_node_t;

typedef struct {
	struct list_node *head;
} list_t;

/* functions */
list_t * list_new();
list_node_t * list_node_new(int);
void list_push(list_t *, int);
int list_pop(list_t *);
void list_remove(list_t *, int);
int list_len(list_t *);
void list_print(list_t *);
void list_destroy(list_t *);
void cleanup(list_t **, int);

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
		fclose(fi);
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
			fclose(fi);
			cleanup(adj, v);
			return 1;
		}
		list_push(adj[a], b);
		list_push(adj[b], a);
	}

	/* close file */
	fclose(fi);

	/* check is eulerian path exists */
	int odd = 0, location;
	for (i = 0; i < v; i++)	{
		if (list_len(adj[i]) & 1) {
			odd++;
			location = i;
		}
	}

	if (odd != 0 && odd != 2) {
		fprintf(stderr, "eulerian path does not exist\n");
		cleanup(adj, v);
		return 1;
	}

	cleanup(adj, v);
}

list_t * list_new() {
	list_t *list;
	list = malloc(sizeof(list_t));
	list->head = NULL;
	return list;
}

list_node_t * list_node_new(int val) {
	list_node_t *node = malloc(sizeof(list_node_t));
	node->val = val;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void list_push(list_t *list, int val) {
	list_node_t *node = list_node_new(val), *h;

	h = list->head;
	list->head = node;
	if (h != NULL) {
		h->next = node;
		node->prev = h;
	}
}

int list_pop(list_t *list) {
	list_node_t *h = list->head;
	int val = h->val;

	if (h->prev != NULL) {
		h->prev->next = NULL;
	}
	list->head = h->prev;

	free(h);
	return val;
}

void list_remove(list_t *list, int val) {
	list_node_t *current = list->head, *search = NULL;

	while (current != NULL) {
		if (current->val == val) {
			search = current;
			break;
		}
		current = current->prev;
	}

	if (search == NULL) {
		return;
	}

	if (search->prev != NULL) {
		search->prev->next = search->next;
	}

	if (search->next != NULL) {
		search->next->prev = search->prev;
	}

	if (search == list->head) {
		list->head = search->prev;
	}

	free(search);
}

int list_len(list_t *list) {
	int len = 0;
	list_node_t *current = list->head;
	while(current != NULL) {
		current = current->prev;
		len++;
	}
	return len;
}

void list_print(list_t *list) {
	list_node_t *current = list->head;
	while(current != NULL) {
		printf(" %d", current->val);
		current = current->prev;
	}
	printf("\n");
}

void list_destroy(list_t *list) {
	list_node_t *current = list->head, *tmp;
	while (current != NULL) {
		tmp = current;
		current = current->prev;
		free(tmp);
	}

	free(list);
}

void cleanup(list_t **adj, int v) {
	int i;
	for (i = 0; i < v; i++)	{
		list_destroy(adj[i]);
	}
	free(adj);
}