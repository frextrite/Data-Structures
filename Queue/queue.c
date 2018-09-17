#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int front;
    int rear;
    int *array;
    int max_size;
};

struct Queue *createQueue(int max_size) {
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->max_size = max_size;
    queue->array = (int *)malloc(sizeof(int) * max_size);

    return queue;
}

bool enqueue(struct Queue *queue, int x) {
    if(queue->rear == queue->max_size - 1) {
        printf("Queue is full\n");
        return false;
    }
    if(queue->rear == -1) queue->front++;
    queue->array[queue->rear+1] = x;
    queue->rear++;
    return true;
}

int dequeue(struct Queue *queue) {
    if(queue->rear == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    int x = queue->array[queue->front];
    queue->front++;
    return x;
}

int main() {
    struct Queue *queue = createQueue(5);
    enqueue(queue, 5);
    enqueue(queue, 6);
    enqueue(queue, 2);
    enqueue(queue, 1);
    printf("Element removed %d\n", dequeue(queue));
    printf("Element removed %d\n", dequeue(queue));
    return 0;
}