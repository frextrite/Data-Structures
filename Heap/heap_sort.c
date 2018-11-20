#include <stdio.h>
#include <stdlib.h>

struct Heap { // max heap
	int *a; // array
	int size; // current heap size
};

void heapify(struct Heap*, int);

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int parent(int i) {
	return (i - 1) / 2;
}

int childLeft(int i) {
	return 2 * i + 1;
}

int childRight(int i) {
	return 2 * i + 2;
}

void insert(struct Heap *h, int *a, int x) {
	int i = h->size;
	a[i] = x;
	while(i != 0) {
		if(a[parent(i)] < a[i]) {
			swap(&a[parent(i)], &a[i]);

		}
		i = parent(i);
	}
}

void heapify(struct Heap *h, int i) {
	int l = childLeft(i);
	int r = childRight(i);
	int largest = i;
	if(l < h->size && h->a[l] > h->a[largest])
		largest = l;
	if(r < h->size && h->a[r] > h->a[largest])
		largest = r;
	if(largest != i) {
		swap(&h->a[largest], &h->a[i]);
		heapify(h, largest);
	}
}

void heapSort(struct Heap *h) {
	for(int i = (h->size-1) / 2; i >= 0; i--) {
		heapify(h, i);
	}
	for(int i = h->size-1; i >= 0; i --) {
		swap(&h->a[0], &h->a[i]);
		h->size--;
		heapify(h, 0);
	}
}

void printArray(struct Heap *h) {
	for(int i = 0; i < h->size; i++) {
		printf("%d ", h->a[i]);
	}
}

int main() {
	int a[] = {15, 14, 43, 32, 19, 8, 1, 7, 6, 20};
	struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
	h->size = 10;
	h->a = a;
	heapSort(h);
	h->size = 10;
	printArray(h);
	return 0;
}
