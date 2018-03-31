#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef enum { false, true } bool;
typedef struct {
	int Order;
	float **cy;
} matrix;
bool Malloc(matrix *);
// Allocate for the matrix£¬return ture if success£¬otherwise return false;
void Printf(matrix *);
//Print the details
void Free(matrix *);
//Free the memory that function malloc allocated
int y(int a);
//Return (-1)^a;
bool Scanf(matrix *);
// Assign for the matrix at the beginning£¬return ture if success£¬otherwise return false;
bool Assign(const matrix * ,matrix *,int );
// Assign for the new matrix£¬return ture if success£¬otherwise return false;
float Det(matrix *);
//Return the det of the matrix pointed by the incoming pointer 
int main(void) {
	matrix a;
	puts("enter the order of your matrix: ");
	while ((scanf_s("%d", &a.Order))&&(Malloc(&a))&&(Scanf(&a)))
	printf("the work is done ,the det of your matrix is %.0f\n", Det(&a));
	system("pause");
	return 0;
}
void Printf(matrix *a) {
	register int i, j;
	for (i = 0; i < a->Order; i++) {
		printf("|");
		for (j = 0; j < a->Order; j++)
			printf("%4.0f ", a->cy[i][j]);
		printf("|\n");
	}
	return;

}
bool Malloc(matrix * b) {
	b->cy = (float **)malloc(b->Order * sizeof(float *));
	if (b->cy == NULL) {
		fprintf(stderr,"unable to allocate memory for pointer cy");
		return false;
	}
	int i;
	for (i = 0; i < b->Order; i++) {
		b->cy[i] = (float *)malloc(b->Order * sizeof(float));
		if (b->cy[i] == NULL) {
			fprintf(stderr,"unable to allocate memory for pointer cy[%d+1]\n", i);
			return false;
		}
	}
	return true;
}
int y(int a) {
	return a % 2 == 0 ? 1 : -1;
}
void Free(matrix *a) {
	register int i;
	for (i = 0; i < a->Order; i++)
		free(a->cy[i]);
	free(a->cy);
}
bool Scanf(matrix * b) {
	int i, j;
	for (i = 0; i < b->Order; i++)
	for (j = 0; j < b->Order; j++)
	if (!scanf_s("%f", &b->cy[i][j])) {
	fprintf(stderr,"Unable to assign for a[%d][%d] \n", i + 1, j + 1);
	return false;
	}
	return true;
}
bool Assign(const matrix *a, matrix * b, int ORDER) {
	register int ia, ja, ib, jb;
	b->Order = a->Order - 1;
	if (!Malloc(b)){
		fprintf(stderr,"errors have happened");
	return false;
}
	for (ia=0,ib=0;ib<b->Order;ia++,ib++)
		for (ja=0,jb = 0; jb < b->Order;ja++,jb++) {
			if (ia == 0)
				ia++;
			if (ja == ORDER)
				ja++;
			b->cy[ib][jb] = a->cy[ia][ja]/**a->cy[0][ORDER]*y(ORDER)*/;
		}
	printf("%.0f¡Á\n", y(ORDER)*a->cy[0][ORDER]);
	Printf(b);
	return true;
}

float Det(matrix * a) {
	register float det = 0;
	if (a->Order == 1) {
		det = a->cy[0][0];
		Free(a);
		return det;
	}
	else {
		register int i;
		matrix *A = (matrix *)malloc(sizeof(matrix)*a->Order);
		for (i = 0; i < a->Order; i++) 
			if (!Assign(a, &A[i], i)) {
				fprintf(stderr, "errors happaned when function Assign is running\n");
				exit(EXIT_FAILURE);
			}
		for (i = 0; i < a->Order; i++) 
			det += Det(&A[i])*a->cy[0][i] * y(i);	
			free(A);
			Free(a);
		return det;
	}
}
