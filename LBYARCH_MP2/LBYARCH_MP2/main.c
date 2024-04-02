// Salen, Rommel Kendric D.
// Suba, Kaye Diosa Advincula
// S12

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, end;
extern double dotProductInit(double vectorA[], double vectorB[], int n);

void randomizeVectors(double vectorA[], double vectorB[], int n, double one_hundred) {
	for (int i = 0; i < n; i++) {
		vectorA[i] = ((double)rand() / RAND_MAX) * one_hundred;
		vectorB[i] = ((double)rand() / RAND_MAX) * one_hundred;
	}
}
double dotProductASM(double vectorA[], double vectorB[], int n, double sDot_ASM, double* time_used_ASM) {

	start = clock();
	sDot_ASM = dotProductInit(vectorA, vectorB, n);
	end = clock();
	*time_used_ASM = ((double)(end - start)) / CLOCKS_PER_SEC;
	return sDot_ASM;
}

double dotProductC(double vectorA[], double vectorB[], int n, double sDot_C, double* time_used_C) {

	start = clock();
	for (int i = 0; i < n; i++) {
		sDot_C += vectorA[i] * vectorB[i];
	}
	end = clock();
	*time_used_C = ((double)(end - start)) / CLOCKS_PER_SEC;

	return sDot_C;
}

int main() {
	//Constants
	int n = 0;

	while (1) {
		printf("Enter the value of which n will be raised to: ");
		int integerChecker = scanf_s("%d", &n);
		if (integerChecker == 1) {
			break;
		}
		else {
			printf("Invalid input. Try again.\n");
			while (getchar() != '\n');
		}
	}

	n = (int)pow(2, n);
	double one_hundred = 100;

	//Vectors
	double* vectorA = (double*)malloc(n * sizeof(double));
	double* vectorB = (double*)malloc(n * sizeof(double));

	//sDots 
	double sDot_ASM = 0.0;
	double sDot_C = 0.0;

	//Times
	double time_used_ASM = 0.0;
	double time_used_C = 0.0;

	//Total Times
	double total_ASM = 0.0;
	double total_C = 0.0;

	//Sanity Counter
	int correctness = 0;
	printf("The value of n is: %d", n);
	for (int i = 0; i < 30; i++) {
		randomizeVectors(vectorA, vectorB, n, one_hundred);

		//dotProduct solving via Assembly
		sDot_ASM = 0.0;
		printf("ASM	- Interation# %d\n", i + 1);
		sDot_ASM = dotProductASM(vectorA, vectorB, n, sDot_ASM, &time_used_ASM);
		total_ASM += time_used_ASM;
		printf("	TIME USED BY ASM: %f\n", time_used_ASM);
		printf("	VALUE OF sDOT in ASM: %f\n\n", sDot_ASM);

		//dotProduct solving via C
		sDot_C = 0.0;
		printf("C	- Interaction# %d\n", i + 1);
		sDot_C = dotProductC(vectorA, vectorB, n, sDot_C, &time_used_C);
		total_C += time_used_C;
		printf("	TIME USED BY C: %f\n", time_used_C);
		printf("	VALUE OF sDOT in C: %f\n", sDot_C);

		//Sanity and Correctness Check
		printf("\nSanity and Correctness Check: ");
		if (sDot_ASM == sDot_C) {
			printf("Passed. Values are equal.\n");
			correctness++;
		}
		else {
			printf("FAILED! Values are not equal.\n");
		}

	}

	//Avg. Times
	double avg_ASM = total_ASM / 30.0;
	double avg_C = total_C / 30.0;

	printf("Average Assembly time: %f\n", (avg_ASM / 30.0));
	printf("Average C time: %f\n", (avg_C / 30.0));
	printf("Total Passed Sanity Checks: %d\n", correctness);

	free(vectorA);
	free(vectorB);
}
