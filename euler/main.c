#include <stdio.h>

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
	int a, b, n;
	int x;

	x = fscanf(fi, "%d", &n);

	if (x == EOF || x == 0) {
		fprintf(stderr, "invalid input\n");
		return 1;
	}

	printf("%d\n", n);

	while ((x = fscanf(fi, "%d %d", &a, &b)) != EOF) {
		if (x == 0) {
			fprintf(stderr, "invalid input\n");
			return 1;
		}
		printf("%d, %d\n", a, b);
	}


	/* close file */
	fclose(fi);
}