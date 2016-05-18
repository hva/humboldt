#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "no input files\n");
		return 1;
	}

	FILE * fi;
	if ((fi = fopen(argv[1], "rt")) == 0) {
		fprintf(stderr, "%s: No such file or directory\n", argv[1]);
		return 1;
	}
	fclose(fi);
}