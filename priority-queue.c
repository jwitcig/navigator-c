#include <stdio.h>
#include <stdlib.h>

#include "priority-queue.h"

#define SIZE 0;

typedef PriorityQueue Queue;

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return i * 2;
}

int right(int i) {
    return i * 2 + 1;
}

int compare(int a, int b) {
    return a < b;
}

Queue* createQueue(int size) {
    Queue *queue = malloc(sizeof(Queue));
    queue->arraySize = size + 1;
    queue->queueSize = 0;
    queue->heap = malloc(sizeof(int) * (size + 1));
    queue->indexes = malloc(sizeof(int) * (size + 1));

    for (int i=0; i<size+1; i++) {
        queue->indexes[i] = -1;
    }
    return queue;
}

int indexOf(Queue *queue, int x) {
    return queue->indexes[x];
}

int includes(Queue *queue, int x) {
    return indexOf(queue, x) >= 0;
}

int hasIncluded(Queue *queue, int x) {
    return indexOf(queue, x) >= -2;
}

void exchange(Queue *queue, int xIndex, int yIndex) {
    int x = queue->heap[xIndex];
    int y = queue->heap[yIndex];

    queue->heap[xIndex] = y;
    queue->heap[yIndex] = x;
    
    // queue->indexes[this.getId(x)] = yIndex;
    // queue->indexes[this.getId(y)] = xIndex;
}

void heapify(Queue *queue, int i) {
    int l = left(i);
    int r = right(i);
    int target = i;

    if (l <= queue->queueSize && compare(queue->heap[l], queue->heap[target])) {
        target = l;
    }
    if (r <= queue->queueSize && compare(queue->heap[r], queue->heap[target])) {
        target = r;
    }
    if (target != i) {
        exchange(queue, i, target);
        heapify(queue, target);
    }
}
  
int min(Queue *queue) {
    return queue->heap[1];
}
  
int extractMin(Queue *queue) {
    if (queue->queueSize < 1) return -1;

    int target = queue->heap[1];
    // queue->indexes[this.getId(target)] = -2;
    exchange(queue, 1, queue->queueSize);
    queue->queueSize--;
    heapify(queue, 1);
    return target;
}

void update(Queue *queue, int i, int value) {
    int index = i;
    if (compare(queue->heap[index], value)) return;

    queue->heap[index] = value;

    while (index > 1 && compare(queue->heap[index], queue->heap[parent(index)])) {
      exchange(queue, index, parent(index));
      index = parent(index);
    }
}

void insert(Queue *queue, int x) {
    int size = ++queue->queueSize;
    queue->heap[size] = x;
    // queue->indexes[this.getId(x)] = size;
    update(queue, size, x);
}

int main(void) {
    Queue *queue = createQueue(4);
    insert(queue, 13);
    insert(queue, 14);
    insert(queue, 6565);
    insert(queue, 1);

    for (int i=0; i<4; i++) {
        printf("%d\n", extractMin(queue));
    }
    return 0;
}