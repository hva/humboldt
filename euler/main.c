#include <stdio.h>
#include <stdlib.h>

/* linked list type */
typedef struct node {
    int val;
    struct node * next;
} node_t;

void push(node_t *head, int val);
void print_list(node_t *head);

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

	node_t *adj[v];
	int i;
	for (i = 0; i < v; i++)
	{
		adj[i] = NULL;
	}

	while ((x = fscanf(fi, "%d %d", &a, &b)) != EOF) {
		if (x == 0) {
			fprintf(stderr, "invalid input\n");
			return 1;
		}

		if (adj[a] == NULL) {
			adj[a] = malloc(sizeof(node_t));
			adj[a]->val = b;
			adj[a]->next = NULL;
		}
		else {
			push(adj[a], b);
		}

		if (adj[b] == NULL) {
			adj[b] = malloc(sizeof(node_t));
			adj[b]->val = a;
			adj[b]->next = NULL;
		}
		else {
			push(adj[b], a);
		}

	}

	/* close file */
	fclose(fi);

	for (i = 0; i < v; i++)
	{
		fprintf(stderr, "----%d\n", i);
		print_list(adj[i]);
	}
}


void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        fprintf(stderr, "%d\n", current->val);
        current = current->next;
    }
}

void push(node_t *head, int val) {
	node_t * current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}