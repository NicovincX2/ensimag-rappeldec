#include <stdlib.h>
#include <stdio.h>

#define abmc(a ,b ,c) ((a + b) - c)

int main(int argc, char **argv) {
	(void) argc;
	(void) argv;

	/* version 1 et 2 */	
	float a=0.1f, b=0.2f, c=0.3f;
	printf("%e\n", abmc(a, b, c));

	double da=0.1, db=0.2, dc=0.3;
	printf("%e\n", abmc(da, db, dc));

	long double lda=0.1L, ldb=0.2L, ldc=0.3L;
	printf("%Le\n", abmc(lda, ldb, ldc));

	return EXIT_SUCCESS;
} 
