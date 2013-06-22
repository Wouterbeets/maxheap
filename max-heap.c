/* Max heap implementation w/ extract max */
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define left(i) ((i)<<1)
#define right(i) (((i)<<1)+1)
#define parent(i) ((i)>>1)

typedef struct {
	int size;
	int element[100];
} Heap;

//Swaps the values of two ints a and b
void swap(int * a, int * b) {
	int temp;
	temp = * a;
	* a = * b;
	* b = temp;
}

//Ensures that the max heap property in heap A is satisfied at and below index i
void makeHeap(Heap * A, int i) {
	int largest = A->element[i];
	int position = i;
	int l = left(i);
	if(l <= A->size && A->element[l] > largest) {
		largest = A->element[l];
		position = l;
	}
	int r = right(i);
	if(r <= A->size && A->element[r] > largest) {
		largest = A->element[r];
		position = r;
	}
	if(i != position) {
		swap(&A->element[i], &A->element[position]);
		makeHeap(A, position);
	}
}

//Get the maximum value in the heap A
int extractMax(Heap * A) {
	if(!A->size) {
		puts("error: heap empty");
		return 0;	//Ensure that the heap isn't empty
	}
	int max = A->element[0];
	swap(&A->element[0], &A->element[A->size]);
	--A->size; 
	makeHeap(A, 0);
	return max;
}

//Increase the key of the ith element in heap A to be k
void increaseKey(Heap * A, int i, int k) {
	if(A->element[i] >= k) return;
	int position = i;
	while(position != 0 && A->element[parent(position)] < k) {
		A->element[position] = A->element[parent(position)];
		position = parent(position);
	}
	A->element[position] = k;
}

//Inserts the value i into the heap A
void insert(Heap * A, int i) {
	if(A->size > 99) printf("error: heap full\n");
	A->element[A->size] = INT_MIN;
	increaseKey(A, A->size, i);
	++A->size;
}

//Prints the heap A as an array
void print(Heap * A) {
	int i = 0;
	printf("[ ");
	for(i = 0; i < A->size; i++) {
		printf("%d ", A->element[i]);
	}
	printf("]\n");
}

//Makes a heap out of an unsorted array a of n elements 
void buildHeap(Heap * A, int * a, int n) {
	if(n > 100) {
		printf("error: too many elements\n");
		return;
	}
	if(A->size) {
		printf("error: heap not empty\n");
	}
	int nbytes = n * sizeof(int);
	memcpy(A->element, a, nbytes);
	A->size = n;
	int i = 0;
	for(i = A->size/2; i > -1 ; i--) {
		makeHeap(A, i);
	}
}

int main() {
	Heap someHeap = {0, {0}};
	Heap * A = &someHeap;
	print(A);
	int a[10] = {1234, 443234, 3141, 5, 14, 2, 234, 1, 4521435, 1112};
	buildHeap(A, a, 10);
	print(A);
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	printf("%d\n", extractMax(A));
	return 0;
}
