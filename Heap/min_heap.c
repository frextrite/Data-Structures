#include <stdio.h>
#include <stdlib.h>

struct MinHeap {
	int *harr;
	int capacity;
	int heap_size;
};

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void MinHeapify(struct MinHeap*, int);

int parent(int i) {
	return (i-1) / 2;
}

int childLeft(int i) {
	return 2 * i + 1;
}

int childRight(int i) {
	return 2 * i + 2;
}

void insertKey(struct MinHeap *min_heap, int x) {
	min_heap->heap_size++;
	min_heap->harr[min_heap->heap_size-1] = x;
	int i = min_heap->heap_size - 1;
	while(i != 0 && min_heap->harr[parent(i)] > min_heap->harr[i]) {
		swap(&min_heap->harr[parent(i)], &min_heap->harr[i]);
		i = parent(i);
	}
}

void decrease(struct MinHeap *min_heap, int i, int x) {
	min_heap->harr[i] = x;
	while(i != 0 && min_heap->harr[parent(i)] > min_heap->harr[i]) {
		swap(&min_heap->harr[parent(i)], &min_heap->harr[i]);
	}
}

int extractMin(struct MinHeap *min_heap) {
	if(min_heap->heap_size == 0) {
		return -1;
	}
	if(min_heap->heap_size == 1) {
		min_heap->heap_size--;
		return min_heap->harr[0];
	}

	int x = min_heap->harr[0];
	min_heap->harr[0] = min_heap->harr[min_heap->heap_size-1];
	min_heap->heap_size--;
	MinHeapify(min_heap, 0);
	return x;
}

void deleteKey(struct MinHeap *min_heap, int i) {
	decrease(min_heap, i, -1);
	extractMin(min_heap);
}

void MinHeapify(struct MinHeap *min_heap, int i) {
	int l = childLeft(i);
	int r = childRight(i);
	int smallest = i;

	if(l < min_heap->heap_size && min_heap->harr[l] < min_heap->harr[smallest]) {
		swap(&min_heap->harr[l], &min_heap->harr[smallest]);
		smallest = l;
	}

	if(r < min_heap->heap_size && min_heap->harr[r] < min_heap->harr[smallest]) {
		swap(&min_heap->harr[r], &min_heap->harr[smallest]);
		smallest = r;
	}

	if(smallest != i) {
		MinHeapify(min_heap, smallest);
	}

}

int *getMin(struct MinHeap *min_heap) {
	return min_heap->harr;
}

int main() {
	struct MinHeap *heap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
	int capacity = 100;
	heap->capacity = capacity;
	heap->harr = (int *)calloc(capacity, sizeof(int));
	heap->heap_size = 0;
	insertKey(heap, 5);
	insertKey(heap, 4);
	insertKey(heap, 2);
	insertKey(heap, 1);
	printf("Minimum element: %d\n", extractMin(heap));
	printf("Minimum element: %d\n", extractMin(heap));
	insertKey(heap, 0);
	printf("Minimum element: %d\n", extractMin(heap));
	decrease(heap, 1, 1);
	printf("Minimum element: %d\n", extractMin(heap));
	printf("Minimum element: %d\n", extractMin(heap));
	printf("Minimum element: %d\n", extractMin(heap));
	printf("Minimum element: %d\n", extractMin(heap));
	return 0;
}
